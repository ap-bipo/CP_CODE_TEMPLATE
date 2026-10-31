#include<bits/stdc++.h>
#define ll long long
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
int curChain,curPos;




void dfs(int u,int z)
{
    sz[u] = 1;
    for(int i=0;i<adj[u].size();i++)
    {
        int v = adj[u][i];
        if(v==z) continue;
        par[v] = u;
        high[v] = high[u] + 1;
        dfs(v,u);
        sz[v] += sz[u];
    }
}


int hld(int u,int z)
{
    if(chainHead[curChain] == 0) chainHead = u;
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
    if(nxt == 0) hld(nxt,u);
    
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
        st[id*2].lazy *= delta;
        st[id*2].val *= st[id*2].lazy;
        st[id*2+1].lazy *= delta;
        st[id*2+1].val *= st[id*2+1].lazy;
        st[id].lazy = 1;
    }

    void upd1(int id,int l,int r,int i,ll x)
    {
        down(id,l,r);
        if(r<i || i<l) return;
        if(l==r)
        {
            st[id].val += x;
            return ;
        }
        int mid = (l+r)>>1;
        upd(id*2,l,mid,i,x);
        upd(id*2+1,mid+1,r,i,x);
        st[id].val = st[id*2+1].val + st[id*2].val;
    }

    void upd2(int id,int l,int r,int u,int v)
    {
        down(id,l,r);
        if(r<u || v<l) return;
        if(l<=u&&v<=r)
        {
            st[id].val *= (-1);
            st[id].lazy *= (-1);
            return;
        }
        int mid = (l+r) >> 1;
        upd2(id*2,l,mid,u,v);
        upd2(id*2+1,mid+1,r,u,v);
        st[id].val = st[id*2+1].val + st[id*2].val;
    }

    ll get(int id,int l,int r,int u,int v)
    {
        down(id,l,r);
        if(r<u || v<l) return 0;
        if(l<=u && v<=r) return st[id].val;
        int mid = (l+r) >> 1;
        return get(id*2,l,mid,u,v) + get(id*2+1,mid+1,r,u,v);
    }
};


void solve()
{
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int u,v; cin>>u>>v;
        adj[u].pb(v);
    }

    lazy st(sz);

}





signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t=1;
    while(t--) solve();
}