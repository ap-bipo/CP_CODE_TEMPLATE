#include <bits/stdc++.h>
#define task "test"
#define ll long long

const ll N = 1e6+20;

struct segment
{
    struct node
    {
        ll val=0;
        ll lazy=0;
    }
    ll st[4*N];
    void down(int id,int l,int r)
    {
        ll t = st[id].lazy;
        int mid = (l+r)/2;
        st[id*2].val+=(mid-l+1)*t;
        st[id*2].lazy += t;
        st[id*2+1].val+=(r-mid)*t;
        st[id*2+1].lazy +=t;
        st[id].lazy=0;
    }

    void upd(int id,int l,int r,int u,int v,int val)
    {
        down(id,l,r);
        if(v<l||r<u)
        {
            return;
        }
        if(u<=l&&r<=v)
        {
            st[id].val+=(r-l+1)*val;
            st[id].lazy+=val;
            return ;
        }
        int mid = (l+r)/2;
        upd(id*2,l,mid,u,v,val);.
        upd(id*2+1,mid+1,r,u,v,val);
        st[id].val = st[id*2].val + st[id*2+1].val;
    }

    ll get(int id,int l,int r,int u,int v)
    {
        down(id,l,r);
        if(v<l||r<u) return 0;
        if(u<=l&&r<=v) return st[id].val;
        int mid = (l+r)/2;
        return get(id*2,l,mid,u,v) + get(id*2+1,mid+1,r,u,v);
    }

} tree;

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if(fopen(task".INP", "r")){
        freopen(task".INP", "r", stdin);
        freopen(task".OUT", "w", stdout);
    }
    ll n;
    int t; cin>>t>>n;
    for(int i=1;i<=n;i++)
    {
        ll x; cin>>x;
        tree.upd(1,1,n,i,i,x);
    }
    while(t--)
    {
        int type; cin>>type;
        if(type==1)
        {
            ll l,r,val; cin>>l>>r>>val;
            tree.upd(1,1,n,l,r,val);
        }else 
        {
            ll l,r; cin>>l>>r;
            cout<<tree.get(1,1,n,l,r)<<'\n';
        }
    }
}