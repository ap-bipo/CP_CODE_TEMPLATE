#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "htgt"
using namespace std;


const int N = 5e5+20;

vector<int> adj[N];
int tin[N];
int tout[N];
ll sz[N];
int up=0;

struct segment
{
    vector<ll> st;
    segment(int _sz) : st(4*_sz+5){}
    void upd(int id,int l,int r,int i,int x)
    {
        if(r<i || i<l) return;
        if(l==r) 
        {
            st[id]+=x;
            return ;
        }
        int mid = (l+r)>>1;
        upd(id*2,l,mid,i,x);
        upd(id*2+1,mid+1,r,i,x);
        st[id] = st[id*2] + st[id*2+1];
    }
    ll get(int id,int l,int r,int u,int v)
    {
        if(r<u || v<l) return 0;
        if(u<=l&&r<=v) return st[id];
        int mid = (l+r)>>1;
        return get(id*2,l,mid,u,v) + get(id*2+1,mid+1,r,u,v);
    }
};
int n;

void dfs(int u,int p)
{
    sz[u] = 1;
    tin[u] = ++up;
    for(int v:adj[u])
    {
        if(v==p) continue;
        dfs(v,u);
        sz[u] += sz[v];
    }
    tout[u] = up;
}

void solve()
{
    cin>>n;
    segment st(n);
    for(int i=1;i<n;i++)
    {
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1,0);
    ll ans = 0;
    for(int i=1;i<=n;i++)
    {
        ll less = 0;
        ll great = 0;
        for(int v:adj[i])
        {
            if(tin[v] < tin[i]) continue;
            ll sub = st.get(1,1,n,tin[v],tout[v]);
            less += sub;
            great += sz[v]-sub;
            ans -= (sub)*(sz[v]-sub);
        }
        ans -= (i-1-less) * (n-i-great);
        ans += 1LL * (n-i) * (i-1);
        st.upd(1,1,n,tin[i],1);
    }
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