#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "A"
#define in insert
using namespace std;

const int N = 500005;
set<int> s;
map<ll,int> conv;

struct SegmentTree {
    struct Node {
        int max_val;
        int lazy_add;
        bool lazy_set_zero;
    };
    vector<Node> st;
    
    SegmentTree(int n) {
        st.assign(4 * n + 5, {0, 0, false});
    }

    void down(int id) {
        if(st[id].lazy_set_zero)
        {
            st[id*2].max_val = 0;
            st[id*2].lazy_add = 0;
            st[id*2].lazy_set_zero = true;

            st[id*2+1].max_val = 0;
            st[id*2+1].lazy_add = 0;
            st[id*2+1].lazy_set_zero = true;

            st[id].lazy_set_zero = false;
        }
        if(st[id].lazy_add > 0)
        {
            int t = st[id].lazy_add;
            st[id*2].max_val += t;
            st[id*2].lazy_add += t;

            st[id*2+1].max_val += t;
            st[id*2+1].lazy_add += t;

            st[id].lazy_add = 0;
        }
    }

    void upd_set_zero(int id, int l, int r, int u, int v) {
        if (u > r || v < l) return;
        if (u <= l && r <= v) {
            st[id].max_val = 0;
            st[id].lazy_add = 0;
            st[id].lazy_set_zero = true;
            return;
        }
        down(id);
        int mid = (l + r) / 2;
        upd_set_zero(id*2, l, mid, u, v);
        upd_set_zero(id*2+1, mid+1, r, u, v);
        st[id].max_val = max(st[id*2].max_val, st[id*2+1].max_val);
    }

    void upd_add(int id, int l, int r, int u, int v, int val) {
        if (u > r || v < l) return;
        if (u <= l && r <= v) {
            st[id].max_val += val;
            st[id].lazy_add += val;
            return;
        }
        down(id);
        int mid = (l + r) / 2;
        upd_add(id*2, l, mid, u, v, val);
        upd_add(id*2+1, mid+1, r, u, v, val);
        st[id].max_val = max(st[id*2].max_val, st[id*2+1].max_val);
    }

    int get_max()
    {
        return st[1].max_val; 
    }
};

struct query
{
    int d;
    int l;
    int r;
};

struct cmp
{
    bool operator()(const query& a, const query& b) const {return a.d < b.d;}
};



void solve()
{
    int n, m;
    cin>>n>>m;
    vector<vector<pair<int, int>>> days(n + 1);
    vector<int> vals;
    for (int i = 1; i <= m; i++)
    {
        int d, l, r; 
        cin >> d >> l >> r;
        days[d].push_back({l, r});
        vals.push_back(l);
        vals.push_back(r); 
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    int lim = vals.size() - 1;
    SegmentTree st(lim > 0 ? lim : 1); 
    vector<ll> res;

    for (int i = n; i >= 1; i--)
    {
        if (days[i].empty()) 
        {
            if (lim > 0) st.upd_set_zero(1, 1, lim, 1, lim);
        } 
        else 
        {
            sort(days[i].begin(), days[i].end());
            int last_R = 0;
            for (auto seg : days[i]) 
            {
                int cur_L = lower_bound(vals.begin(), vals.end(), seg.first) - vals.begin() + 1;
                int cur_R = lower_bound(vals.begin(), vals.end(), seg.second) - vals.begin(); 
                if (cur_L > last_R + 1) {
                    st.upd_set_zero(1, 1, lim, last_R + 1, cur_L - 1);
                }
                st.upd_add(1, 1, lim, cur_L, cur_R, 1);
                last_R = max(last_R, cur_R);
            }
            if (last_R < lim) {
                st.upd_set_zero(1, 1, lim, last_R + 1, lim);
            }
        }
        res.push_back(st.get_max());
    }  

    reverse(res.begin(), res.end());
    for (ll x : res) cout << x << '\n';
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