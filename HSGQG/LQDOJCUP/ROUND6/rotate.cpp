#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "rotate"
using namespace std;


const int N = 5e5+20;

void solve()
{
    cin>>T;
    int n = T.length();
    vector<int> pi(n, 0);
    for(int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while(j > 0 && T[i] != T[j]) j = pi[j - 1];
        if(T[i] == T[j]) j++;
        pi[i] = j;
    }
    
    int L = pi[n - 1];
    int C = 1;
    if(L > 0 && n % (n - L) == 0) {
        C = n / (n - L);
    }
    
    int q;
    cin >> q;
    
    vector<ll> dp_A(220797 + 5, 0);
    vector<ll> dp_B(220797 + 5, 0);
    dp_A[0] = 1;
    dp_B[0] = 0;
    
    for(int i = 1; i <= 220797; i++) {
        dp_A[i] = (1LL * (n - 1) * dp_B[i - 1]) % MOD;
        dp_B[i] = (dp_A[i - 1] + 1LL * (n - 2) * dp_B[i - 1]) % MOD;
    }
    
    while(q--) {
        ll k;
        cin >> k;
        if (k <= 220797) {
            ll ans = (dp_A[k] + 1LL * (C - 1) * dp_B[k]) % MOD;
            cout << ans << " ";
        } else {
            ll A = 1, B = 0;
            for (ll i = 1; i <= k; ++i) {
                ll nA = (1LL * (n - 1) * B) % MOD;
                ll nB = (A + 1LL * (n - 2) * B) % MOD;
                A = nA;
                B = nB;
            }
            ll ans = (A + 1LL * (C - 1) * B) % MOD;
            cout << ans << " ";
        }
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