#include<bits/stdc++.h>
#define ll long long
#define task "task"
#define pb push_back
using namespace std;

const int N = 102;
vector<int> adj[N];
bool visited[N];
int n,m;

bool kt_tri(int n)
{
    for(int u = 1; u <= n; u++)
    {
        for(int v : adj[u])
        {
            visited[v] = true;
        }
        for(int v : adj[u])
        {
            for(int w : adj[v])
            {
                if(visited[w]) 
                {
                    for(int reset_v : adj[u]) visited[reset_v] = false;
                    return true;
                }
            }
        }
        for(int v : adj[u])
        {
            visited[v] = false;
        }
    }
    return false;
}

void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) 
    {
        visited[i] = false;
        adj[i].clear();
    }
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    if(kt_tri(n) == true)
    {
        if(m <= 3*n-6) cout<<"YES\n";
        else cout<<"NO\n";
    }else
    {
        if(m <= 2*n-4) cout<<"YES\n";
        else cout<<"NO\n";
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
    int t=1; cin>>t;
    while(t--) solve();
}