#include <bits/stdc++.h>
#define task "ESCAPE"
#define ll long long

using namespace std;

const int N = 50005;
int n, d;
ll a[N];

bool check(ll val)
{
    ll cur = 0;
    int idx = 1;
    
    for (int day = 1; day <= d; ++day)
    {
        while (cur < val && idx <= n)
        {
            cur += a[idx];
            idx++;
        }
        if (cur < val) return false;
        cur /= 2;
    }
    return true;
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
    cin>>n>>d;
    ll sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        cin>>a[i];
        sum+=a[i];
    }
    
    ll l = 0, r = sum, ans = 0;
    while (l <= r) {
        ll mid = (l+r)/2;
        if (check(mid))
        {
            ans = mid;
            l = mid + 1;
        }
        else 
        {
            r = mid - 1;
        }
    }
    cout<<ans;
}