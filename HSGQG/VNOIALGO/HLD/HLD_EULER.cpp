#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "HLD_EULER"
using namespace std;

const int N = 2e5+20;

int chainID[N];
int chainHead[N];
int curChain = 1;
int up = 0;
int tin[N];
int tout[N];
ll val[N];
int par[N];
int sz[N];
vector<int> adj[N];
int n,q;

struct segment
{
    vector<ll> st;
    segment(int _sz) : st(4*_sz+5){}

    void upd(int id,int l,int r,int i,ll x)
    {
        if(r<i || i<l) return ;
        if(l==r)
        {
            st[id] = x;
            return ;
        }
        int mid = (l+r) >> 1;
        upd(id*2,l,mid,i,x);
        upd(id*2+1,mid+1,r,i,x);
        st[id] = max(st[id*2], st[id*2+1]);
    }

    ll get(int id,int l,int r,int u,int v)
    {
        if(r<u || v<l) return -1e18;
        if(u<=l&&r<=v) return st[id];
        int mid = (l+r)>>1;
        return max(get(id*2,l,mid,u,v), get(id*2+1,mid+1,r,u,v));
    }
} st(N);

void dfs(int u,int p)
{
    sz[u]=1;
    for(int v:adj[u])
    {
        if(v==p) continue;
        dfs(v,u);
        sz[u] += sz[v];
        par[v] = u;
    }
}


void hld(int u,int p)
{
    tin[u] = ++up;
    if(chainHead[curChain] == 0) chainHead[curChain] = u;
    chainID[u] = curChain;
    int nxt = 0;
    for(int v:adj[u])
    {
        if(v==p) continue;
        if(nxt == 0 || sz[v] > sz[nxt]) nxt = v;
    }
    if(nxt != 0) hld(nxt,u);
    for(int v:adj[u])
    {
        if(v!=p && v!=nxt)
        {
            curChain++;
            hld(v,u);
        }
    }
    tout[u] = up;
}

ll get(int u,int v)
{
    ll ans = -1e18;
    while(chainID[u] != chainID[v])
    {
        if(tin[u] < tin[v]) swap(u,v); // u nam duoi
        int z = chainHead[chainID[u]];
        ans = max(ans, st.get(1,1,n,tin[z],tin[u]));
        u = par[z];
    }
    if(tin[u] < tin[v]) swap(u,v);
    ans = max(ans,st.get(1,1,n,tin[v],tin[u]));
    return ans;
}

void solve()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>val[i];
    for(int i=1;i<n;i++)
    {
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1,0);
    hld(1,0);
    for(int i=1;i<=n;i++) st.upd(1,1,n,tin[i],val[i]);
    while(q--)
    {
        int t; cin>>t;
        if(t==1)
        {
            ll v;
            int u; cin>>u>>v;
            st.upd(1,1,n,tin[u],v);
        }
        else
        {
            int u,v;
            cin>>u>>v;
            cout<<get(u,v)<<' ';
        }
        
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
    int t=1;
    while(t--) solve();
}