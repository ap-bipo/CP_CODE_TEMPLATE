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
using namespace std;
const ll N=1e6+20;
const ll M=1LL<<10;
const ll GH=5;
const ll MOD=1e9+7;
const ll base=521;
const ll LOG=30;
ll idx[]={0,0,1,-1};
ll idy[]={1,-1,0,0};

void solve()
{
    int n,x,y; cin>>n>>x>>y;
    ll a[n+5];
    for(int i=1;i<=n;i++) cin>>a[i];

    
}
signed main(){

    if(fopen("code.INP", "r")){
        freopen("code.INP", "r", stdin);
        freopen("code.OUT", "w", stdout);
    }
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t=1;
    while(t--) solve();
}
