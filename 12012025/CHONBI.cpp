#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("CHONBI.INP", "r", stdin);
    freopen("CHONBI.OUT", "w", stdout);

    int n, m;
    if (cin >> n >> m) {
        // pair: first là số bi trong 1 hộp (b_i), second là số hộp (a_i)
        vector<pair<int, int>> boxes(m);
        for (int i = 0; i < m; ++i) {
            cin >> boxes[i].second >> boxes[i].first;
        }

        // Sắp xếp giảm dần theo số bi trong hộp
        sort(boxes.rbegin(), boxes.rend());

        long long total_balls = 0;
        for (int i = 0; i < m && n > 0; ++i) {
            int take = min(n, boxes[i].second); // Số hộp có thể lấy
            total_balls += 1LL * take * boxes[i].first; // Dùng 1LL để tránh tràn số
            n -= take;
        }

        cout << total_balls << "\n";
    }
    return 0;
}