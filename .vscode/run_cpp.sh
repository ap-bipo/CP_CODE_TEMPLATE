#!/bin/bash
# =============================================================================
# C++ Runner with Resource Limits (like Online Judge / Codeforces / VNOI)
# Shows: Time, Memory, Verdict (AC / TLE / MLE / RTE)
# Cross-Platform: macOS (Darwin), Windows (Git Bash/MSYS2), Linux
# =============================================================================

# --- Configuration (adjust as needed) ---
TIME_LIMIT=5           # seconds (TLE threshold)
MEMORY_LIMIT_MB=1024   # MB = 1 GB (MLE threshold)
STACK_LIMIT=65536      # KB = 64 MB (stack size for deep recursion)
CPP_STD="c++17"

# --- Operating System Detection ---
OS_NAME="$(uname -s 2>/dev/null || echo "Unknown")"
IS_MAC=false
IS_WINDOWS=false
IS_LINUX=false

if [[ "$OS_NAME" =~ ^Darwin ]]; then
    IS_MAC=true
elif [[ "$OS_NAME" =~ ^(MINGW|MSYS|CYGWIN) ]] || [ "$OS" = "Windows_NT" ]; then
    IS_WINDOWS=true
elif [[ "$OS_NAME" =~ ^Linux ]]; then
    IS_LINUX=true
else
    # Fallback heuristic
    if [ -n "$WINDIR" ] || [ -n "$SYSTEMROOT" ]; then
        IS_WINDOWS=true
    else
        IS_LINUX=true
    fi
fi

# --- Platform-specific Compiler & Flags ---
if [ "$IS_MAC" = true ]; then
    # macOS: Ưu tiên g++ mới nhất từ Homebrew nếu có, fallback về g++ mặc định / clang++
    if command -v g++-16 >/dev/null 2>&1; then
        COMPILER="g++-16"
    elif command -v g++-15 >/dev/null 2>&1; then
        COMPILER="g++-15"
    elif command -v g++-14 >/dev/null 2>&1; then
        COMPILER="g++-14"
    else
        COMPILER="g++"
    fi
    SDK_PATH=$(xcrun --show-sdk-path 2>/dev/null)
    EXTRA_COMPILE_FLAGS=""
    if [ -n "$SDK_PATH" ]; then
        EXTRA_COMPILE_FLAGS="-isysroot ${SDK_PATH}"
    fi

elif [ "$IS_WINDOWS" = true ]; then
    # Windows (MinGW-w64 / MSYS2 / WinLibs): dùng g++
    COMPILER="g++"
    SDK_PATH=""
    # Trên Windows, lệnh ulimit -s không tăng stack size của file .exe được.
    # Cần dùng cờ linker -Wl,--stack,67108864 để cấp 64MB Stack (tránh lỗi Stack Overflow khi đệ quy sâu)
    EXTRA_COMPILE_FLAGS="-Wl,--stack,67108864"

else
    # Linux
    COMPILER="g++"
    SDK_PATH=""
    EXTRA_COMPILE_FLAGS=""
fi

# --- Detect Python command for precise timing ---
if command -v python3 >/dev/null 2>&1; then
    PYTHON_CMD="python3"
elif command -v python >/dev/null 2>&1; then
    PYTHON_CMD="python"
elif command -v py >/dev/null 2>&1; then
    PYTHON_CMD="py"
else
    PYTHON_CMD=""
fi

MEMORY_LIMIT_KB=$((MEMORY_LIMIT_MB * 1024))
MEMORY_LIMIT_BYTES=$((MEMORY_LIMIT_MB * 1024 * 1024))

# --- Colors for output ---
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color
BOLD='\033[1m'
DIM='\033[2m'

# --- Input validation ---
if [ -z "$1" ]; then
    echo -e "${RED}✗ Error: No source file provided${NC}"
    echo "Usage: $0 <source_file.cpp>"
    exit 1
fi

SOURCE_FILE="$1"
DIR=$(cd "$(dirname "$SOURCE_FILE")" 2>/dev/null && pwd)
if [ -z "$DIR" ]; then
    DIR=$(dirname "$SOURCE_FILE")
