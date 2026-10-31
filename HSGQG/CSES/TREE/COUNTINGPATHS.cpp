#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define in insert
#define task "task"
using namespace std;

const int N = 2e5+20;
vector<int> adj[N];
int high[N];
int par[N][17];
int f[N];
int up = 0;
int n,m;

int lca(int u,int v)
{
    if(high[u] < high[v]) swap(u,v);
    // high[u] > high[v]
    for(int i=16;i>=0;i--)
    {
        if(par[u][i]!=-1)
        {
            if(high[par[u][i]] >= high[v]) u=par[u][i];
        }
    }
    if(u==v) return u;
    for(int i=16;i>=0;i--)
    {
        if(par[u][i]!=-1 && par[v][i]!=-1)
        {
            if(par[u][i] != par[v][i]) 
            {
                u = par[u][i];
                v = par[v][i];
            }
        }
    }
    return par[u][0];
}

void preDfs(int u,int p)
{
    for(int v:adj[u])
    {
        if(v==p) continue;
        par[v][0] = u;
        high[v] = high[u] + 1;
        preDfs(v,u);
    }
}

void dfs(int u,int p)
{
    for(int v:adj[u])
    {
        if(v==p) continue;
        dfs(v,u);
        f[u] += f[v];
    }
}


void solve()
{
    cin>>n>>m;
    for(int i=1;i<n;i++)
    {
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    high[1] = 1;
    preDfs(1,0);
    for(int j=1;j<=16;j++)
    {
        for(int i=1;i<=n;i++)
        {
            if(par[i][j-1]!=-1)
            {
                par[i][j] = par[par[i][j-1]][j-1];
            }
        }
    }
    for(int i=1;i<=m;i++)
    {
        int u,v; cin>>u>>v;
        if(high[u] > high[v]) swap(u,v);
        // high[v] > high[u]
        int ances = lca(u,v);
        //cout<<ances<<' '<<u<<' '<<v<<'\n';
        f[v]++;
        if(par[ances][0] == -1) f[0]--;
        else f[par[ances][0]]--;
        if(ances!=u)
        {
            f[ances]--;
            f[u]++;
        }     
    }
    dfs(1,-1);
    for(int i=1;i<=n;i++) cout<<f[i]<<' ';
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
    memset(par,-1,sizeof(par));
    memset(f,0,sizeof(f));
    while(t--) solve();
}