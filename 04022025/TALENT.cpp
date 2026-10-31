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
#define task "TALENT"
using namespace std;
const ll N=2e5+20;
const ll M=1LL<<10;
const ll GH=5;
const ll MOD=1e9+7;
const ll base=521;
const ll LOG=30;
ll idx[]={0,0,1,-1};
ll idy[]={1,-1,0,0};
void solve(){
    ll n,m;
    cin>>n>>m;
    ll pre[n+5];
    ll pre_w[n+5];
    pair<ll,ll> p[n+5];
    for(ll i=1;i<=n;i++)
    {
        cin>>p[i].fi;
    }
    for(ll i=1;i<=n;i++)
    {
        cin>>p[i].se;
    }
    sort(p+1,p+1+n);
    pre[1]=p[1].fi*p[1].se;
    pre_w[1]=p[1].se;
    for(ll i=2;i<=n;i++)
    {
        pre[i]=pre[i-1]+p[i].fi*p[i].se;
        pre_w[i]=pre_w[i-1]+p[i].se;
    }
    p[n+1].fi=1e18;
    p[0].fi=0;
    while(m--)
    {
        ll x;
        cin>>x;
        ll l=0;
        ll r=n+1;
        ll pos=0;
        while(l<=r)
        {
            ll mid=(l+r)/2;
            if(p[mid].fi<=x)
            {
                pos=mid;
                l=mid+1;
            }
            else
            {
                r=mid-1;
            }
        }
        if(pos==0)
        {
            
            cout<<(pre[n])-pre_w[n]*x<<'\n';
        }
        else if(pos==n+1)
        {
            
            cout<<(pre_w[n]*x)-pre[n]<<'\n';
        }else
        {

            cout<<(pre_w[pos]*x-pre[pos])+(-(pre_w[n]-pre_w[pos])*x+(pre[n]-pre[pos]))<<'\n';
        }
    }
}
signed main(){

    if(fopen(task".INP", "r")){
        freopen(task".INP", "r", stdin);
        freopen(task".OUT", "w", stdout);
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