fi
FILENAME=$(basename "$SOURCE_FILE")
BASENAME="${FILENAME%.*}"   # strip any extension (.cpp, .CPP, .cc, ...)

if [ "$IS_WINDOWS" = true ]; then
    EXECUTABLE="${DIR}/${BASENAME}.exe"
else
    EXECUTABLE="${DIR}/${BASENAME}"
    # Safety: on macOS (case-insensitive FS) never let the executable overwrite/delete the source
    SRC_LC=$(echo "$SOURCE_FILE" | tr '[:upper:]' '[:lower:]')
    EXE_LC=$(echo "$EXECUTABLE" | tr '[:upper:]' '[:lower:]')
    if [ "$SRC_LC" = "$EXE_LC" ]; then
        EXECUTABLE="${DIR}/${BASENAME}.out"
    fi
fi

TIME_LOG=$(mktemp 2>/dev/null || mktemp -t cpp_runner_time.XXXXXX 2>/dev/null || echo "/tmp/cpp_runner_time_$$")

# --- Compilation ---
echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${BOLD}⚙ Compiling${NC} ${BASENAME}.cpp (${COMPILER}) ..."

COMPILE_ARGS="-std=${CPP_STD} -O2 -Wall -Wextra -Wshadow"
if [ -n "$EXTRA_COMPILE_FLAGS" ]; then
    COMPILE_ARGS="${COMPILE_ARGS} ${EXTRA_COMPILE_FLAGS}"
fi

$COMPILER $COMPILE_ARGS "$SOURCE_FILE" -o "$EXECUTABLE" 2>&1
COMPILE_STATUS=$?

if [ $COMPILE_STATUS -ne 0 ]; then
    echo -e "${RED}✗ Compilation Error (CE)${NC}"
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    rm -f "$TIME_LOG"
    exit 1
fi

echo -e "${GREEN}✓ Compiled successfully${NC}"
echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${DIM}  Time Limit : ${TIME_LIMIT}s  |  Memory Limit : ${MEMORY_LIMIT_MB} MB  |  Stack : $((STACK_LIMIT / 1024)) MB${NC}"
echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

# --- Detect input file used by fopen(...) in source ---
detect_input_file() {
    local src="$1" line var ext name
    line=$(grep -m1 -E 'fopen[[:space:]]*\(' "$src" | tr -d '\r')
    [ -z "$line" ] && return
    # Literal file name: fopen("ABC.INP", ...)
    name=$(echo "$line" | sed -nE 's/.*fopen[[:space:]]*\([[:space:]]*"([^"]+)".*/\1/p' | tr -d '\r')
    if [ -n "$name" ]; then echo "$name"; return; fi
    # Macro/variable + extension: fopen(task".INP", ...)
    var=$(echo "$line" | sed -nE 's/.*fopen[[:space:]]*\([[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*"[^"]*".*/\1/p' | tr -d '\r')
    ext=$(echo "$line" | sed -nE 's/.*fopen[[:space:]]*\([[:space:]]*[A-Za-z_][A-Za-z0-9_]*[[:space:]]*"([^"]*)".*/\1/p' | tr -d '\r')
    [ -z "$var" ] && return
    name=$(grep -m1 -E "#[[:space:]]*define[[:space:]]+${var}[[:space:]]+\"" "$src" | sed -nE 's/.*"([^"]*)".*/\1/p' | tr -d '\r')
    if [ -z "$name" ]; then
        name=$(grep -m1 -E "[^A-Za-z0-9_]${var}[[:space:]]*(\[[^]]*\])?[[:space:]]*=[[:space:]]*\"" "$src" | sed -nE 's/.*"([^"]*)".*/\1/p' | tr -d '\r')
    fi
    [ -n "$name" ] && echo "${name}${ext}"
}

INPUT_FILE=$(detect_input_file "$SOURCE_FILE")

# Change to the directory containing the source file so fopen can find .INP/.OUT files
cd "$DIR" || exit 1

