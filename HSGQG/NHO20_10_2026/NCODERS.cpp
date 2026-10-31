#include<bits/stdc++.h>
#define ll long long
#define task "NCODERS"
using namespace std;

const int N = 50005;
const ll INF = 1e18;

int n, m, p;
vector<pair<int,ll>> adj[N];
ll dis[N];

void f(int st)
{
    for(int i = 1; i <= n; i++) dis[i] = INF;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dis[st] = 0;
    pq.push({0, st});
    
    while(!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if(d > dis[u]) continue;
        for(auto edge : adj[u])
        {
            int v = edge.first;
            ll w = edge.second;
            if(dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
            }
        }
    }
}

void solve() {
    if (!(cin >> n >> m >> p)) return;
    
    for(int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    f(1);
    for(int i = 1; i <= p; i++)
    {
        int u,v;
        cin>>u>>v;
        cout<<dis[u]+dis[v]<<'\n';
    }
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if(fopen(task".INP","r"))
    {
        freopen(task".INP","r",stdin);
        freopen(task".OUT","w",stdout);
    }
    solve();
}