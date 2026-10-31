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
const ll M=1LL<<20;
const ll GH=2e5+2;
const ll MOD=1e9+7;
const ll base=521;
const ll LOG=30;
ll idx[]={0,0,1,-1};
ll idy[]={1,-1,0,0};
ll par[N];
ll sz[N];
ll root(ll u) {
    return par[u] == u ? u : par[u] = root(par[u]);
}
void ghep(ll u, ll v) {
    u = root(u);
    v = root(v);
    if (u == v) return;
    if (sz[u] < sz[v]) swap(u, v);
    par[v] = u;
    sz[u] += sz[v];
}
void solve()
{

    ll n,m,k;
    cin>>n>>m>>k;
    ll min_dis=1e18;
    for(ll i=1;i<=n;i++)
    {
        par[i]=i;
        sz[i]=1;
    }
    for(ll i=1;i<=k;i++)
    {
        ll x; cin>>x;
        min_dis=min(min_dis,x);
    }
    for(ll i=1;i<=m;i++)
    {
        ll u,v,z;
        cin>>u>>v>>z;
        if(min_dis<=z)
        {
            ghep(u,v);
        }
    }
    set<ll> ans;
    for(ll i=1;i<=n;i++)
    {
        ans.in(root(i));
    }
    cout<<ans.size();
}
signed main(){

    if(fopen("banhkeo.inp", "r")){
        freopen("banhkeo.inp", "r", stdin);
        freopen("banhkeo.out", "w", stdout);
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
