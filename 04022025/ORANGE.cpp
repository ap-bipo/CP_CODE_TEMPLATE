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
#define task "ORANGE"
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
    ll n;
    cin>>n;
    map<ll,bool> mp;
    ll a[n+5];
    for(ll i=1;i<=n;i++)
    {
        cin>>a[i];
        mp[a[i]]=true;
    }
    sort(a+1,a+1+n);
    ll ans=0;
    ll pos=n;
    for(ll i=n;i>=1;i--)
    {
        while(a[pos]>a[i] && pos>0){
            pos--;
        }
        ll sl1=(n-pos)*a[i]+a[i];
        ll sl2=(n-i+1)*(a[i]-1);
        if(mp[a[i]-1]==true)
        {
            sl2+=a[i]-1;
        }
        ans=max(ans,sl1);
        ans=max(ans,sl2);
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
