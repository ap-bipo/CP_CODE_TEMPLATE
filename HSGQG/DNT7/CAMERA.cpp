#include<bits/stdc++.h>
#define task "CAMERA"
#define fi first
#define se second
#define pb push_back
#define ll long long
using namespace std;

const int N = 1e5+20;

struct edges
{
    int x,y;
    ll d;
};
edges p[N];

int n,m,k;
vector<pair<int,int>> adj[N];
bool visited[N];
bool spec[N];
int res[N];


int id[N << 1];
int num[N << 1], low[N << 1];
int timeDFS = 0, scc = 0;
int st[N << 1];

struct cmp
{
    bool operator()(edges a, edges b)
    {
        if(a.d == b.d)
        {
            if(a.y == b.y) return a.x < b.x;
            else return a.y < b.y; 
        }
        return a.d < b.d;
    }
};

vector<int> G[N << 1];

int NOT(int x)
{
    return x + (x <= n ? n : -n); 
}

void add_clause(int u, int v)
{
    G[NOT(u)].push_back(v); // -u -> v
    G[NOT(v)].push_back(u); // -v -> u
}

void dfs(int u)
{
    num[u] = low[u] = ++timeDFS;
    st[++st[0]] = u;
    for (const int &v : G[u])
    {
        if (id[v] != 0)
            continue;
        if (num[v] == 0)
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else
            low[u] = min(low[u], num[v]);
    }

    if (num[u] == low[u])
    {
        for (++scc; true;)
        {
            int v = st[st[0]--];
            id[v] = scc;
            if (v == u)
                break;
        }
    }
}


bool TWOSAT(ll limit)
{
    for(int i=1;i<=2*n;i++) G[i].clear();
    memset(id,0,sizeof(id));
    memset(num,0,sizeof(num));
    memset(low,0,sizeof(low));
    memset(st,0,sizeof(st));
    timeDFS = 0, scc = 0;
    
    for(int i=1;i<=m;i++)
    {
        if(p[i].d == -1)
        {
            add_clause(p[i].x,p[i].y);
            add_clause(NOT(p[i].x),NOT(p[i].y));
        }
        else if(p[i].d > limit)
        {
            add_clause(p[i].x,p[i].y);
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(spec[i] == false) add_clause(NOT(i),NOT(i));
    }
    // TWOSAT
    for(int i = 1; i <= 2 * n; ++i) if(!id[i]) dfs(i);
    bool answer = 1;
    for (int i = 1; i <= n; ++i) if(id[i] == id[NOT(i)]) answer = 0;
    if (!answer)
    {
        return false;
    }
    for (int i = 1; i <= n; ++i) res[i]=(id[i] < id[NOT(i)]);
    return true;
}



void solve()
{
    memset(visited,false,sizeof(visited));
    memset(spec,false,sizeof(spec));

    cin>>n>>m>>k;
    ll best = 0;
    for(int i=1;i<=m;i++)
    {
        ll z;
        int x,y; 
        cin>>x>>y>>z;
        adj[x].pb({y,z});
        adj[y].pb({x,z});
        p[i] = {x,y,z};
        if(z == -1)
        {
            spec[x] = true;
            spec[y] = true;
        }
    }

    sort(p+1,p+1+m,cmp());

    int l=1;
    int r=m;
    int best_pos = -1;
    
    while(l<=r)
    {
        int mid = (l+r) >> 1;
        
        if(TWOSAT(p[mid].d) == true)
        {
            best_pos = mid;
            r = mid-1;
        } else l = mid+1;
    }


    if(best_pos==-1)
    {
        cout<<-1<<'\n';
        return ;
    }

    TWOSAT(p[best_pos].d);
    cout<<max(0LL,p[best_pos].d)<<'\n';
    for(int i=1;i<=n;i++)  
    {
        if(res[i] == true) cout<<i<<' ';
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
    int t=1;
    while(t--) solve();
}