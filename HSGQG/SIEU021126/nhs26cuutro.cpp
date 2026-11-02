#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pb push_back
#define task "CUUTRO"
using namespace std;

const int N = 1000005;
const ll INF = 1e18;

int n;
ll a[N];
ll dp[3], ndp[3];

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    dp[0]=0;
    dp[1]=-INF;
    dp[2]=-INF;
    for(int i=1; i<=n; i++)
    {
        ndp[0] = dp[0];
        ndp[1] = dp[1];
        ndp[2] = dp[2];
        if(dp[1] != -INF) ndp[0]=max(ndp[0],dp[1]+a[i]);
        if(dp[2] != -INF) ndp[1]=max(ndp[1],dp[2]+a[i]);
        if(dp[0] != -INF) ndp[1]=max(ndp[1],dp[0]-a[i]);
        if(dp[1] != -INF) ndp[2]=max(ndp[2],dp[1]-a[i]);
        dp[0] = ndp[0];
        dp[1] = ndp[1];
        dp[2] = ndp[2];
    }
    cout<<dp[0];
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