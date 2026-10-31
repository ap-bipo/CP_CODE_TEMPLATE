#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "task"
using namespace std;

const int N = 2e5+20;
int n;
int high[N];
int res[N];
int f[N];
vector<int> adj[N];

void depth(int u,int p)
{
    for(int v:adj[u])
    {
        if(v==p) continue;
        f[v] = f[u]+1;
        high[v] = high[u]+1;
        depth(v,u);
    }
}

void dfs2(int u,int p)
{
    for(int v:adj[u])
    {
        if(v==p) continue;
        dfs2(v,u);
        f[u] = max(f[u],f[v]);
    }
}

void dfs(int u,int p,int max_cluster)
{
    int best = 0;
    int se_best = 0;
    int cnt_child=0;
    for(int v:adj[u])
    {
        if(v==p) continue;
        if(f[v] > best)
        {
            int tmp = best;
            best = f[v];
            se_best = tmp;
        }else if(f[v]>se_best) se_best = f[v];
        cnt_child++;
    }
    if(cnt_child >= 2)
    {
        for(int v:adj[u])
        {
            if(v==p) continue;
            if(f[v] == best)
            {
                res[v] = max(f[v]-high[v],high[v] + max(max_cluster, se_best-high[u]));
                dfs(v,u,max(max_cluster, se_best-high[u]));
            }
            else
            {
                res[v] = max(f[v]-high[v],high[v] + max(max_cluster, best-high[u]));
                dfs(v,u,max(max_cluster, best-high[u]));
            }
        }
    }else
    {
        for(int v:adj[u])
        {
            if(v==p) continue;
            res[v] = max(f[v]-high[v],high[v] + max_cluster);
            dfs(v,u,max_cluster);
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
    high[1] = 0;
    depth(1,0);
    dfs2(1,0);
    dfs(1,0,0);
    for(int i:adj[1]) res[1] = max(res[1],f[i]);
    int ans=0;
    for(int i=1;i<=n;i++) cout<<res[i]<<' ';
    // cout<<ans;
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