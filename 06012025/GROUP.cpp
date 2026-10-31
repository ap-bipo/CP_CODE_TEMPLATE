#include<bits/stdc++.h>
#define ll long long
#define dbl double long
#define pb push_back
#define in insert
#define fi first
#define se second
#define MASK(i) (1LL << (i))
#define c_bit(i) __builtin_popcountll(i)
#define bit(x, i) ((x) & MASK(i))
#define on(x, i) ((x) |(1LL<<i))
#define off(x, i) ((x) & ~MASK(i))
#define task "code"
using namespace std;
const ll N=1200;
const ll M=1LL<<20;
const ll GH=2e5+2;
const ll MOD=1e9+7;
const ll base=521;
const ll LOG=30;
struct segment
{
    map<ll,pair<ll,ll> > st;
    void upd(ll id,ll l,ll r,ll i,ll val,ll type)
    {
        if(i<l||i>r)
        {
            return ;
        }
        if(l==r)
        {
            if(type==1)
            {
                st[id].fi+=val;
            }else
            {
                st[id].se+=val;
            }
            
            return ;
        }
        ll mid=(l+r)/2;
        upd(id*2,l,mid,i,val,type);
        upd(id*2+1,mid+1,r,i,val,type);
        st[id].se=st[id*2].se+st[id*2+1].se;
        st[id].fi=st[id*2].fi+st[id*2+1].fi;
    }
    ll get(ll id,ll l,ll r,ll u,ll v,ll type)
    {
        if(r<u||v<l)
        {
            return 0;
        }
        if(u<=l&&r<=v)
        {
            if(type==1)
            {
                return st[id].fi;
            }else
            {
                return st[id].se;
            }
            
        }
        ll mid=(l+r)/2;
        return get(id*2,l,mid,u,v,type)+get(id*2+1,mid+1,r,u,v,type);
    }
};
segment st;
void solve()
{
    ll n;
    cin>>n;
    ll a[n+5];
    for(ll i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    ll p;
    cin>>p;
    ll sum=0;
    ll ans=0;
    ll cnt_0=0;
    for(ll i=1;i<=n;i++)
    {
        a[i]-=p;
        sum+=a[i];
        ll op=0;
        if(sum>0)
        {
            op=st.get(1,1,1e12,1,sum,1)+st.get(1,1,1e12,1,1e12,2);
            op=op+cnt_0;
            st.upd(1,1,1e12,sum,sum,1);
        }else if (sum<0)
        {
            op=st.get(1,1,1e12,1,sum,2);
            st.upd(1,1,1e12,abs(sum),abs(sum),2);
        }
        else if(sum==0)
        {
            cnt_0++;
            op=st.get(1,1,1e12,1,1e12,2);
            op=op+cnt_0;
        }
        ans+=op;
    }
    cout<<ans;
}
signed main(){

    if(fopen("GROUP.INP", "r")){
        freopen("GROUP.INP", "r", stdin);
        freopen("GROUP.OUT", "w", stdout);
    }
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll t;
    t=1;
    while(t--)
    {

        solve();
    }

}
//
