#include<bits/stdc++.h>
#define ll long long
#define task "TRADE"
#define fi first
#define se second
using namespace std;

const int N = 1e6+5;
const ll INF = 1e18;

int n, k;
ll a[N];

void solve()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];

    if (n <= 1 || k == 0)
    {
        cout << 0 << "\n";
        return;
    }
    vector<ll> dp(n+2,0);
    vector<ll> prev_dp(n+2,0);

    for (int z = 1; z <= k; z++)
    {
        ll max_diff = -a[1]; 
        for (int i = 2; i <= n; i++)
        {
            dp[i] = max(dp[i - 1], a[i] + max_diff);
            max_diff = max(max_diff, prev_dp[i] - a[i]);
        }
        prev_dp = dp;
    }

    cout << dp[n] << "\n";
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen(task".INP", "r"))
    {
        freopen(task".INP", "r", stdin);
        freopen(task".OUT", "w", stdout);
    }
    int t = 1;
    while (t--) solve();
    return 0;
}