# Interactive mode: input file missing / not readable (or code has no fopen)
# -> program reads from the terminal, no time-limit watchdog (you need time to type)
INTERACTIVE=false
if [ -z "$INPUT_FILE" ] || [ ! -r "$INPUT_FILE" ]; then
    INTERACTIVE=true
fi

if [ "$INTERACTIVE" = true ]; then
    if [ -n "$INPUT_FILE" ]; then
        echo -e "${YELLOW}⚠ Không tìm thấy / không mở được '${INPUT_FILE}' → nhập dữ liệu từ terminal${NC}"
    else
        echo -e "${YELLOW}⌨ Không dùng file input → nhập dữ liệu từ terminal${NC}"
    fi
    echo -e "${DIM}  (Time Limit tắt ở chế độ này, nhấn Ctrl+D hoặc Ctrl+Z để kết thúc input)${NC}"
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
else
    echo -e "${DIM}  📄 Input file: ${INPUT_FILE}${NC}"
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
fi

# Timestamp helper
get_now_ts() {
    if [ -n "$PYTHON_CMD" ]; then
        $PYTHON_CMD -c "import time; print(time.time())" 2>/dev/null
    else
        date +%s
    fi
}

START_TIME=$(get_now_ts)

if [ "$INTERACTIVE" = true ]; then
    # Run in foreground with stdin attached to the terminal
    if { : < /dev/tty; } 2>/dev/null; then
        STDIN_SRC=/dev/tty
    else
        STDIN_SRC=/dev/stdin
    fi

    if [ "$IS_MAC" = true ]; then
        (
            ulimit -v $((MEMORY_LIMIT_KB * 2)) 2>/dev/null
            ulimit -s $STACK_LIMIT 2>/dev/null
            exec /usr/bin/time -l "$EXECUTABLE" 2>"$TIME_LOG"
        ) < "$STDIN_SRC"
        EXIT_CODE=$?
    elif [ "$IS_LINUX" = true ]; then
        (
            ulimit -v $((MEMORY_LIMIT_KB * 2)) 2>/dev/null
            ulimit -s $STACK_LIMIT 2>/dev/null
            if [ -x /usr/bin/time ]; then
                exec /usr/bin/time -v "$EXECUTABLE" 2>"$TIME_LOG"
            else
                exec "$EXECUTABLE"
            fi
        ) < "$STDIN_SRC"
        EXIT_CODE=$?
    else
        # Windows
        "$EXECUTABLE" < "$STDIN_SRC"
        EXIT_CODE=$?
    fi
