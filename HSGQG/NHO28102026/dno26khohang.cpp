#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define in insert
#define task "task"
using namespace std;

const int N = 1e5+20;
int n,m;
ll deq[N];
ll dp[N];
ll deq_val[N];
ll n_dp[N];

void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        int w,v,c; cin>>w>>v>>c;
        if(w*c>=m)
        {
            for(int j = w;j<=m;j++) dp[j] = max(dp[j],dp[j-w] + v);
        }
        else   
        {
            for(int r = 0;r < w;r++)
            {
                int head=0,tail=0;
                int k = (m-r)/w;
                for(int z=0;z<=k;z++)
                {
                    int j = r + z*w;
                    ll val = dp[j] - 1LL*z*v;
                    while(head < tail && deq[head] < z-c) head++;
                    while(head < tail && deq_val[tail - 1] <= val) tail--;
                    deq[tail] = z;
                    deq_val[tail] = val;
                    tail++;
                    n_dp[j] = deq_val[head] + z*v;
                }
            }
            for(int j=0;j<=m;j++) dp[j] = n_dp[j];
        }
    }
    ll ans=0;
    for(int i=0;i<=m;i++) ans=max(ans,dp[i]);
    cout<<ans;
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