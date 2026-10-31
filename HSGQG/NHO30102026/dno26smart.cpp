#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "task"
using namespace std;

const int N = 5e5+20;
unsigned int seed;
unsigned int next_rand() {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}
int n,m,K,Q;
vector<int> adj[N];
ll val[N];

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if(fopen(task".INP","r"))
    {
        freopen(task".INP","r",stdin);
        freopen(task".OUT","w",stdout);
    }
    cin>>n>>m>>Q>>K>>seed;
    for(int i=1;i<=n;i++) cin>>val[i];
    for(int i=1;i<=m;i++)
    {
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    unsigned ll XOR_SUM = 0;
    for (int i = 1; i <= Q; ++i) {
        int type = (next_rand() % 2) + 1;
        int u = (next_rand() % K) + 1; 

        if (type == 1) {
            ll x = (next_rand() % 1000000000) + 1;
            val[u] = x;
        } else {
            ll ans = 0;
            for(int v:adj[u]) ans += val[v];
            XOR_SUM ^= ans;
        }
    }
    cout<<XOR_SUM;

}