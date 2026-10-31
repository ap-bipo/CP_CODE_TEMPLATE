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
const ll N=2e5+20;
const ll M=1LL<<21;
const ll GH=2e5+2;
const ll MOD=1e9+7;
const ll base=521;
const ll LOG=30;
ll rd(ll l,ll r)
{
    ll tmp=0;
    for(ll i=0;i<60;i++)
    {
        if(rand()%2==0)
        {

            continue;
        }
        tmp=tmp+(1LL<<i);

    }
    return l+(tmp%(r-l+1));
}
ll getNum(vector<ll>& v)
{
    ll n = v.size();
    srand(time(NULL));
    ll index = rd(1,n);
    ll num = v[index];
    swap(v[index], v[n - 1]);
    v.pop_back();
    return num;
}
vector<ll> res;
void generateRandom(ll n)
{
    vector<ll> v(n);
    for (ll i = 0; i < n; i++)
        v[i] = i + 1;
    while (v.size()) {
        res.pb(getNum(v));
    }
}
signed main(){
    srand(time(NULL));
    for(ll t=1;t<=10000;t++)
    {

        ofstream fo ("code.inp");
        res.clear();
        ll n=rd(10,12);
        fo<<n<<"\n";
        generateRandom(n);
        for(auto x:res)
        {

            fo<<x<<" ";
        }
        fo.close();
        system("code.exe");
        system("code_trau.exe");
        if(system("fc code.out code.ans")!=0)
        {

            cout<<"WRONG";
            return 0;
        }else
        {

            cout<<"OK"<<endl;
        }
    }

}
//
