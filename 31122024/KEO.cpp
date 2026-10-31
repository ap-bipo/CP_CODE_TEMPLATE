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
const ll N=3e3+20;
const ll M=1LL<<20;
const ll GH=2e5+2;
const ll MOD=1e9+7;
const ll base=521;
const ll LOG=30;
ll idx[]={0,0,1,-1};
ll idy[]={1,-1,0,0};
bool kt(ll n,ll x)
{
    ll tmp=n;
    ll sl=0;
    while(n>=x)
    {
        sl+=x;
        n-=x;
        n-=(n/10);
    }
    if((sl+n)*2>=tmp)
    {
        return true;
    }else
    {
        return false;
    }
}
void solve()
{

    ll n;
    cin>>n;
    ll l=1;
    ll r=n;
    ll res=n;
    while(l<=r)
    {
        ll mid=(l+r)/2;
        if(kt(n,mid)==true)
        {
            r=mid-1;
        }else
        {
            l=mid+1;
        }
    }
    cout<<l;

}
signed main(){

    if(fopen("KEO.INP", "r")){
        freopen("KEO.INP", "r", stdin);
        freopen("KEO.OUT", "w", stdout);
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
