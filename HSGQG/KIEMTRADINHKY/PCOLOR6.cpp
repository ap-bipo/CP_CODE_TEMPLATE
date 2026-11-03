#include<bits/stdc++.h>
#define ll long long
#define task "PCOLOR6"
#define pb push_back
using namespace std;

const int N = 3e5+200;
int n, m;
vector<int> adj[N];
int deg[N], color[N], used_color[N];
bool in_queue[N];

void solve()
{
    cin>>n>>m;
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    for(int i = 1; i <= n; i++)
    {
        sort(adj[i].begin(), adj[i].end());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
        deg[i] = adj[i].size();
    }

    queue<int> q;
    vector<int> order;

    for(int i = 1; i <= n; i++)
    {
        if(deg[i] <= 5)
        {
            q.push(i);
            in_queue[i] = true;
        }
    }

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        order.pb(u);

        for(int v : adj[u])
        {
            if(!in_queue[v])
            {
                deg[v]--;
                if(deg[v] <= 5)
                {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }

    for(int i = 1; i <= n; i++) if(!in_queue[i]) order.pb(i);

    reverse(order.begin(), order.end());

    int timer = 0, max_color = 0;

    for(int u : order)
    {
        timer++;
        for(int v : adj[u])
        {
            if(color[v] != 0)
            {
                used_color[color[v]] = timer;
            }
        }

        int c = 1;
        while(used_color[c] == timer) c++;
        color[u]=c;
        max_color=max(max_color, c);
    }
    cout<<max_color<<'\n';
    for(int i=1;i<=n;i++) cout<<color[i]<<' ';
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