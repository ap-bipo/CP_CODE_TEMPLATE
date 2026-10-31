/*
    SU DUNG TOPO + XET EDGE CASES
*/
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define se second
#define fi first
#define task "INCPATH"
using namespace std;

const ll N = 1e3+20;
vector<int> adj[N];
vector<int> adj_comp[N];
pair<int,int> edge[N];
int visited[N];
bool found = false;
bool ans = true;
int res[N];

void dfs(int u,pair<int,int> del)
{
    if(found == true) return ;
    visited[u] = true;
    if(u == del.fi)
    {
        found = true;
        return ;
    }
    for(int v:adj[u])
    {
        if(v == del.se) continue;
        if(visited[v]==true) continue;
        dfs(v,del);
    }
}

stack<int> ord;

void topo(int u)
{
    visited[u] = 1;
    for (auto v : adj_comp[u])
    {
        if (visited[v] == 1)
        {
            ans = false;
            return;
        }
        if(!visited[v])
            topo(v);
    }
    ord.push(u);
    visited[u] = 2;
}

void solve()
{
    int n,m; cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        edge[i] = {u,v};
    }
    for(int i=1;i<=m;i++)
    {
        if(edge[i].se == 1) continue;
        for(int j=1;j<=n;j++) visited[j] = false;
        found = false;
        dfs(1,edge[i]);
        if(found == true)
        {
            // van di dc 
            adj_comp[edge[i].fi].pb(edge[i].se);
        }
    }
    for(int i=1;i<=n;i++) visited[i] = false;
    for(int i=1;i<=n;i++)
    {
        if(!visited[i]) topo(i);
    }
    if(ans == false)
    {
        cout<<-1;
        return ;
    }
    int cnt = 0;
    while(!ord.empty())
    {
        int idx = ord.top();
        res[idx] = ++cnt;
        ord.pop();
    }
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