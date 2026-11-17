#include<bits/stdc++.h>
#define ll long long
#define task "LiChaoTree"
using namespace std;

// tim Min 

struct Line
{
    ll a,b;
    Line() : a(0), b(1e18){}
    Line(ll _a, ll _b) : a(_a), b(_b){}
    ll cal(ll x) {return a*x+b;}
    ll slope() {return a;}
};

struct Node
{
    Line f;
    int left_id;
    int right_id;
    Node() : f(Line()), left_id(-1), right_id(-1){}
};

struct LiChao
{
    vector<Node> 
    void upd(int id,int l,int r,int x)
    {
        if(l==r)
        {

        }
    }
};

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if(fopen(task".INP","r"))
    {
        freopen(task".INP","r",stdin);
        freopen(task".OUT","w",stdout);
    }
    int t=1;
    while(t--) solve();
}