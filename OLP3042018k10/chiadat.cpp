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
const ll N=550;
const ll M=1LL<<20;
const ll GH=2e5+2;
const ll MOD=1e9+7;
const ll base=521;
const ll LOG=30;
ll idx[]={0,0,1,-1};
ll idy[]={1,-1,0,0};
ll pre[N][N];
ll a[N][N];
ll get_sum(ll u,ll v,ll x,ll y)
{
    return pre[x][y]-pre[u-1][y]-pre[x][v-1]+pre[u-1][v-1];
}
void solve()
{
    memset(pre,0,sizeof(pre));
    ll n;
    cin>>n;
    ll m=n;
    for(ll i=1;i<=n;i++)
    {
        for(ll j=1;j<=m;j++)
        {
            cin>>a[i][j];
        }
    }
    for(ll i=1;i<=n;i++)
    {
        for(ll j=1;j<=m;j++)
        {
            pre[i][j]=pre[i-1][j]+pre[i][j-1]+a[i][j]-pre[i-1][j-1];
        }
    }
    ll ans=1e18;
    for(ll i=1;i<=n;i++)
    {
        for(ll j=1;j<=m;j++)
        {
            ll f1=get_sum(1,1,i,j);
            ll f2=get_sum(i+1,1,m,j);
            ll f3=get_sum(1,j+1,i,n);
            ll f4=get_sum(i+1,j+1,n,m);
            ll op1=max(f1,max(f2,max(f3,f4)));
            ll op2=min(f1,min(f2,min(f3,f4)));
            ll dd=abs(op1-op2);
            ans=min(ans,dd);
        }
    }
    cout<<ans;
}
signed main(){

    if(fopen("chiadat.inp", "r")){
        freopen("chiadat.inp", "r", stdin);
        freopen("chiadat.out", "w", stdout);
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
