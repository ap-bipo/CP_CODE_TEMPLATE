#include<bits/stdc++.h>
#define ll long long
#define task "ASYNC"
using namespace std;

const int N = 2e5+20;
const int M = 18;

int n;
int a[N];


struct sparse{
    ll table[N][M];
    void build()
    {
        for(int i=1;i<=n;i++) table[i][0]=a[i];
        for(int j=1;j<M;j++)
        {
            for(int i=1;i+(1<<j)-1<=n;i++) table[i][j]=__gcd(table[i][j-1],table[i+(1<<(j-1))][j-1]);
        }
    }
    ll get(ll l,ll r)
    {
        ll j=(ll) log2(r-l+1);
        return __gcd(table[l][j],table[r-(1<<j)+1][j]);
    }
} rmq;




void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    rmq.build();
    for(int i=1;i<=n;i++)
    {
        int res = i;
        int l=i;
        int r=n;
        while(l<=r)
        {
            int mid =(l+r)>>1;
            if(rmq.get(l,r) == a[i])
            {
                res = mid;
                l = mid+1;
            }else r = mid-1;
        }
        cout<<i<<' '<<res<<'\n';
    }
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