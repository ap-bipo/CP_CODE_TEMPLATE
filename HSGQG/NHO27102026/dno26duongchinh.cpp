#include<bits/stdc++.h>
#define ll long long 
#define pb push_back
#define fi first
#define se second
#define task "task"
using namespace std;

const int N = 2e5 + 20;
const ll INF = 1e18;
const ll MOD1 = 1234567891;
const ll MOD2 = 1e9 + 7;

struct Road {
    int u, v;
    ll w;
} edges[N];

vector<pair<int, ll>> adj1[N],adj2[N];
ll d1[N],d2[N];
ll cnt1_a[N],cnt1_b[N];
ll cnt2_a[N],cnt2_b[N];
int n,m,st,ed;

struct edge
{
    int v;
    ll d;
};

struct cmp
{
    bool operator()(edge a, edge b)
    {
        return a.d > b.d;
    }
};

void dijkstra(int st, vector<pair<int, ll>> adj[], ll res[], ll cnt_a[], ll cnt_b[])
{
    for (int i=1;i<=n;i++)
    {
        res[i] = INF;
        cnt_a[i] = 0;
        cnt_b[i] = 0;
    }
    res[st] = 0;
    cnt_a[st] = 1;
    cnt_b[st] = 1;

    priority_queue<edge, vector<edge>, cmp> pq;
    pq.push({st, 0});

    while (!pq.empty())
    {
        edge top = pq.top();
        pq.pop();
        int u = top.v;
        ll d = top.d;
        if (d > res[u]) continue;
        for (pair<int, ll> v : adj[u])
        {
            if (res[v.fi]>res[u]+v.se)
            {
                res[v.fi] = res[u] + v.se;
                cnt_a[v.fi] = cnt_a[u];
                cnt_b[v.fi] = cnt_b[u];
                pq.push({v.fi, res[v.fi]});
            } 
            else if (res[v.fi]==res[u]+v.se) 
            {
                cnt_a[v.fi] = (cnt_a[v.fi] + cnt_a[u]) % MOD1;
                cnt_b[v.fi] = (cnt_b[v.fi] + cnt_b[u]) % MOD2;
            }
        }
    }
}

void solve()
{
    cin>>n>>m>>st>>ed;
    for (int i=1;i<=m;i++)
    {
        int u, v;
        ll k;
        cin >> u >> v >> k;
        edges[i] = {u, v, k};
        adj1[u].pb({v, k});
        adj2[v].pb({u, k});
    }
    dijkstra(st, adj1, d1, cnt1_a, cnt1_b);
    dijkstra(ed, adj2, d2, cnt2_a, cnt2_b);

    ll best = d1[ed];

    for (int i = 1; i <= m; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;
        ll w = edges[i].w;
        if (d1[u] == INF || d2[v] == INF)
        {
            cout << -1 << "\n";
            continue;
        }
        if (d1[u] + w + d2[v] == best)
        {
            ll ways1=(cnt1_a[u]*cnt2_a[v])%MOD1;
            ll ways2=(cnt1_b[u]*cnt2_b[v])%MOD2;
            if (ways1==cnt1_a[ed] && ways2==cnt1_b[ed])
            {
                cout << 0 << "\n";
                continue;
            }
        }
        ll w_new = (best - 1)-d1[u]-d2[v];
        if(w_new >= 1) cout<<w-w_new<<'\n';
        else cout<<-1<<'\n';
    }
}

signed main() {
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