#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "FRUIT"
#define fi first
#define se second
using namespace std;

const int N = 250010, K=20;

int n,q;
int a[N];
int tin[N];
int tout[N];
int cnt[N];
int high[N];
int pref[N][K];
int par[N][K];
int up = 0;
vector<int> adj[N];


struct persistent
{
    struct Node
    {
        int l, r, val;
        Node()
        {
            l = -1, r = -1, val = 0;
        }
        Node(int _l, int _r, int _val) : l(_l), r(_r), val(_val) { }
    };

    int root[N], cur = 0;
    Node st[N*40 + 2];
    // CHINH VAL VOI MERGE
    int VAL(int id)
    {
        if(id == -1) return 0;
        return st[id].val;
    }

    void MERGE(int id)
    {
        st[id].val = VAL(st[id].l) + VAL(st[id].r);
    }

    int build(int l, int r)
    {
        int id = ++cur;
        if(l == r) return id;
        int mid = (l + r) >> 1;
        st[id].l = build(l, mid);
        st[id].r = build(mid + 1, r);
        return id;
    }

    int upd(int id, int l, int r, int pos, int val)
    {
        int nid = ++cur; st[nid] = st[id];
        if(l == r)
        {
            st[nid].val += val;
            return nid;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) st[nid].l = upd(st[id].l, l, mid, pos, val);
        else st[nid].r = upd(st[id].r, mid + 1, r, pos, val);
        MERGE(nid);
        return nid;
    }
    int get(int id, int l, int r, int u, int v)
    {
        if(r<u || v<l) return 0;
        if(u<=l&&r<=v) return VAL(id);
        int mid=(l+r)>>1;
        if(v<=mid) return get(st[id].l,l,mid,u,v);
        if(u>mid) return get(st[id].r,mid+1,r,u,v);
        return get(st[id].l,l,mid,u,v) + get(st[id].r,mid+1,r,u,v);
    }
} st_kt;

void dfs(int u,int p)
{
    tin[u] = ++up;
    st_kt.root[tin[u]] = st_kt.upd(st_kt.root[tin[p]], 1, n, a[u], 1);
    for(int bit = 0; bit <= 18; bit++)
    {
        pref[u][bit] = pref[p][bit] + ((a[u] >> bit) & 1);
    }
    for(int v:adj[u])
    {
        if(v==p) continue;
        high[v] = high[u]+1;
        par[v][0] = u;
        dfs(v,u);
    }
    tout[u]=up;
}

pair<int,int> lca(int u,int v)
{
    int ans = 0;
    if(high[u] < high[v]) swap(u,v);
    // high[u] > high[v]
    for(int i = 18;i>=0;i--)
    {
        if(par[u][i] == -1) continue;
        if(high[par[u][i]] >= high[v])
        {
            u = par[u][i];
            ans += (1<<i);
        }
    }
    if(u==v) return {u,ans+1};
    for(int i=18;i>=0;i--)
    {
        if(par[u][i] == -1 || par[v][i] == -1) continue;
        if(par[u][i] != par[v][i])
        {
            u = par[u][i];
            v = par[v][i];
            ans += (1<<i);
            ans += (1<<i);
        }
    }
    ans += 2;
    return {par[u][0],ans+1};
}

int get_x(int u,int v,int ances,int bit)
{
    return pref[u][bit] + pref[v][bit] - 2 * pref[ances][bit] + ((a[ances] >> bit) & 1);
}

int check_x(int u,int v,int x)
{
    if(high[u] > high[v]) swap(u,v);
    // high[u] < high[v]
    return st_kt.get(st_kt.root[tin[v]],1,n,x,x) - st_kt.get(st_kt.root[tin[u]],1,n,x,x);
}

void solve()
{
    memset(par,-1,sizeof(par));
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++)
    {
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    st_kt.root[0] = st_kt.build(1, n);
    high[0] = 0;
    tin[0] = 0;
    dfs(1,0);
    for(int j=1;j<=18;j++)
    {
        for(int i=1;i<=n;i++)
        {
            if(par[i][j-1] == -1) continue;
            par[i][j] = par[par[i][j-1]][j-1];
        }
    }

    while(q--)
    {
        int u,v; cin>>u>>v;
        pair<int,int> ances = lca(u,v);
        int mask = 0;
        bool kt = true;
        for(int bit=0;bit<=18;bit++)
        {
            int tmp = get_x(u,v,ances.fi,bit);
            if(2*tmp > ances.se) mask |= (1<<bit);
        }

        if(ances.fi == u || ances.fi == v)
        {
            int cha,con;
            if(ances.fi == u) cha = u, con = v;
            else cha = v, con = u;

            int ans = check_x(cha,con,mask) + (a[cha]==mask);
            if(ans*2 > ances.se) cout<<mask<<'\n';
            else cout<<-1<<'\n';
        }
        else
        {
            int ans = check_x(ances.fi,u,mask) + check_x(ances.fi,v,mask) + (a[ances.fi]==mask);
            if(ans*2 > ances.se) cout<<mask<<'\n';
            else cout<<-1<<'\n';
        }

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
    int t = 1;
    while(t--) solve();
}