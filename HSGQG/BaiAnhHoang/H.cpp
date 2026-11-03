#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "H"
#define fi first
#define in insert
#define se second
using namespace std;

const int N = 1502;
int up=0;
vector<int> adj[N];
bool visited[N];
int num[N];
int low[N];
bool del[N];
int conv[N];
stack<int> scc;
int num_scc = 0;
int id[N];
vector<int> topo_list;
pair<int,int> edges[N*N];
set<pair<int,int>> spec;
vector<pair<int,int>> res;
bitset<N> op[N];

void dfs(int u)
{
    num[u] = low[u] = ++up;
    scc.push(u);
    for(int v:adj[u])
    {
        if(del[v]) continue;
        if(!num[v])
        {
            dfs(v);
            low[u] = min(low[u],low[v]);
        } else low[u] = min(low[u],num[v]);
    }
    if(low[u] == num[u])
    {
        num_scc++;
        int v;
        do
        {
            v = scc.top();
            id[v] = num_scc;
            conv[num_scc] = v;
            scc.pop();
            del[v] = true;
        }while(v!=u);
        //cout<<'\n';
    }
}

void topo(int u)
{
    op[u].set(u);
    visited[u] = true;
    for(int v:adj[u])
    {
        if(visited[v] == false) 
        {
            topo(v);
        }
        op[u] |= op[v];
    }
    topo_list.push_back(u);
}

void solve()
{
    int n,m; cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        del[i] = false;
        visited[i] = false;
    }
    for(int i=1;i<=m;i++) 
    {
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        edges[i] = {u,v};
    }
    for(int i=1;i<=n;i++) if(!num[i]) dfs(i);
    for(int i=1;i<=n;i++) adj[i].clear();
    for(int i=1;i<=m;i++)
    {
        int u = edges[i].fi;
        int v = edges[i].se;
        if(u==v) continue;
        //cout<<u<<' '<<v<<'\n';
        spec.in({id[u],id[v]});
    }
    for(pair<int,int> x:spec) adj[x.fi].pb(x.se);
    for(int i=1;i<=n;i++) 
    {
        if(num[i] == 0)
        {
            id[i] = ++num_scc;
            conv[num_scc] = i;
        }
        int u = id[i];
        //cout<<i<<' '<<u<<'\n';
        if(visited[u] == false) topo(u);
    }
    reverse(topo_list.begin(),topo_list.end());
    for(int i=0;i<(int)topo_list.size();i++)
    {
        for(int j=(int)topo_list.size()-1;j>=i+1;j--)
        {
            int u = topo_list[i];
            int v = topo_list[j];
            if(!op[u][v])
            {
                // u da den dc v
                op[u] |= op[v];
                res.pb({conv[u],conv[v]});
            }
        }
    }
    for(int i = (int)topo_list.size()-1;i>=1;i--) res.pb({conv[topo_list[i]],conv[topo_list[i-1]]});
    cout<<(int)res.size()<<'\n';
    for(pair<int,int> x:res) cout<<x.fi<<' '<<x.se<<'\n';
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