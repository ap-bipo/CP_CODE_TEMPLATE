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
#define task "MOBI"
using namespace std;
const ll N=1e6+20;
const ll M=1LL<<10;
const ll GH=5;
const ll MOD=1e9+7;
const ll base=521;
const ll LOG=30;
ll idx[]={0,0,1,-1};
ll idy[]={1,-1,0,0};
ll pre[N];
void solve(){
    ll n,k;
    cin>>n>>k;
    memset(pre,0,sizeof(pre));
    for(ll i=1;i<=n;i++)
    {
        ll x,y;
        cin>>x>>y;
        pre[x+1]+=y;
    }
    pre[0]=0;
    for(ll i=1;i<=1e6+1;i++){
        pre[i]=pre[i-1]+pre[i];
    }
    ll ans=0;
    for(ll i=1;i<=1e6+1;i++)
    {
        ll left=max(1LL,i-k);
        ll right=min(1000000LL + 1LL,i+k);
        ans=max(ans,pre[right]-pre[left-1]);
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
