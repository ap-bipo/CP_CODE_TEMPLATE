#include<bits/stdc++.h>
#define ll long long
#define task "RAFT"
using namespace std;

const int N = 21;
ll a[N];
int n;

bool kt(ll x,ll y)
{
    while(x>0 && y>0)
    {
        if ((x % 10) + (y % 10) > 9) return false;
        x /= 10;
        y /= 10;
    }
    return true;
}

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    int best = 0;
    for(ll mask = 0; mask < (1LL<<n); mask++)
    {
        ll sum = 0;
        bool ap = true;
        int cnt = 0;
        for(int i=0;i<n;i++)
        {
            if((((mask>>i)&1)==true))
            {
                if(kt(sum,a[i+1]) == true)
                {
                    sum += a[i+1];
                    cnt++;
                }else
                {
                    ap = false;
                    break;
                }
            }
        }
        if(ap == true) 
        {
            best = max(best,cnt);
        }
    }
    cout<<best;

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