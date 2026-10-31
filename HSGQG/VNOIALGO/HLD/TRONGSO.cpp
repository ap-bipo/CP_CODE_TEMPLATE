// DOWN(ID,L,R) ĐỂ DƯỚI MID


#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "TRONGSO"
using namespace std;


const int N = 2e4+20;

vector<int> adj[N];
int n,q;
int par[N];
int pos[N];
int a[N];
int sz[N];
int chainID[N];
int high[N];
int chainHead[N];
int curChain = 1;
int curPos = 1;

struct edge
{
    int u,v;
    ll d;
} edges[N];

struct lazy
{
    struct node
    {
        ll val;
        ll lazy;
        node() : val(0), lazy(1){}
    };
    vector<node> st;
    lazy(int _sz) : st(4*_sz+5){}

    void down(int id,int l,int r)
    {
        int mid = (l+r) >> 1;
        int delta = st[id].lazy;
        if(delta == 1) return;
        st[id*2].lazy *= delta;
        st[id*2].val *= delta;
        st[id*2+1].lazy *= delta;
        st[id*2+1].val *= delta;
        st[id].lazy = 1;
    }

    void upd1(int id,int l,int r,int i,ll x)
    {
        
        if(r<i || i<l) return;
        if(l==r)
        {
            st[id].val = x;
            return ;
        }
        int mid = (l+r)>>1;
        down(id,l,r);
        upd1(id*2,l,mid,i,x);
        upd1(id*2+1,mid+1,r,i,x);  
        st[id].val = st[id*2+1].val + st[id*2].val;
    }

    void upd2(int id,int l,int r,int u,int v)
    {
        
        if(r<u || v<l) return;
        if(u<=l&&r<=v)
        {
            st[id].val *= (-1);
            st[id].lazy *= (-1);
            return;
        }
        int mid = (l+r) >> 1;
        down(id,l,r);
        upd2(id*2,l,mid,u,v);
        upd2(id*2+1,mid+1,r,u,v);
        st[id].val = st[id*2+1].val + st[id*2].val;
    }

    ll get(int id,int l,int r,int u,int v)
    {
        if(r<u || v<l) return 0;
        if(u<=l && r<=v) return st[id].val;
        int mid = (l+r) >> 1;
        down(id,l,r);
        return get(id*2,l,mid,u,v) + get(id*2+1,mid+1,r,u,v);
    }
} st(N);


void dfs(int u,int z)
{
    sz[u] = 1;
    for(int v : adj[u])
    {
        if(v==z) continue;
        par[v] = u;
        high[v] = high[u] + 1;
        dfs(v,u);
        sz[u] += sz[v];
    }
}


void hld(int u,int z)
{
    if(chainHead[curChain] == 0) chainHead[curChain] = u;
    chainID[u] = curChain;
    pos[u] = curPos;
    a[curPos] = u;
    curPos++;
    int nxt = 0;
    for(int v : adj[u])
    {
        if(v!=z)
        {
            // trong chuoi canh nang
            if(nxt == 0 || sz[v] > sz[nxt]) nxt = v;
        }
    }
    // canh nang
    if(nxt != 0) hld(nxt,u);
    
    for(int v : adj[u])
    {
        if(v!=z && v!=nxt)
        {
            // canh nhe - them canh moi
            curChain++;
            hld(v,u);
        }
    }
}

int lca(int u,int v)
{
    while(chainID[u] != chainID[v])
    {
        if(chainID[u] > chainID[v]) u = par[chainHead[chainID[u]]];
        else v = par[chainHead[chainID[v]]];
    }
    if(high[u] < high[v]) return u;
    else return v;
}

void upd1(int u,int v, ll val)
{
    if(high[u] > high[v]) swap(u,v);
    st.upd1(1,1,n,pos[v],val);
}

void upd2(int u,int v)
{
    int ances = lca(u,v);
    ll sum = 0;
    while(chainID[u] != chainID[ances])
    {
        st.upd2(1,1,n,pos[chainHead[chainID[u]]], pos[u]);
        u = par[chainHead[chainID[u]]];
    }
    while(chainID[v] != chainID[ances])
    {
        st.upd2(1,1,n,pos[chainHead[chainID[v]]], pos[v]);
        v = par[chainHead[chainID[v]]];
    }
    if(u==v) return; // tranh pos[u]+1 -> pos[u];
    if(high[u] < high[v]) st.upd2(1,1,n,pos[u]+1,pos[v]);
    else st.upd2(1,1,n,pos[v]+1,pos[u]);
}  

ll query(int u,int v)
{
    int ances = lca(u,v);
    //cout<<u<<' '<<v<<' '<<ances<<'\n';
    ll sum = 0;
    while(chainID[u] != chainID[ances])
    {
        sum += st.get(1,1,n,pos[chainHead[chainID[u]]], pos[u]);
        u = par[chainHead[chainID[u]]];
    }
    while(chainID[v] != chainID[ances])
    {
        sum += st.get(1,1,n,pos[chainHead[chainID[v]]], pos[v]);
        v = par[chainHead[chainID[v]]];
    }
    if(u==v) return sum;
    if(high[u] < high[v]) sum += st.get(1,1,n,pos[u]+1,pos[v]);
    else sum += st.get(1,1,n,pos[v]+1,pos[u]);
    return sum;
}


void solve()
{
    cin>>n;
    for(int i=1;i<n;i++)
    {
        ll z;
        int u,v; cin>>u>>v>>z;
        u++;
        v++;
        adj[u].pb(v);
        adj[v].pb(u);
        edges[i] = {u,v,z};
    }
    dfs(1,-1);
    hld(1,-1);
    /*
    for(int i=1;i<=n;i++)
    {
        cout<<i<<' '<<high[i]<<'\n';
    }
    */
    for(int i=1;i<n;i++) upd1(edges[i].u,edges[i].v,edges[i].d);
    cin>>q;
    while(q--)
    {
        string s; cin>>s;
        if(s == "SUM" || s == "Sum")
        {
            int u,v; cin>>u>>v;
            u++;
            v++;
            cout<<query(u,v)<<'\n';
        }else if(s == "C")
        {
            int u;
            ll x; 
            cin>>u>>x;
            upd1(edges[u].u,edges[u].v,x);
        }else
        {
            int u,v; cin>>u>>v;
            u++;
            v++;
            upd2(u,v);
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