#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "task"
using namespace std;

const int N = 2e5+20;
int n;
int f[N];
int res[N];
vector<int> adj[N];

void depth(int u,int p)
{
    for(int v:adj[u])
    {
        if(v==p) continue;
        f[v] = f[u]+1;
        depth(v,u);
    }
}

void dfs(int u,int p)
{
    int best = -1;
    int se_best = -1;
    int cnt_child = 0;
    for(int v:adj[u])
    {
        if(v==p) continue;
        cnt_child++;
    }
    if(cnt_child>=2)
    {
        for(int v:adj[u])
        {
            if(v==p) continue;
            dfs(v,u);
            if(f[v] > best)
            {
                int tmp = best;
                best = f[v];
                se_best = tmp;
            }else if(f[v] > se_best) se_best = f[v];
        }
        res[u] = max(res[u], best - f[u] + se_best - f[u]);
        f[u] = max(f[u],best);
    }else
    {
        for(int v:adj[u])
        {
            if(v==p) continue;
            dfs(v,u);
            res[u] = max(res[u], f[v] - f[u]);
            f[u] = max(f[u],f[v]);
        }
    }

}

void solve()
{
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    f[1] = 1;
    depth(1,0);
    dfs(1,0);
    int ans=0;
    for(int i=1;i<=n;i++) ans = max(ans,res[i]);
    cout<<ans;
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
    int t=1;
    while(t--) solve();
}