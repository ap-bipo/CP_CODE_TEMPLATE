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
struct Node{
    ll l;
    ll r;
    ll val;
    Node(ll n_l,ll n_r,ll n_val)
    {
        l=n_l;
        r=n_r;
        val=n_val;
    }
};
void solve()
{
    ll n,k;
    cin>>n>>k;
    ll a[n+5];
    vector<Node> v;
    ll dp[n+5][k+2];
    memset(dp,0,sizeof(dp));
    for(ll j=1;j<=k;j++)
    {
        for(ll i=1;i<=n;i++)
        {
            dp[i][j]=1e18;
        }
    }
    for(ll i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    for(ll i=1;i+1<=n;i++)
    {
        Node tmp=Node(i,i+1,abs(a[i]-a[i+1]));
        //cout<<tmp.l<<" "<<tmp.r<<" "<<tmp.val<<"\n";
        v.pb(tmp);
    }
    for(ll i=1;i<=k;i++)
    {
        for(ll j=0;j<v.size();j++)
        {
            if(v[j].l<i)
            {
                continue;
            }
            dp[v[j].r][i]=min(dp[v[j].r-1][i],dp[v[j].r][i]);
            dp[v[j].r][i]=min(dp[v[j].l-1][i-1]+v[j].val,dp[v[j].r][i]);
            
        }
    }
    cout<<dp[n][k];
}
signed main(){

    if(fopen("DANCE.INP", "r")){
        freopen("DANCE.INP", "r", stdin);
        freopen("DANCE.OUT", "w", stdout);
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
