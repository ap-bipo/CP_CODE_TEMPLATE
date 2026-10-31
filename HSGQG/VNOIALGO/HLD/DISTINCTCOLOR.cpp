#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "DISTINCTCOLOR"
using namespace std;

const int N = 2e5+20;

int up=0;
int n;
vector<int> pre;
vector<int> adj[N];
int tin[N];
int tout[N];
map<int,int> last_pos;
int euler_tour[N];
ll a[N];

struct MergeSort
{
    vector<vector<int>> st;
    MergeSort(int _sz) : st(4*_sz+5){}
    void build(int id,int l,int r,vector<int>& a)
    {
        if(l == r)
        {
            st[id] = {a[l]};
            return;
        }
        int mid = (l+r)>>1;
        build(id*2,l,mid,a);
        build(id*2+1,mid+1,r,a);
        st[id].resize((int)st[id*2].size() + (int)st[id*2+1].size());
        merge(st[id*2].begin(),st[id*2].end(),st[id*2+1].begin(),st[id*2+1].end(),st[id].begin());
    }
    int get(int id,int l,int r,int u,int v,ll k)
    {
        if(r<u || v<l) return 0;
        if(u<=l && r<=v) return lower_bound(st[id].begin(),st[id].end(),k) - st[id].begin();
        int mid = (l+r)>>1;
        return get(id*2,l,mid,u,v,k) + get(id*2+1,mid+1,r,u,v,k);
    }
} tree(N);


void dfs(int u,int p)
{
    tin[u] = ++up;
    euler_tour[up] = a[u];
    for(int v:adj[u])
    {
        if(v==p) continue;
        dfs(v,u);
    }
    tout[u] = up;
}


void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<n;i++)
    {
        int u,v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1,0);
    pre.assign(n+1,0);  

    for(int i=1;i<=n;i++)
    {
        if(last_pos[euler_tour[i]] == 0) pre[i] = 0;
        else pre[i] = last_pos[euler_tour[i]];

        last_pos[euler_tour[i]] = i;
        //cout<<pre[i]<<' '<<euler_tour[i]<<' '<<last_pos[euler_tour[i]]<<'\n';
    }
    //for(int i=1;i<=n;i++) cout<<pre[i]<<' ';
    tree.build(1,1,n,pre);
    for(int i=1;i<=n;i++)
    {
        cout<<tree.get(1,1,n,tin[i],tout[i],tin[i])<<' ';
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