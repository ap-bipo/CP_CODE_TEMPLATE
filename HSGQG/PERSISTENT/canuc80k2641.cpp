#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "task"
#define in insert
using namespace std;

const int N = 2e5+20;

struct Node
{
    int l, r, val;
};

vector<Node> st;
int n,q;
map<ll,int> mp;
int a[N], root[N];
int rev[N];
set<ll> s;

int update(int id, int l, int r, int i)
{
    int v = st.size();
    st.pb(st[id]);
    st[v].val++;
    if(l < r)
    {
        int mid = (l + r) >> 1;
        if(i <= mid)
        {
            int t = update(st[v].l, l, mid, i);
            st[v].l = t;
        }
            else
            {
            int t = update(st[v].r, mid + 1, r, i);
            st[v].r = t;
        }
    }
    return v;
}

int walk(int id1, int id2, int l, int r, int k)
{
    if(l==r) return l;
    int mid=(l+r)>>1;
    int t = st[st[id1].l].val - st[st[id2].l].val;
    if(k <= t)
        return walk(st[id1].l, st[id2].l, l, mid, k);
    return walk(st[id1].r, st[id2].r, mid + 1, r, k - t);
}



void solve()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        s.in(a[i]);
    }

    int pos=0;
    for(ll x:s) 
    {
        mp[x] = ++pos;
        rev[pos] = x;
    }
    for(int i=1;i<=n;i++) a[i] = mp[a[i]];
    int sz = (int) s.size();
    st.clear();
    st.reserve(N*20);
    st.push_back({0, 0, 0});
    root[0] = 0;
    for(int i=1;i<=n;i++) root[i] = update(root[i-1],1,sz,a[i]);

    while(q--)
    {
        int l,r,k;
        cin>>l>>r>>k;
        int ans = walk(root[r],root[l-1],1,sz,k);
        cout<<rev[ans]<<'\n';
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