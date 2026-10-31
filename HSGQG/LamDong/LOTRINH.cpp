#include<bits/stdc++.h>
#define ll long long 
#define pb push_back
#define task "LOTRINH"
using namespace std;

const int N = 5005;
const ll MOD = 1e9+7;

int n, m;
int a[N];
vector<int> adj[N];
int d[N][N];
vector<int> lv[N];
ll f[N];  
ll f_sum[N];  

void bfs(int st)
{
    for(int i = 1; i <= n; i++) d[st][i]=-1;
    queue<int> q;
    q.push(st);
    d[st][st] = 0;
    while(!q.empty())
    {
        int u = q.front(); 
        q.pop();
        for(int v : adj[u])
        {
            if(d[st][v] == -1)
            {
                d[st][v] = d[st][u]+1;
                q.push(v);
            }
        }
    }
}

void solve()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        lv[a[i]].pb(i);
    }
    for(int i = 1; i < n; i++)
    {
        int u, v; 
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for(int i=1;i<=n;i++) bfs(i);
    f[1]=1;
    f_sum[1]=0;
    for(int k=1;k<m;k++)
    {
        for(int v : lv[k+1])
        {
            f[v]=0;
            f_sum[v]=0;
            for(int u : lv[k])
            {
                if(f[u] == 0) continue;
                f[v] = (f[v]+f[u])%MOD;
                ll delta = (f[u]*d[u][v])%MOD;
                f_sum[v] = (f_sum[v]+f_sum[u]+delta)%MOD;
            }
        }
    }
    cout << f_sum[n] << '\n';
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
    int t = 1;
    while(t--) solve();
}