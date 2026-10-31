#include<bits/stdc++.h>
#define task "B"
#define fi first
#define se second
#define pb push_back
using namespace std;

const int N = 2e5+20;

int n, q;
int query[N];
int res[N];
pair<int,int> seq[N];
vector<int> ap;

int pt_type[N*2];
int pt_id[N*2];
int L_idx[N];
int R_idx[N];

struct segment
{
    struct node
    {
        int val, lazy;
    };
    vector<node> st;
    segment(int _n) : st(4*_n+2){}
    
    void clear_tree()
    { 
        for(int i=0; i<st.size(); i++) st[i].val=st[i].lazy=0; 
    }
    
    void down(int id, int l, int r)
    {
        if (st[id].lazy == 0) return;
        if (l == r)
        {
            st[id].lazy = 0;
            return;
        }
        int t = st[id].lazy;
        st[id*2].val+=t;
        st[id*2+1].val+=t;
        st[id*2].lazy+=t;
        st[id*2+1].lazy+=t;
        st[id].lazy=0;
    }

    void upd(int id, int l, int r, int u, int v, int x)
    {
        down(id, l, r);
        if(r < u || v < l) return;
        if(u <= l && r <= v) {
            st[id].val += x;
            st[id].lazy += x;
            return;
        }
        int mid = (l+r) >> 1;
        upd(id*2,l,mid,u,v,x);
        upd(id*2+1,mid+1,r,u,v,x);
        st[id].val = max(st[id*2+1].val, st[id*2].val);
    }
};

void solve() {
    cin >> n >> q;
    for(int i=1;i<=n;i++)
    {
        cin>>seq[i].fi>>seq[i].se;
        ap.pb(seq[i].fi);
        ap.pb(seq[i].se);
    }

    for(int i=1; i<=q; i++) cin>>query[i];

    sort(ap.begin(),ap.end());
    int lim = (int)ap.size();
    
    for(int i=1; i<=n; i++)
    {
        int u=lower_bound(ap.begin(), ap.end(), seq[i].fi)-ap.begin();
        int v=lower_bound(ap.begin(), ap.end(), seq[i].se)-ap.begin();
        pt_type[u]=1;
        pt_id[u]=i;
        L_idx[i]=u;
        pt_type[v]=-1;
        pt_id[v]=i;
        R_idx[i]=v;
    }

    segment st(lim+5);
    st.clear_tree();

    for(int i=1; i<=n; i++)
    {
        st.upd(1,1,lim, L_idx[i]+1, lim, 1);
        st.upd(1,1,lim, R_idx[i]+1, lim, -1);
    }
    int op = st.st[1].val;

    int idx_ans = op;
    for(int i=1; i<=op; i++) res[i]=0;
    
    int l = 0;
    int r = lim - 1;
    int cnt = 0;
    
    while(l < r)
    {
        int type_left = pt_type[l];
        int id_left = pt_id[l];
        int type_right = pt_type[r];
        int id_right = pt_id[r];
        if(type_left == -1 && type_right == 1)
        {
            int y_idx = R_idx[id_left];
            int u_idx = L_idx[id_right];
            
            if(y_idx > u_idx)
            {
                r--;
                l++;
                continue;
            }
            cnt++;
            pt_type[y_idx] = 1;
            pt_type[u_idx] = -1;
            swap(seq[id_left].se, seq[id_right].fi);
            swap(R_idx[id_left], L_idx[id_right]);
            st.upd(1,1,lim,y_idx+1,u_idx,2);
            int new_gh = st.st[1].val;
            if(new_gh > idx_ans)
            {
                for(int i=idx_ans+1; i<= new_gh; ++i) res[i]=cnt;
                idx_ans = new_gh;
            }
            r--;
            l++;
        }
        else if(type_right == -1) r--;
        else if(type_left == 1) l++;
    }
    
    for(int i=1; i<=q; i++) cout<<res[query[i]]<<' ';
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if(fopen(task".INP", "r"))
    {
        freopen(task".INP", "r", stdin);
        freopen(task".OUT", "w", stdout);
    }
    int t=1;
    while(t--) solve();
}