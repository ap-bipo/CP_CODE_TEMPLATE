#include<bits/stdc++.h>
#define ll long long
#define in insert
#define pb push_back
#define task "DISTINCTCOLOR"
using namespace std;

const int N = 2e5+20;

int par[N];
int a[N];
int col[N];
int n;
vector<int> adj[N];
int res[N];
set<int> sz[N];

int root(int u)
{
    if(u == par[u]) return u;
    else return root(par[u]);
}

void ghep(int u,int v)
{
    u = root(u);
    v = root(v);
    if(u!=v)
    {
        if((int)sz[u].size() < (int)sz[v].size()) swap(u,v);
        // sz[u] > sz[v];
        par[v] = u;
        for(int x:sz[v]) sz[u].in(x);
    }
}

void dfs(int u,int p)
{
    for(int v:adj[u])
    {
        if(v==p) continue;
        dfs(v,u);
        ghep(v,u);
    }
    res[u] = (int)sz[root(u)].size();
}


void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++)
    {
        sz[i].in(a[i]);
        par[i] = i;
    }

    for(int i=1;i<n;i++)
    {
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++) cout<<res[i]<<' ';

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