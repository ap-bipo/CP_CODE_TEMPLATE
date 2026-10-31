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
#define task "CPL3F"
using namespace std;
const ll N=205+20;
const ll M=1LL<<10;
const ll GH=5;
const ll MOD=1e9+7;
const ll base=521;
const ll LOG=30;
ll idx[]={0,0,1,-1};
ll idy[]={1,-1,0,0};
vector<ll> adj[N];
vector<ll> v;
vector<ll> cheo_l[N];
vector<ll> cheo_r[N];
vector<ll> row[N];
void duong_cheo_trai(ll depth)
{
    //cout<<row[depth].size()<<'\n';
    ll id=1;
    for(ll i=2; i < row[depth].size() ; i+=2)
    {
        ll tmp=i/2;
        for(ll d = 0;d<=i; d+=2)
        {
            if(depth-d<0 || i-d <=0)
            {
                continue;
            }
            cheo_l[id].pb(row[depth-d][i-d]);
        }
        id++;
    }
}
void duong_cheo_phai(ll depth)
{
    //cout<<row[depth].size()<<'\n';
    ll id=1;
    for(ll i=row[depth].size()-2; i >=0  ; i-=2)
    {
        ll tmp=i/2;
        ll cur=0;
        //cout<<row[depth].size()-i-1<<'\n';
        for(ll d = row[depth].size()-i-1;d>=0; d-=2)
        {
            if(depth-d<0 || row[depth-cur].size()-d-1 < 0)
            {
                continue;
            }
            cheo_r[id].pb(row[depth-cur][row[depth-cur].size()-d-1]);
            cur+=2;
        }
        id++;
    }
}
void solve(){
    ll n;
    cin>>n;
    ll gh= (3* n * (n+1) )/2;
    ll del[n+5];
    ll gh_dinh =( n * (n+1) )/2;
    for(ll i=1;i<=n;i++)
    {
        cin>>del[i];
    }
    ll cur=1;
    ll op=0;
    ll depth;
    ll i=2;
    while(cur<=gh)
    {
        op++;
        row[op].pb(0);
        for(ll j=1;j<=i;j++)
        {
            row[op].pb(cur);
            cout<<cur<<' ';
            cur++;
        }
        cout<<'\n';
        op++;
        row[op].pb(0);
        for(ll j=1;j<=i/2;j++)
        {
            row[op].pb(cur);
            cout<<cur<<' ';
            cur++;
        }
        depth=op;
        cout<<'\n';
        i+=2;
    }
    cout<<'\n' << "____"<<'\n';
    //cout<<depth<<'\n';
    duong_cheo_trai(depth-1);
    duong_cheo_phai(depth-1);
    for(ll id=1;id<=n;id++)
    {
        for(ll i=0;i<cheo_r[id].size();i++)
        {
            cout<< cheo_r[id][i] << ' ';
        }
        cout<<'\n';
    }
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
