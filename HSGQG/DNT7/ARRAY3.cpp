#include<bits/stdc++.h>
#define ll long long
#define task "ARRAY3"
#define pb push_back
#define in insert
using namespace std;

const int N = 1e5+20;

int n; 
vector<int> v;
set<ll> s;
int cnt[N];
bool visited[N];
priority_queue<int> pq;

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        ll x; cin>>x;
        s.in(x);
        if(x < N) cnt[x]++;
    }

    for(ll x : s) v.pb(x);
    ll mi=v[0];
    if(mi<N&&cnt[mi]==1)
    {
        cout<<mi;
        return;
    }
    for(int i=1;i<v.size();i++)
    {
        pq.push(v[i]);
        visited[v[i]] = true;
    }

    ll ans=0;
    int steps=0;
    const int GH = 20000000;
    while(!pq.empty())
    {
        ll u = pq.top();
        pq.pop();
        if(u<=ans||ans==mi-1||steps>GH) break;
        ans = max(ans,u%mi);
        if(ans==mi-1) break;
        int idx = lower_bound(v.begin(), v.end(), u)-v.begin()-1;
        int tmp = 0; 
        for(int i = idx; i >= 1; i--)
        {
            if(v[i]<=ans+1) break;
            if(++steps>GH || ++tmp > 500) break; 
            ll re = u % v[i];
            if(re<=ans) continue;

            if(re<mi) 
            {
                ans=max(ans,re);
                if(ans==mi-1) break;
            }
            else if(visited[re] == false)
            {
                visited[re]=true;
                pq.push(re);
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