else
    # Start the process in background with resource limits
    if [ "$IS_MAC" = true ]; then
        (
            ulimit -v $((MEMORY_LIMIT_KB * 2)) 2>/dev/null
            ulimit -s $STACK_LIMIT 2>/dev/null
            exec /usr/bin/time -l "$EXECUTABLE" 2>"$TIME_LOG"
        ) &
        PID=$!
    elif [ "$IS_LINUX" = true ]; then
        (
            ulimit -v $((MEMORY_LIMIT_KB * 2)) 2>/dev/null
            ulimit -s $STACK_LIMIT 2>/dev/null
            if [ -x /usr/bin/time ]; then
                exec /usr/bin/time -v "$EXECUTABLE" 2>"$TIME_LOG"
            else
                exec "$EXECUTABLE"
            fi
        ) &
        PID=$!
    else
        # Windows: Run directly or via python to track peak memory if available
        if [ -n "$PYTHON_CMD" ]; then
            (
                $PYTHON_CMD -c '
import sys, subprocess, ctypes
from ctypes import wintypes
class PMC(ctypes.Structure):
    _fields_ = [
        ("cb", wintypes.DWORD), ("PageFaultCount", wintypes.DWORD),
        ("PeakWorkingSetSize", ctypes.c_size_t), ("WorkingSetSize", ctypes.c_size_t),
        ("QuotaPeakPagedPoolUsage", ctypes.c_size_t), ("QuotaPagedPoolUsage", ctypes.c_size_t),
        ("QuotaPeakNonPagedPoolUsage", ctypes.c_size_t), ("QuotaNonPagedPoolUsage", ctypes.c_size_t),
        ("PagefileUsage", ctypes.c_size_t), ("PeakPagefileUsage", ctypes.c_size_t)
    ]
exe = sys.argv[1]
log = sys.argv[2]
try:
    p = subprocess.Popen([exe])
    p.wait()
    pmc = PMC()
    pmc.cb = ctypes.sizeof(PMC)
    try:
        ctypes.windll.psapi.GetProcessMemoryInfo(p._handle, ctypes.byref(pmc), ctypes.sizeof(PMC))
        with open(log, "w") as f:
            f.write(str(pmc.PeakWorkingSetSize))
    except Exception:
        pass
    sys.exit(p.returncode)
except Exception:
    sys.exit(1)
' "$EXECUTABLE" "$TIME_LOG"
            ) &
            PID=$!
        else
            "$EXECUTABLE" &
            PID=$!
        fi
    fi

    # Watchdog: kill after TIME_LIMIT seconds
    (
        sleep $TIME_LIMIT
        kill -9 $PID 2>/dev/null
        pkill -9 -P $PID 2>/dev/null
        if [ "$IS_WINDOWS" = true ]; then
            taskkill //F //PID $PID 2>/dev/null
            taskkill //F //IM "${BASENAME}.exe" 2>/dev/null
        fi
    ) &
    WATCHDOG_PID=$!

    # Wait for the main process to finish
    wait $PID 2>/dev/null
    EXIT_CODE=$?

    # Kill the watchdog if the process finished before timeout
    kill $WATCHDOG_PID 2>/dev/null
    wait $WATCHDOG_PID 2>/dev/null
fi

END_TIME=$(get_now_ts)
if [ -n "$PYTHON_CMD" ]; then
    ELAPSED=$($PYTHON_CMD -c "print(f'{${END_TIME} - ${START_TIME}:.3f}')" 2>/dev/null || echo "0.000")
else
    ELAPSED="$((END_TIME - START_TIME)).000"
fi

# --- Extract peak memory from log ---
PEAK_MEM_BYTES=""
if [ "$IS_MAC" = true ]; then
    # macOS /usr/bin/time -l reports bytes
    PEAK_MEM_BYTES=$(grep "maximum resident set size" "$TIME_LOG" 2>/dev/null | awk '{print $1}')
elif [ "$IS_LINUX" = true ]; then
    # Linux /usr/bin/time -v reports kbytes
    PEAK_MEM_KB=$(grep -i "Maximum resident set size" "$TIME_LOG" 2>/dev/null | awk -F': ' '{print $2}' | tr -d ' ')
    if [ -n "$PEAK_MEM_KB" ]; then
        PEAK_MEM_BYTES=$((PEAK_MEM_KB * 1024))
    fi
elif [ "$IS_WINDOWS" = true ]; then
    if [ -s "$TIME_LOG" ]; then
        VAL=$(cat "$TIME_LOG" 2>/dev/null | tr -d '\r\n ')
        if [[ "$VAL" =~ ^[0-9]+$ ]]; then
            PEAK_MEM_BYTES="$VAL"
        fi
    fi
fi

if [ -z "$PEAK_MEM_BYTES" ] || [ "$PEAK_MEM_BYTES" = "0" ]; then
    PEAK_MEM_DISPLAY="N/A"
else
    PEAK_MEM_KB=$((PEAK_MEM_BYTES / 1024))
    if [ $PEAK_MEM_KB -lt 1024 ]; then
        PEAK_MEM_DISPLAY="${PEAK_MEM_KB} KB"
    else
        if [ -n "$PYTHON_CMD" ]; then
            PEAK_MEM_MB=$($PYTHON_CMD -c "print(f'{${PEAK_MEM_BYTES} / 1024 / 1024:.2f}')")
            PEAK_MEM_DISPLAY="${PEAK_MEM_MB} MB"
        else
            PEAK_MEM_DISPLAY="$((PEAK_MEM_KB / 1024)) MB"
        fi
    fi
fi

