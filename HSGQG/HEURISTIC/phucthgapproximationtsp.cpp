#include<bits/stdc++.h>
#define ll long long
#define task "task"
#define pb push_back
#define fi first
#define se second
using namespace std;

const int N = 105;
int n;
ll w[N][N];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve()
{  
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cin >> w[i][j];
        }
    }

    ll best_cost = 1e18;
    vector<int> best_path;
    
    int max_grasp_iter = 9000;
    
    for(int iter = 1; iter <= max_grasp_iter; iter++)
    {
        int st = rng() % n + 1; 
        vector<int> path;
        vector<bool> vis(n + 1, false);
        
        path.pb(st);
        vis[st] = true;
        int cur = st;
        ll current_cost = 0;
        
        for(int step = 1; step < n; step++)
        {
            ll min_dist = 1e18;
            ll max_dist = -1;
            for(int j = 1; j <= n; j++)
            {
                if(!vis[j])
                {
                    min_dist = min(min_dist, w[cur][j]);
                    max_dist = max(max_dist, w[cur][j]);
                }
            }
            double alpha = (rng() % 6) / 100.0; 
            ll threshold = min_dist + alpha * (max_dist - min_dist);
            vector<int> candidates;
            for(int j = 1; j <= n; j++)
            {
                if(!vis[j] && w[cur][j] <= threshold)
                {
                    candidates.pb(j);
                }
            }
            int next_node = candidates[rng() % candidates.size()];
            
            path.pb(next_node);
            vis[next_node] = true;
            current_cost += w[cur][next_node];
            cur = next_node;
        }
        current_cost += w[cur][path[0]];

        if(current_cost < best_cost)
        {
            best_cost = current_cost;
            best_path = path;
        }
    }

    vector<int> shuffle_path(n);
    for(int i = 0; i < n; i++) shuffle_path[i] = i + 1;
    
    int max_shuffle_iter = 10000; 
    
    for(int iter = 1; iter <= max_shuffle_iter; iter++)
    {
        shuffle(shuffle_path.begin() + 1, shuffle_path.end(), rng);

        ll current_cost = 0;
        for(int i = 0; i < n - 1; i++)
        {
            current_cost += w[shuffle_path[i]][shuffle_path[i+1]];
        }
        current_cost += w[shuffle_path[n-1]][shuffle_path[0]]; 
        
        if(current_cost < best_cost)
        {
            best_cost = current_cost;
            best_path = shuffle_path;
        }
    }

    for(int i = 0; i < n; i++) cout << best_path[i] << (i == n - 1 ? "" : " ");
    cout << '\n';
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
    
    int t = 1;
    while(t--) solve();
}
