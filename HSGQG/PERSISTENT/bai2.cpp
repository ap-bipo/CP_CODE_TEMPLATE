#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "task"
#define fi first
#define se second
#define in insert
using namespace std;

const int N = 1e5+20;

struct Node
{
    int l, r;
    int pref,suff,max_len,len;
};

vector<Node> st;
map<int, vector<int>, greater<int>> mp;
int n, q;
int a[N], root[N];
int vals[N]; 

Node merge_node(Node left, Node right) 
{
    if(left.len == 0) return right;
    if(right.len == 0) return left;
    Node res;
    res.l = 0; res.r = 0; 
    res.len = left.len + right.len;
    res.pref = left.pref + (left.pref == left.len ? right.pref : 0);
    res.suff = right.suff + (right.suff == right.len ? left.suff : 0);
    res.max_len = max({left.max_len, right.max_len, left.suff + right.pref});
    return res;
}

int build(int l, int r) 
{
    int v = st.size();
    st.pb({0, 0, 0, 0, 0, r-l+1}); 
    if(l == r) return v;
    int mid = (l+r)>>1;
    int left_child = build(l, mid);
    int right_child = build(mid + 1, r);
    st[v].l = left_child;
    st[v].r = right_child;
    return v;
}

int upd(int id, int l, int r, int i)
{
    int v = st.size();
    st.pb(st[id]);
    if(l==r)
    {
        st[v].pref=1;
        st[v].suff=1;
        st[v].max_len=1;
        return v;
    }
    int mid=(l+r)>>1;
    if(i<=mid)
    {
        int t=upd(st[v].l, l, mid, i);
        st[v].l = t;
    }
    else
    {
        int t=upd(st[v].r, mid + 1, r, i);
        st[v].r = t;
    }
    Node lc = st[st[v].l];
    Node rc = st[st[v].r];
    st[v].len = lc.len+rc.len;
    st[v].pref = lc.pref+(lc.pref==lc.len ? rc.pref : 0);
    st[v].suff = rc.suff+(rc.suff==rc.len ? lc.suff : 0);
    st[v].max_len = max({lc.max_len, rc.max_len, lc.suff + rc.pref});
    return v;
}

Node query(int id, int l, int r, int u, int v)
{
    if(u<=l&&r<=v) return st[id];
    int mid=(l+r)>>1;
    if(v<=mid) return query(st[id].l,l,mid,u,v);
    if(u>mid) return query(st[id].r,mid+1,r,u,v);
    return merge_node( query(st[id].l,l,mid,u,v), query(st[id].r,mid+1,r,u,v));
}

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        mp[a[i]].pb(i);
    }
    cin>>q;
    st.clear();
    st.reserve(N * 40); 
    root[0] = build(1,n);
    int pos = 0;
    for(auto it:mp)
    {
        int val = it.fi;
        vals[++pos] = val;
        int cur = root[pos - 1];
        for(int idx:it.se)
        {
            cur = upd(cur, 1, n, idx);
        }
        root[pos] = cur;
    }
    int ver=pos;
    while(q--)
    {
        int l, r, w;
        cin>>l>>r>>w;
        int l1= 1,r1=ver,ans = -1;
        while(l1<=r1)
        {
            int mid=(l1+r1)>>1;
            Node res = query(root[mid], 1, n, l, r);
            if(res.max_len >= w)
            {
                ans=vals[mid];
                r1=mid-1; 
            }
            else
            {
                l1=mid+1; 
            }
        }  
        cout<<ans<<'\n';
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