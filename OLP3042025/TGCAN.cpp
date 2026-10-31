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
#define task "TGCAN"
using namespace std;
const ll N=1e5+20;
const ll M=1LL<<10;
const ll GH=5;
const ll MOD=1e9+7;
const ll base=521;
const ll LOG=30;
ll idx[]={0,0,1,-1};
ll idy[]={1,-1,0,0};
vector<ll> v;
ll mp[N];
ll pre[N];
void solve(){
    memset(mp,0,sizeof(mp));
    memset(pre,0,sizeof(pre));
    ll n;
    cin>>n;
    ll a[n+5];
    ll ans=0;
    for(ll i=1;i<=n;i++)
    {
        cin>>a[i];
        if(mp[a[i]]==0)
        {
            v.pb(a[i]);
        }
        mp[a[i]]++;
    }
    for(ll i=1;i<=1e5;i++)
    {
        pre[i]=mp[i];
        pre[i]=pre[i-1]+pre[i];
    }
    for(ll i=0;i<v.size();i++)
    {
        ll x=v[i];
        // chon 2
        ll right=min(2*x-1,100000LL);
        //cout<<x<<' '<<right<<'\n';
        ans+=max(0LL,((mp[x]*(mp[x]-1))/2)*(pre[right]-mp[x]));
        // chon 3
        ans+=max(0LL,((mp[x]*(mp[x]-1)*(mp[x]-2))/6));
    }
    cout<<ans;
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
