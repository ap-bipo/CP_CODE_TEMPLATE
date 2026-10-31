#include<bits/stdc++.h>
#define ll long long
#define task "LiChaoTree"
using namespace std;

const ll LIM = 1e18;
const ll N = 1e6+20;
ll dp[N];
ll a[N];
ll pre[N];


/*
    (Hi - Hj)^2 - Wi khong duoc chon
    khi chon J moi thi: Hi^2 + Hj^2 - 2Hi * Hj - S[j-1] + S[i];

*/


struct Line
{
    ll a, b;
    Line() : a(0), b(1e18) {}
    Line(ll _a,ll _b) : a(_a), b(_b) {}
    ll cal(ll x)
    {
        return a*x+b;
    }
    ll slope()
    {
        return a;
    }
};

struct LiChao
{
    vector<Line> st;
    LiChao(){}
    LiChao(int sz) : st(4*sz+2){}
    void upd(int id, int l,int r, Line f)
    {
        if(l==r)
        {
            if(f.cal(l) < st[id].cal(l)) st[id] = f;
            return ;
        }
        int mid = (l+r) >> 1;
        if(f.cal(mid) < st[id].cal(mid)) swap(st[id],f);
        if(f.slope() > st[id].slope()) upd(id*2,l,mid,f); // > -> xuong cay trai
        else if(f.slope() < st[id].slope()) upd(id*2+1,mid+1,r,f); // < -> xuong cay phai
    }
    ll get(int id,int l,int r,int x)
    { 
        // min ax+b
        ll cur =  st[id].cal(x); 
        int mid = (l+r) >> 1;
        if(l==r) return cur;
        if(x <= mid) return min(cur, get(id*2,l,mid,x));
        else return min(cur, get(id*2+1,mid+1,r,x));
    }
};

void solve()
{
    LiChao tree(N);
    int n; cin>>n;
    pre[0] = 0;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++)
    {
        ll x; cin>>x;
        pre[i] = pre[i-1] + x;
    }
    dp[1] = 0;
    tree.upd(1,0,1e6,{-2*a[1], dp[1] + a[1]*a[1] - pre[1]});
    for(int i=2;i<=n;i++)
    {
        ll cur_ans = tree.get(1,0,1e6,a[i]);
        dp[i] = cur_ans + pre[i-1] + a[i]*a[i];
        tree.upd(1,0,1e6, {-2 * a[i], dp[i] + a[i]*a[i] - pre[i]});
        //cout<<dp[i]<<' ';
    }

    cout<<dp[n];

}

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