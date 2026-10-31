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
const ll N=1e3+20;
const ll M=1LL<<21;
const ll GH=2e5+2;
const ll MOD=1e9+7;
const ll base=521;
const ll LOG=30;
void solve()
{
    ll n;
    cin>>n;
    ll a[n+5];
    ll dp[n+5];
    memset(dp,0,sizeof(dp));
    for(ll i=1;i<=n;i++)
    {

        cin>>a[i];
    }
    ll ans=0;
    for(ll i=1;i<=n;i++)
    {
        dp[i]=1LL;
        for(ll j=1;j<i;j++)
        {

            if(a[j]<a[i])
            {
                dp[i]=max(dp[i],1+dp[j]);
                ans=max(ans,dp[i]);

            }
        }
    }
    cout<<ans;

}
signed main(){

    ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("code.inp","r"))
    {

        freopen("code.inp","r",stdin);
        freopen("code.ans","w",stdout);
    }
    ll t;
    t=1;
    while(t--)
    {

        solve();
    }

}
//
