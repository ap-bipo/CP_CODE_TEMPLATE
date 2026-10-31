#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define task "TERM"
using namespace std;

const int N = 1e5+20;
pair<ll,ll> a[N];
int n;
ll B;

void solve()
{
    cin>>n>>B;
    for(int i=1;i<=n;i++) cin>>a[i].fi>>a[i].se;
    sort(a+1,a+1+n);
    ll ans = 0;
    for(int i=1;i<=n;i++)
    {
        ll cur = min(a[i].se, B/a[i].fi);
        ans += cur;
        B -= cur * a[i].fi;
        //cout<<cur<<' '<<B<<'\n';
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