# Check if memory exceeded
MEM_EXCEEDED=false
if [ -n "$PEAK_MEM_BYTES" ] && [ "$PEAK_MEM_BYTES" != "0" ]; then
    if [ "$PEAK_MEM_BYTES" -gt "$MEMORY_LIMIT_BYTES" ] 2>/dev/null; then
        MEM_EXCEEDED=true
    fi
fi

echo ""
echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

# --- Verdict ---
if [ -n "$PYTHON_CMD" ]; then
    ELAPSED_INT=$($PYTHON_CMD -c "print(int(float('${ELAPSED}') + 0.5))" 2>/dev/null || echo "0")
else
    ELAPSED_INT="${ELAPSED%.*}"
    [ -z "$ELAPSED_INT" ] && ELAPSED_INT=0
fi

if [ "$MEM_EXCEEDED" = true ]; then
    echo -e "${RED}${BOLD}✗ Memory Limit Exceeded (MLE)${NC}"
elif [ $EXIT_CODE -eq 0 ]; then
    echo -e "${GREEN}${BOLD}✓ Accepted (AC)${NC}"
elif [ $EXIT_CODE -eq 137 ] || [ $EXIT_CODE -eq 9 ]; then
    if [ "$INTERACTIVE" = false ] && [ "$ELAPSED_INT" -ge "$TIME_LIMIT" ]; then
        echo -e "${RED}${BOLD}✗ Time Limit Exceeded (TLE)${NC}"
    else
        echo -e "${RED}${BOLD}✗ Memory Limit Exceeded (MLE)${NC}"
    fi
# Segmentation Fault (macOS/Linux/Windows 0xC0000005)
elif [ $EXIT_CODE -eq 139 ] || [ $EXIT_CODE -eq 11 ] || [ $EXIT_CODE -eq 3221225477 ] || [ $EXIT_CODE -eq -1073741819 ]; then
    echo -e "${RED}${BOLD}✗ Runtime Error (RTE)${NC} — Segmentation Fault (Truy cập bộ nhớ không hợp lệ)"
# Stack Overflow (Windows 0xC00000FD)
elif [ $EXIT_CODE -eq 3221225725 ] || [ $EXIT_CODE -eq -1073741571 ]; then
    echo -e "${RED}${BOLD}✗ Runtime Error (RTE)${NC} — Stack Overflow (Đệ quy quá sâu / Tràn stack)"
# Division by zero (macOS/Linux/Windows 0xC0000094)
elif [ $EXIT_CODE -eq 136 ] || [ $EXIT_CODE -eq 8 ] || [ $EXIT_CODE -eq 3221225620 ] || [ $EXIT_CODE -eq -1073741676 ]; then
    echo -e "${RED}${BOLD}✗ Runtime Error (RTE)${NC} — Floating point exception (Chia cho 0)"
# Aborted assertion failed
elif [ $EXIT_CODE -eq 134 ] || [ $EXIT_CODE -eq 6 ] || [ $EXIT_CODE -eq 3221225478 ] || [ $EXIT_CODE -eq -1073741818 ]; then
    echo -e "${RED}${BOLD}✗ Runtime Error (RTE)${NC} — Aborted (assertion failed)"
else
    echo -e "${RED}${BOLD}✗ Runtime Error (RTE)${NC} — exit code: ${EXIT_CODE}"
fi

if [ "$INTERACTIVE" = true ]; then
    echo -e "  ${MAGENTA}⏱ Time   :${NC} ${ELAPSED}s ${DIM}(gồm cả thời gian nhập)${NC}"
else
    echo -e "  ${MAGENTA}⏱ Time   :${NC} ${ELAPSED}s"
fi
echo -e "  ${MAGENTA}💾 Memory :${NC} ${PEAK_MEM_DISPLAY}"
echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

# --- Cleanup ---
rm -f "$EXECUTABLE" "$TIME_LOG"
if [ "$IS_WINDOWS" = true ]; then
    rm -f "${DIR}/${BASENAME}.exe" "${DIR}/${BASENAME}"
fi

exit $EXIT_CODE
