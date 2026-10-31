#include<bits/stdc++.h>
#define task "cup2026r4p1"
#define ll long long
#define fi first
#define se second
#define pb push_back
using namespace std;

const ll N = 1e3+20;



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