#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pb push_back
#define task "task"
using namespace std;

const int N = 200005;

int n, m, q;
ll s_[N];
int par_[N], sz_[N];
ll mx_[N], ans_[N];
bool vis_[N];

vector<pair<int, ll>> adj_[N];
vector<ll> val_;

struct Edge {
    ll w;
    int u, v;
};

struct Query {
    ll x;
    int v, k, id;
};

vector<Edge> edges_;
vector<Query> queries_;
int q_cnt = 0, edge_ptr = 0;

int findSet(int u) {
    return par_[u] == u ? u : par_[u] = findSet(par_[u]);
}

void unionSet(int u, int v) {
    u = findSet(u);
    v = findSet(v);
    if (u != v) {
        if (sz_[u] < sz_[v]) swap(u, v);
        par_[v] = u;
        sz_[u] += sz_[v];
        mx_[u] = max(mx_[u], mx_[v]); 
    }
}

void dfs(int u, ll x) {
    vis_[u] = true;
    val_.pb(s_[u]);
    for (auto &e : adj_[u]) {
        if (!vis_[e.fi] && e.se <= x) {
            dfs(e.fi, x);
        }
    }
}

void solve() {
    if (!(cin >> n >> m >> q)) return;

    for (int i = 1; i <= n; i++) {
        cin >> s_[i];
    }

    for (int i = 1; i <= m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj_[u].pb({v, w});
        adj_[v].pb({u, w});
        edges_.pb({w, u, v});
    }

    if (n <= 1000 && m <= 1000 && q <= 1000) {
        while (q--) {
            int type;
            cin >> type;
            if (type == 1) {
                int i; ll v;
                cin >> i >> v;
                s_[i] = v;
            } else {
                int v, k; ll x;
                cin >> v >> x >> k;
                for (int i = 1; i <= n; i++) vis_[i] = false;
                val_.clear();
                dfs(v, x);
                if ((int)val_.size() < k) cout << -1 << "\n";
                else {
                    sort(val_.rbegin(), val_.rend());
                    cout << val_[k - 1] << "\n";
                }
            }
        }
    } 
    else {
        for (int i = 1; i <= q; i++) {
            int type;
            cin >> type;
            if (type == 1) {
                int u; ll v;
                cin >> u >> v;
            } else {
                int v, k; ll x;
                cin >> v >> x >> k;
                q_cnt++;
                queries_.pb({x, v, k, q_cnt});
            }
        }

        sort(edges_.begin(), edges_.end(), [](const Edge &a, const Edge &b) {
            return a.w < b.w;
        });
        sort(queries_.begin(), queries_.end(), [](const Query &a, const Query &b) {
            return a.x < b.x;
        });

        for (int i = 1; i <= n; i++) {
            par_[i] = i;
            sz_[i] = 1;
            mx_[i] = s_[i];
        }
        for (auto &qr : queries_) {
            while (edge_ptr < m && edges_[edge_ptr].w <= qr.x) {
                unionSet(edges_[edge_ptr].u, edges_[edge_ptr].v);
                edge_ptr++;
            }
            int r = findSet(qr.v);
            if (sz_[r] < qr.k) ans_[qr.id] = -1;
            else ans_[qr.id] = mx_[r];
        }
        for (int i = 1; i <= q_cnt; i++) {
            cout << ans_[i] << "\n";
        }
    }
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    if (fopen(task".INP", "r")) {
        freopen(task".INP", "r", stdin);
        freopen(task".OUT", "w", stdout);
    }

    int t = 1;
    while (t--) solve();

    return 0;
}