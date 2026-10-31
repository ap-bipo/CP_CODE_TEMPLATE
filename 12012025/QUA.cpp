#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Tối ưu hóa I/O trong C++
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("QUA.INP", "r", stdin);
    freopen("QUA.OUT", "w", stdout);

    int n;
    if (cin >> n) {
        vector<int> winners;
        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            // Kiểm tra số hoàn thiện trong phạm vi 3 * 10^5
            if (a == 6 || a == 28 || a == 496 || a == 8128) {
                winners.push_back(a);
            }
        }

        cout << winners.size() << "\n";
        for (int i = 0; i < winners.size(); ++i) {
            cout << winners[i] << (i == winners.size() - 1 ? "" : " ");
        }
    }
    return 0;
}