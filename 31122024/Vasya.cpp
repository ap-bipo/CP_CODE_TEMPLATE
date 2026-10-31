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
struct Node{
    ll U;
    ll R;
    ll L;
    ll D;
    Node()
    {
        U=0;
        R=0;
        L=0;
        D=0;
    }
};
Node sub(Node a,Node b)
{
    Node ans;
    ans.D=a.D-b.D;
    ans.L=a.L-b.L;
    ans.U=a.U-b.U;
    ans.R=a.R-b.R;
    return ans;
}
bool kt(ll dd,string s,Node pre[],ll x,ll y)
{
    Node op2=pre[s.size()-1];
    
    for(ll i=1;i+dd-1<=s.size()-1;i++)
    {
        Node ins=sub(pre[i+dd-1],pre[i-1]);
        Node out=sub(op2,ins);
        ll n_y=out.U-out.D;
        ll n_x=out.R-out.L;
        ll dis_y=abs(y-n_y);
        ll dis_x=abs(x-n_x);
        ll re=dd-dis_y-dis_x;
        if(re%2==0&&re>=0)
        {
            return true;
        }
    }
    return false;
}
void solve()
{
    ll n;
    cin>>n;
    string s;
    cin>>s;
    ll x,y;
    cin>>x>>y;
    s=' '+s;
    Node pre[n+5];
    for(ll i=1;i<=n;i++)
    {
        pre[i]=pre[i-1];
        if(s[i]=='D')
        {
            pre[i].D++;
        }else if(s[i]=='U')
        {
            pre[i].U++;
        }else if(s[i]=='L')
        {
            pre[i].L++;
        }else 
        {
            pre[i].R++;
        }
    }
    ll l=1;
    ll r=n;
    ll res=-1;
    while(l<=r)
    {
        ll mid=(l+r)/2;
        if(kt(mid,s,pre,x,y)==true)
        {
            res=mid;
            r=mid-1;
        }else
        {
            l=mid+1;
        }
    }
    cout<<res;

}
signed main(){

    if(fopen("Vasya.inp", "r")){
        freopen("Vasya.inp", "r", stdin);
        freopen("Vasya.out", "w", stdout);
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
