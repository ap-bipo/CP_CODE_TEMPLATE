#include<bits/stdc++.h>
using namespace std;

#define ll long long

const bool Multitest = 0;
const int N = 2e5 + 10;
int n, q, a[N]; vector<int> adj[N];
int sz[N];
int tin[N], tout[N], up = 0, curId = 1, par[N], id[N], head[N];
struct Query
{
    int id, a, b;
    Query() { }
    Query(int _id, int _a, int _b) : id(_id), a(_a), b(_b) { }
}; Query qr[N];

struct SegmentTree
{
    int n, t[4 * N];
    void update(int id, int l, int r, int pos, int val)
    {
        if(r < pos || pos < l) return;
        if(l == r) return t[id] = val, void();

        int mid = (l + r) >> 1;

        update(id * 2, l, mid, pos, val);
        update(id * 2 + 1, mid + 1, r, pos, val);

        t[id] = max(t[id * 2], t[id * 2 + 1]);
    }

    int get(int id, int l, int r, int u, int v)
    {
        if(r < u || v < l) return -1e9;
        if(u <= l && r <= v) return t[id];

        int mid = (l + r) >> 1;

        int L = get(id * 2, l, mid, u, v);
        int R = get(id * 2 + 1, mid + 1, r, u, v);
        return max(L, R);
    }

    void update(int u, int v) { return update(1, 1, n, u, v); }
    int get(int l, int r) { return get(1, 1, n, l, r); }
}; SegmentTree st;

bool cmpAdj(int u, int v) { return sz[u] > sz[v]; }
void preDfs(int u, int p)
{
    sz[u] = 1;
    for(int i = 0 ; i < adj[u].size() ; i++)
    {
        int v = adj[u][i];
        if(v == p) continue;
        preDfs(v, u);
        sz[u] += sz[v];
    }
}
void dfs(int u, int p)
{
    tin[u] = ++up; id[u] = curId; par[u] = p;
    if(head[id[u]] == 0) head[id[u]] = u;

    for(int i = 0, f = 0 ; i < adj[u].size() ; i++)
    {
        int v = adj[u][i];
        if(v == p) continue;
        curId += (f != 0); f++;
        dfs(v, u);
    }

    tout[u] = up;
}

int get(int x, int y) // get_HLD
{
    int ans = -1e9;
    while(head[id[x]] != head[id[y]])
    {
        if(id[x] < id[y]) swap(x, y);
        int z = head[id[x]];
        ans = max(ans, st.get(tin[z], tin[x]));
        x = par[z];

    }
    if(tin[x] < tin[y]) swap(x, y);
    return ans = max(ans, st.get(tin[y], tin[x]));
}

void work()
{
    cin >> n >> q;
    for(int i = 1 ; i <= n ; i++) cin >> a[i];
    for(int i = 1 ; i < n ; i++)
    {
        int u, v;   cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i = 1 ; i <= q ; i++) cin >> qr[i].id >> qr[i].a >> qr[i].b;

    st.n = n;
    preDfs(1, 0); for(int i = 1 ; i <= n ; i++) sort(adj[i].begin(), adj[i].end(), cmpAdj);
    dfs(1, 0); for(int i = 1 ; i <= n ; i++) st.update(tin[i], a[i]);

    for(int i = 1 ; i <= q ; i++)
    {
        int id = qr[i].id;
        if(id == 1)
        {
            int x = qr[i].a, y = qr[i].b;
            st.update(tin[x], y);
        }
        else
        {
            int x = qr[i].a, y = qr[i].b;
            cout << get(x, y) << '\n';
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    if(fopen("code.inp", "r"))
    {
        freopen("code.inp", "r", stdin);
        freopen("code.out", "w", stdout);
    }
    int q = 1;
    if(Multitest)   cin >> q;
    while(q--) work();
}
