#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "PATHQUERIES"
using namespace std;

const int N = 2e5+20;

struct segment
{
    vector<ll> st;
    segment(int _sz) : st(4*_sz+5){}
    void upd(int id,int l,int r,int i,ll x)
    {
        if(r<i || i<l) return;
        if(l==r)
        {
            st[id] += x;
            return ;
        }
        int mid = (l+r)>>1;
        upd(id*2,l,mid,i,x);
        upd(id*2+1,mid+1,r,i,x);
        st[id] = st[id*2] + st[id*2+1];
    }
    ll get(int id,int l,int r,int u,int v)
    {
        if(v<l || r<u) return 0;
        if(u<=l&&r<=v) return st[id];
        int mid = (l+r)>>1;
        return get(id*2,l,mid,u,v) + get(id*2+1,mid+1,r,u,v);
    }
} st(N);

vector<int> adj[N];

int n,q;
ll a[N];
int tin[N];
int tout[N];
int up = 0;

void dfs(int u,int p)
{
    tin[u] = ++up;
    for(int v : adj[u])
    {
        if(v==p) continue;
        dfs(v,u);
    }
    tout[u] = up;
}

void upd(int u,ll x)
{
    ll delta = x-a[u];
    st.upd(1,1,up,tin[u],delta);
    st.upd(1,1,up,tout[u]+1,-delta);
    a[u] = x;
}

ll get(int u) { return st.get(1,1,up,tin[1],tin[u]); }

void solve()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++)
    {
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1,0);
    up++; // i think it's important

    for(int i=1;i<=n;i++)
    {
        st.upd(1,1,up,tin[i],a[i]);
        st.upd(1,1,up,tout[i]+1,-a[i]);
    }

    while(q--)
    {
        int t; cin>>t;
        if(t==1)
        {
            int u;
            ll x;
            cin>>u>>x;
            upd(u,x);
        }else
        {
            int u; cin>>u;
            cout<<get(u)<<'\n';
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