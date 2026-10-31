#include<bits/stdc++.h>
#define ll long long
#define in insert
#define task "task"
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


const int N = 1e5+20;
ordered_set st[4*N];
int n,q;
int a[N];

void build(int id, int l, int r)
{
    for(int i=l;i<=r;i++) st[id].in({a[i],i});
    if(l==r) return ;
    int mid=(l+r)>>1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
}

void upd(int id,int l,int r,int i,ll o_x,ll n_x)
{
    st[id].erase({o_x,i});
    st[id].in({n_x,i});
    if(l==r) return ;
    int mid = (l+r)>>1;
    if(i<=mid) upd(id*2,l,mid,i,o_x,n_x);
    else upd(id*2+1,mid+1,r,i,o_x,n_x);
}

ll get(int id,int l,int r,int u,int v,ll val)
{
    if(v<l || r<u) return 0;
    if(u<=l && r<=v) return st[id].order_of_key({val,INT_MAX});
    int mid = (l+r)>>1;
    return get(id * 2,l,mid,u,v,val) + get(id*2+1,mid+1,r,u,v,val);
}


void solve()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    while(q--)
    {
        char c; cin>>c;
        if(c=='Q')
        {
            int u,v,k;
            cin>>u>>v>>k;
            int l=0;
            int r=1e9;
            int ans = -1;
            while(l<=r)
            {
                int mid=(l+r)>>1;
                int cnt = get(1,1,n,u,v,mid);
                if(cnt>=k)
                {
                    ans = mid;
                    r=mid-1;
                }else l=mid+1;
            }
            cout<<ans<<'\n';
        }else
        {
            int p,v;
            cin>>p>>v;
            upd(1,1,n,p,a[p],v);
            a[p]=v;
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