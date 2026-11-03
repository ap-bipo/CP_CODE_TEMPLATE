#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pb push_back
#define task "LUOIDIEN"
using namespace std;

const int N = 1505;
const int INF = 1e9;

int n, m, q;
int f[20];
int adj[N][N];
int dist_out[20][N];
int dist_in[20][N];
int cost[20][20];
int dp[1<<17][17];
int W[20][20];

void solve()
{
    cin >> n >> m >> q;
    for(int i=0; i<m; i++) cin >> f[i];
    
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            cin >> adj[i][j];
        }
    }
    
    for(int i=0; i<m; i++)
    {
        int src = f[i];
        for(int j=1; j<=n; j++) dist_out[i][j] = INF;
        vector<bool> vis(n + 1, false);
        dist_out[i][src] = 0;
        for(int step=1; step<=n; step++)
        {
            int u = -1;
            for(int j=1; j<=n; j++)
            {
                if(!vis[j] && (u == -1 || dist_out[i][j] < dist_out[i][u])) u = j;
            }
            if(u == -1 || dist_out[i][u] == INF) break;
            vis[u] = true;
            for(int v=1; v<=n; v++)
            {
                if(dist_out[i][v] > dist_out[i][u] + adj[u][v]) 
                    dist_out[i][v] = dist_out[i][u] + adj[u][v];
            }
        }
        
        for(int j=1; j<=n; j++) dist_in[i][j] = INF;
        vis.assign(n + 1, false);
        dist_in[i][src] = 0;
        for(int step=1; step<=n; step++)
        {
            int u = -1;
            for(int j=1; j<=n; j++)
            {
                if(!vis[j] && (u == -1 || dist_in[i][j] < dist_in[i][u])) u = j;
            }
            if(u == -1 || dist_in[i][u] == INF) break;
            vis[u] = true;
            for(int v=1; v<=n; v++)
            {
                if(dist_in[i][v] > dist_in[i][u] + adj[v][u]) 
                    dist_in[i][v] = dist_in[i][u] + adj[v][u];
            }
        }
    }
    
    for(int i=0; i<m; i++)
        for(int j=0; j<m; j++)
            cost[i][j] = dist_out[i][f[j]];

    for(int st = 0; st < m; st++)
    {
        for(int mask = 0; mask < (1<<m); mask++)
            for(int i=0; i<m; i++) dp[mask][i] = INF;
            
        dp[1<<st][st] = 0;
        
        for(int mask = 1; mask < (1<<m); mask++)
        {
            for(int u = 0; u < m; u++)
            {
                if(dp[mask][u] == INF) continue;
                for(int v = 0; v < m; v++)
                {
                    if(!(mask & (1<<v)))
                    {
                        dp[mask | (1<<v)][v] = min(dp[mask | (1<<v)][v], dp[mask][u] + cost[u][v]);
                    }
                }
            }
        }
        
        for(int end = 0; end < m; end++)
            W[st][end] = dp[(1<<m)-1][end];
    }

    for(int k=1; k<=q; k++)
    {
        int u, v;
        cin >> u >> v;
        int ans = 2e9;
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<m; j++)
            {
                if(dist_in[i][u] != INF && W[i][j] != INF && dist_out[j][v] != INF)
                {
                    ans = min(ans, dist_in[i][u] + W[i][j] + dist_out[j][v]);
                }
            }
        }
        cout << ans << (k == q ? "" : " ");
    }
    cout << "\n";
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