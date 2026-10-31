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
#define task "MANGDIEN"
using namespace std;
const ll N=1e4+20;
const ll M=1LL<<10;
const ll GH=5;
const ll MOD=1e9+7;
const ll base=521;
const ll LOG=30;
ll idx[]={0,0,1,-1};
ll idy[]={1,-1,0,0};
ll sz[N];
ll par[N];
ll n,m;
struct edge{
    ll x;
    ll y;
    ll dis;
};
vector<edge> v;
struct dsu{

    void reset(){
        for(ll i=0;i<N;i++)
        {
            par[i]=i;
            sz[i]=1;
        }
    }
    ll root(ll u)
{
    if(u==par[u])
    {

        return u;
    }
    return root(par[u]);
}
void ghep(ll u,ll v)
{
    u=root(u);
    v=root(v);
    if(u==v)
    {

        return ;
    }
    if(sz[u]<sz[v])
    {

        swap(u,v);
    }
    par[v]=u;
    sz[u]+=sz[v];
}
};
map<ll,bool> mp;
ll f(ll id)
{
    dsu g;
    g.reset();
    ll ans=0;
    set<ll> s;
    for(ll i=0;i<v.size();i++)
    {
        if(id==i)
        {
            continue;
        }
        ll x=v[i].x;
        ll y=v[i].y;
        if(g.root(x)!=g.root(y))
        {
            ans+=v[i].dis;
            if(id==-1)
            {
                mp[i]=true;
            }
            
            g.ghep(x,y);
        }
    }
    //cout<<ans<<'\n';
    for(ll i=1;i<=n;i++)
    {
        s.in(g.root(i));
    }
    if(s.size()!=1)
    {
        return 1e18;
    }
    return ans;
}
bool cmp(edge a,edge b){
    return a.dis<b.dis;
}
void solve(){
    cin>>n>>m;
    for(ll i=1;i<=m;i++)
    {
        ll x,y,dis;
        cin>>x>>y>>dis;
        edge op;
        op.x=x;
        op.y=y;
        op.dis=dis;
        v.pb(op);
    }
    sort(v.begin(),v.end(),cmp);
    ll ans=f(-1);
    ll ans2=1e18;
    map<ll,bool>::iterator it;
    for(it=mp.begin();it!=mp.end();++it){
        {
            ans2=min(ans2,f(it->fi));
        }
    }
    cout<<ans<<' '<<ans2;
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
