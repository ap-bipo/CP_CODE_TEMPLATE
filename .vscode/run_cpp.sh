#!/bin/bash
# =============================================================================
# C++ Runner with Resource Limits (like Online Judge / Codeblock)
# Shows: Time, Memory, Verdict (AC / TLE / MLE / RTE)
# Compatible with macOS (no coreutils needed)
# =============================================================================

# --- Configuration (adjust as needed) ---
TIME_LIMIT=5           # seconds (TLE threshold)
MEMORY_LIMIT_MB=1024   # MB = 1 GB (MLE threshold)
STACK_LIMIT=65536      # KB = 64 MB (stack size for deep recursion)
COMPILER="g++-16"
CPP_STD="c++17"
SDK_PATH=$(xcrun --show-sdk-path 2>/dev/null)

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
DIR=$(dirname "$SOURCE_FILE")
FILENAME=$(basename "$SOURCE_FILE")
BASENAME="${FILENAME%.*}"   # strip any extension (.cpp, .CPP, .cc, ...) — case-insensitive safe
EXECUTABLE="${DIR}/${BASENAME}"

# Safety: on macOS (case-insensitive FS) never let the executable overwrite/delete the source
SRC_LC=$(echo "$SOURCE_FILE" | tr '[:upper:]' '[:lower:]')
EXE_LC=$(echo "$EXECUTABLE" | tr '[:upper:]' '[:lower:]')
if [ "$SRC_LC" = "$EXE_LC" ]; then
    EXECUTABLE="${DIR}/${BASENAME}.out"
fi
TIME_LOG=$(mktemp /tmp/cpp_runner_time.XXXXXX)

# --- Compilation ---
echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${BOLD}⚙ Compiling${NC} ${BASENAME}.cpp ..."

COMPILE_ARGS="-std=${CPP_STD} -O2 -Wall -Wextra -Wshadow"
if [ -n "$SDK_PATH" ]; then
    COMPILE_ARGS="${COMPILE_ARGS} -isysroot ${SDK_PATH}"
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

# --- Run with resource limits + memory tracking ---
# /usr/bin/time -l gives "maximum resident set size" in bytes on macOS

# --- Detect input file used by fopen(...) in source ---
# Supports:
#   #define task "ABC"   ...  if(fopen(task".INP","r"))
#   const string/char task[] = "ABC"; ... fopen(task".INP","r")
#   fopen("ABC.INP","r")
detect_input_file() {
    local src="$1" line var ext name
    line=$(grep -m1 -E 'fopen[[:space:]]*\(' "$src")
    [ -z "$line" ] && return
    # Literal file name: fopen("ABC.INP", ...)
    name=$(echo "$line" | sed -nE 's/.*fopen[[:space:]]*\([[:space:]]*"([^"]+)".*/\1/p')
    if [ -n "$name" ]; then echo "$name"; return; fi
    # Macro/variable + extension: fopen(task".INP", ...)
    var=$(echo "$line" | sed -nE 's/.*fopen[[:space:]]*\([[:space:]]*([A-Za-z_][A-Za-z0-9_]*)[[:space:]]*"[^"]*".*/\1/p')
    ext=$(echo "$line" | sed -nE 's/.*fopen[[:space:]]*\([[:space:]]*[A-Za-z_][A-Za-z0-9_]*[[:space:]]*"([^"]*)".*/\1/p')
    [ -z "$var" ] && return
    name=$(grep -m1 -E "#[[:space:]]*define[[:space:]]+${var}[[:space:]]+\"" "$src" | sed -nE 's/.*"([^"]*)".*/\1/p')
    if [ -z "$name" ]; then
        name=$(grep -m1 -E "[^A-Za-z0-9_]${var}[[:space:]]*(\[[^]]*\])?[[:space:]]*=[[:space:]]*\"" "$src" | sed -nE 's/.*"([^"]*)".*/\1/p')
    fi
    [ -n "$name" ] && echo "${name}${ext}"
}

INPUT_FILE=$(detect_input_file "$SOURCE_FILE")

