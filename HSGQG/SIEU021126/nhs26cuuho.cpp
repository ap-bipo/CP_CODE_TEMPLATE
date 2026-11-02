#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pb push_back
#define task "task"
using namespace std;

const int N = 100005;
const int S = 320;
const int MOD = 1e9+7;

int n;
ll d[N];
ll x[N];
int dp[N]; 
int add[N][S+5];
int sub[N][S+5];
int f[N][S+5];
int ans = 0;

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++) cin >> d[i] >> x[i];
    dp[1]=1;
    
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=S;j++)
        {
            long long val = 0;
            if(i>j)
            {
                val = (1LL * f[i - j][j] + add[i][j] - sub[i][j]) % MOD;
            }
            else val = (1LL * add[i][j] - sub[i][j]) % MOD;
            
            if (val < 0) val += MOD;
            f[i][j] = val;
            
            dp[i] += f[i][j];
            if(dp[i] >= MOD) dp[i] -= MOD;
        }
        
        ans += dp[i];
        if(ans >= MOD) ans -= MOD;
        
        if(d[i]==0 || x[i]==0) continue;
        
        if (d[i]>S)
        {
            for(int j=1; j<=x[i]; j++)
            {
                ll nxt = i + j*d[i];
                if(nxt>n) break;
                
                dp[nxt] += dp[i];
                if (dp[nxt] >= MOD) dp[nxt] -= MOD;
            }
        }
        else
        {
            ll nxt = i+d[i];
            if(nxt<=n) 
            {
                add[nxt][d[i]] += dp[i];
                if(add[nxt][d[i]] >= MOD) add[nxt][d[i]] -= MOD;
            }
            ll end_nxt = i+(x[i]+1) * d[i];
            if(end_nxt<=n) 
            {
                sub[end_nxt][d[i]] += dp[i];
                if(sub[end_nxt][d[i]] >= MOD) sub[end_nxt][d[i]] -= MOD;
            }
        }
    }
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