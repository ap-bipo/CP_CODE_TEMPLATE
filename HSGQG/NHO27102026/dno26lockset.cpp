#include <bits/stdc++.h>
#define ll long long
#define task "task"
using namespace std;

const int N = 1e6 + 20;
const int M = 20;
const ll MOD = 1e9 + 7;

ll dp[1 << M];
ll res[M + 5];
ll pow2[N];
int n, k;

void solve()
{
    cin >> n >> k;
    pow2[0]=1;
    for(int i = 1; i <= n; i++) pow2[i] = (pow2[i-1] * 2) % MOD;
    for(int i = 1; i <= n; i++)
    {
        int a; cin>>a;
        dp[a]++;
    }

    for(int i = 0; i < k; i++)
    {
        for(int mask = 0; mask < (1 << k); mask++)
        {
            if(!(mask & (1 << i))) dp[mask] += dp[mask ^ (1 << i)];
        }
    }

    for(int mask = 0; mask < (1 << k); mask++) dp[mask] = (pow2[dp[mask]] - 1 + MOD) % MOD;

    for(int i = 0; i < k; i++)
    {
        for(int mask = 0; mask < (1 << k); mask++)
        {
            if(!(mask & (1 << i)))  dp[mask] = (dp[mask] - dp[mask ^ (1 << i)] + MOD) % MOD;
        }
    }

    for(int mask = 0; mask < (1 << k); mask++)
    {
        int bits = __builtin_popcount(mask);
        res[bits] = (res[bits] + dp[mask]) % MOD;
    }

    for(int i = 0; i <= k; i++) cout << res[i] << ' ';
    
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
    solve();
}