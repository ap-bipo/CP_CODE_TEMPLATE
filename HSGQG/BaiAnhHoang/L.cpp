#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define in insert
#define pb push_back
#define task "L"
using namespace std;

const int N = 250005;

int a[N];
int n,k;
vector<int> pos[N];
int id_pos[N];

struct segment
{
    struct node
    {
        ll val;
        ll lazy;
        ll cnt_0;
        node() : val(0), lazy(0), cnt_0(0) {}
    };
    vector<node> st;
    segment(int _sz) : st(4*_sz+5){};
    void build(int id,int l,int r)
    {
        st[id].val = 0;
        st[id].lazy = 0;
        st[id].cnt_0 = r-l+1;
        if(l==r) return;
        int mid = (l+r)>>1;
        build(id*2,l,mid);
        build(id*2+1,mid+1,r);
    }
    void down(int id,int l,int r)
    {
        int t = st[id].lazy;
        if(t==0) return;
        st[id*2].val +=  t;
        st[id*2+1].val += t;
        st[id*2].lazy += t;
        st[id*2+1].lazy += t;
        st[id].lazy = 0;
    }

    void upd(int id,int l,int r,int u,int v,ll x)
    {
        if(r<u || v<l) return ;
        if(u<=l&&r<=v) 
        {
            st[id].val += x;
            st[id].lazy += x;
            return ;
        }
        int mid = (l+r)>>1;
        down(id,l,r);
        upd(id*2,l,mid,u,v,x);
        upd(id*2+1,mid+1,r,u,v,x);
        st[id].val = min(st[id*2+1].val, st[id*2].val);
        st[id].cnt_0 = 0;
        if(st[id].val == st[id*2].val) st[id].cnt_0 += st[id*2].cnt_0;
        if(st[id].val == st[id*2+1].val) st[id].cnt_0 += st[id*2+1].cnt_0;
    }
    ll get_0(int id,int l,int r,int u,int v)
    {
        if(r<u || v<l) return 0;
        if(u<=l&&r<=v) 
        {
            if(st[id].val == 0) return st[id].cnt_0;
            else return 0;
        }
        int mid = (l+r)>>1;
        down(id,l,r);
        return get_0(id*2,l,mid,u,v) + get_0(id*2+1,mid+1,r,u,v);
    }
} st(N);


void solve()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i];
        pos[a[i]].pb(i);
        id_pos[i] = (int)pos[a[i]].size() - 1;
    }
    st.build(1,1,n);
    ll ans = 0;
    for(int i=1;i<=n;i++)
    {  
        if(id_pos[i] == 0) st.upd(1,1,n,1,i,1);
        else st.upd(1,1,n,pos[a[i]][id_pos[i]-1]+1,i,1);
        if(id_pos[i] >= k-1)
        {
            // du k thang
            int pre_k = id_pos[i]-k+1;
            if(pre_k == 0) st.upd(1,1,n,1,pos[a[i]][pre_k],-1);
            else st.upd(1,1,n,pos[a[i]][pre_k-1]+1,pos[a[i]][pre_k],-1);
            
        }
        ans += st.get_0(1,1,n,1,i);
        //for(int i=1;i<=n;i++) cout<<st.get_0(1,1,n,i,i)<<' ';
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