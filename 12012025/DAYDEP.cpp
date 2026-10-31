#include <iostream>
#include <vector>

using namespace std;

// Khai báo mảng đếm toàn cục để tránh lỗi tràn Stack Memory
int cnt[1000005]; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("DAYDEP.INP", "r", stdin);
    freopen("DAYDEP.OUT", "w", stdout);

    int n;
    if (cin >> n) {
        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            if (a <= 1000000) {
                cnt[a]++;
            }
        }

        int removals = 0;
        // Xử lý các số từ 0 đến 10^6
        for (int i = 0; i <= 1000000; ++i) {
            if (cnt[i] > 0) {
                if (cnt[i] >= i) {
                    // Xóa phần thừa
                    removals += (cnt[i] - i);
                } else {
                    // Không đủ số lượng, bắt buộc xóa hết
                    removals += cnt[i];
                }
            }
        }

        cout << removals << "\n";
    }
    return 0;
}