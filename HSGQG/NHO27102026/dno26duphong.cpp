#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define in insert
#define task "task"
using namespace std;

const int N = 1e6 + 20;
const int M = 20;
const ll MOD = 1e9 + 7;
const ll INF = 1e18;

int n,m;
vector<pair<int,ll>> adj[N];
int par[N];
int sz[N];
pair<int,ll> par_mst[N];
bool visited[N];
int up = 0;
int tin[N];
int tout[N];

struct segment 
{
    vector<ll> st;
    segment(int _sz) : st(4*_sz+5){}
    void upd(int id,int l,int r,int i,ll x)
    {
        if(r<i || i<l) return;
        if(l==r) 
        {
            st[id] = max(st[id],x);
            return ;
        }
        int mid = (l+r)>>1;
        upd(id*2,l,mid,i,x);
        upd(id*2+1,mid+1,r,i,x);
        st[id] = max(st[id*2],st[id*2+1]);
    }
    ll get(int id,int l,int r,int u,int v)
    {
        if(r<u || v<l) return 0;
        if(u<=l&&r<=v) return st[id];
        int mid = (l+r)>>1;
        return max(get(id*2,l,mid,u,v),get(id*2+1,mid+1,r,u,v));
    }
} st(N);

struct edge
{
    int u,v;
    ll x;
};
vector<edge> edges;
vector<edge> q;

struct cmp
{
    bool operator()(edge a,edge b)
    {
        return a.x < b.x;
    }
};

int root(int u)
{
    if(u==par[u]) return u;
    else return root(par[u]);
}

void ghep(int u,int v)
{
    u = root(u);
    v = root(v);
    if(u!=v)
    {
        if(sz[u] < sz[v]) swap(u,v);
        //sz[u] > sz[v]
        par[v] = u;
        sz[u] += sz[v];
    }
}

void dfs_euler(int u,int p)
{
    tin[u] = ++up;
    for(pair<int,ll> v:adj[u])
    {
        if(v.fi == p) continue;
        dfs_euler(v.fi,u);
    }  
    tout[u] = up;
}

void dfs(int u,int p)
{
    for(pair<int,ll> v: adj[u])
    {
        if(v.fi == p) continue;
        dfs(v.fi,u);
        q.pb({v.fi,u,v.se});
    }
}



void solve()
{
    memset(visited,false,sizeof(visited));
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        ll z;
        int u,v; cin>>u>>v>>z;
        edges.pb({u,v,z});
    }
    for(int i=1;i<=n;i++)
    {
        sz[i] = 1;
        par[i] = i;
    }

    sort(edges.begin(),edges.end(),cmp());
    for(edge x:edges)
    {
        if(root(x.u) == root(x.v)) continue;
        else
        {
            ghep(x.u,x.v);
            adj[x.u].pb({x.v,x.x});
            adj[x.v].pb({x.u,x.x});
            cout<<x.u<<' '<<x.v<<'\n';
        }
    }
    adj[6].pb({7,10});
    adj[7].pb({6,10});
    adj[6].pb({9,10});
    adj[9].pb({6,10});
    adj[10].pb({9,10});
    adj[9].pb({10,10});
    adj[7].pb({8,10});
    adj[8].pb({7,10});
    adj[2].pb({6,10});
    adj[6].pb({2,10});
    dfs_euler(1,0);
    dfs(1,0);
    for(edge i:q) 
    {
        cout<<i.u<<' '<<i.v<<' '<<i.x<<'\n';
    }


    
    

}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen(task".INP", "r"))
    {
        freopen(task".INP", "r", stdin);
        freopen(task".OUT", "w", stdout);
    }
    solve();
}