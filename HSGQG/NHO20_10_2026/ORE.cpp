#include<bits/stdc++.h>
#define ll long long
#define task "ORE"
using namespace std;

const int N = 505;

ll a[N][N];
ll b[N][N];
int n,m;
ll dp[N][N];

void solve()
{
    memset(dp,0,sizeof(dp));
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
            a[i][j] += a[i][j-1];
        }
    }

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>b[i][j];
            b[i][j] += b[i-1][j];
        }
    }

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            dp[i][j] = max(dp[i][j-1] + b[i][j], dp[i-1][j] + a[i][j]);
        }
    }
    cout<<dp[n][m]<<'\n';

    
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
    solve();
}