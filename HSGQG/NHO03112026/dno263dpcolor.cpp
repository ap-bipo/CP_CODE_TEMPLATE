#include<bits/stdc++.h>
#define ll long long
#define task "pcolor"
using namespace std;

const int N = 10005;
int n, m;
vector<int> adj[N];
int deg[N], color[N], used_color[N];
bool in_queue[N];

bool cmp(int a, int b)
{
    return deg[a] > deg[b];
}

void solve()
{
    if(!(cin >> n >> m)) return;
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    for(int i = 1; i <= n; i++)
    {
        sort(adj[i].begin(), adj[i].end(), cmp);
    }

    vector<int> nodes(n);
    for(int i = 0; i < n; i++) nodes[i] = i + 1;
    sort(nodes.begin(), nodes.end(), cmp);

    int timer = 0, max_color = 0;

    for(int start_node : nodes)
    {
        if(color[start_node] != 0) continue;

        queue<int> q;
        q.push(start_node);
        in_queue[start_node] = true;

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            timer++;
            for(int v : adj[u])
            {
                if(color[v] != 0)
                {
                    used_color[color[v]] = timer;
                }
                else if(!in_queue[v])
                {
                    q.push(v);
                    in_queue[v] = true;
                }
            }

            int c = 1;
            while(used_color[c] == timer) c++;
            color[u] = c;
            max_color = max(max_color, c);
        }
    }

    cout << max_color << "\n";
    for(int i = 1; i <= n; i++)
    {
        cout << color[i] << " ";
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