# Change to the directory containing the source file so fopen can find .INP/.OUT files
cd "$DIR"

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
    echo -e "${DIM}  (Time Limit tắt ở chế độ này, nhấn Ctrl+D để kết thúc input nếu cần)${NC}"
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
else
    echo -e "${DIM}  📄 Input file: ${INPUT_FILE}${NC}"
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
fi

START_TIME=$(python3 -c "import time; print(time.time())")

if [ "$INTERACTIVE" = true ]; then
    # Run in foreground with stdin attached to the terminal
    if { : < /dev/tty; } 2>/dev/null; then
        STDIN_SRC=/dev/tty
    else
        STDIN_SRC=/dev/stdin
    fi
    (
        ulimit -v $((MEMORY_LIMIT_KB * 2)) 2>/dev/null
        ulimit -s $STACK_LIMIT 2>/dev/null
        exec /usr/bin/time -l "$EXECUTABLE" 2>"$TIME_LOG"
    ) < "$STDIN_SRC"
    EXIT_CODE=$?
else
    # Start the process in background with resource limits and memory tracking
    (
        ulimit -v $((MEMORY_LIMIT_KB * 2)) 2>/dev/null  # Virtual memory limit (2x for safety margin)
        ulimit -s $STACK_LIMIT 2>/dev/null               # Stack limit
        exec /usr/bin/time -l "$EXECUTABLE" 2>"$TIME_LOG"
    ) &
    PID=$!

    # Watchdog: kill after TIME_LIMIT seconds
    (
        sleep $TIME_LIMIT
        # Kill the entire process group
        kill -9 $PID 2>/dev/null
        # Also kill any children (the actual executable)
        pkill -9 -P $PID 2>/dev/null
    ) &
    WATCHDOG_PID=$!

    # Wait for the main process to finish
    wait $PID 2>/dev/null
    EXIT_CODE=$?

    # Kill the watchdog if the process finished before timeout
    kill $WATCHDOG_PID 2>/dev/null
    wait $WATCHDOG_PID 2>/dev/null
fi

END_TIME=$(python3 -c "import time; print(time.time())")
ELAPSED=$(python3 -c "print(f'{${END_TIME} - ${START_TIME}:.3f}')")

# --- Extract peak memory from /usr/bin/time output ---
# macOS /usr/bin/time -l reports "maximum resident set size" in bytes
PEAK_MEM_BYTES=$(grep "maximum resident set size" "$TIME_LOG" 2>/dev/null | awk '{print $1}')
if [ -z "$PEAK_MEM_BYTES" ] || [ "$PEAK_MEM_BYTES" = "0" ]; then
    PEAK_MEM_MB="N/A"
    PEAK_MEM_DISPLAY="N/A"
else
    PEAK_MEM_KB=$((PEAK_MEM_BYTES / 1024))
    if [ $PEAK_MEM_KB -lt 1024 ]; then
        PEAK_MEM_DISPLAY="${PEAK_MEM_KB} KB"
    else
        PEAK_MEM_MB=$(python3 -c "print(f'{${PEAK_MEM_BYTES} / 1024 / 1024:.2f}')")
        PEAK_MEM_DISPLAY="${PEAK_MEM_MB} MB"
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
ELAPSED_INT=$(python3 -c "print(int(float('${ELAPSED}') + 0.5))")

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
elif [ $EXIT_CODE -eq 139 ] || [ $EXIT_CODE -eq 11 ]; then
    echo -e "${RED}${BOLD}✗ Runtime Error (RTE)${NC} — Segmentation Fault"
elif [ $EXIT_CODE -eq 134 ] || [ $EXIT_CODE -eq 6 ]; then
    echo -e "${RED}${BOLD}✗ Runtime Error (RTE)${NC} — Aborted (assertion failed)"
elif [ $EXIT_CODE -eq 136 ] || [ $EXIT_CODE -eq 8 ]; then
    echo -e "${RED}${BOLD}✗ Runtime Error (RTE)${NC} — Floating point exception"
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

exit $EXIT_CODE
