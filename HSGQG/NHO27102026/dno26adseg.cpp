#include<bits/stdc++.h>
#define ll long long 
#define pb push_back
#define fi first
#define se second
#define task "task"
using namespace std;

const int N = 1e5 + 20;
const ll INF = 1e18;

int n, q;
ll a[N];

struct Query
{
    int type, l, r, k;
    ll v;
};
vector<Query> qr;

void sub1()
{
    for (int id=0;id<(int)qr.size();id++)
    {
        Query x = qr[id];
        if (x.type == 1)
        {
            a[x.l] = x.v;
        }
        else if (x.type == 2)
        {
            for (int i=x.l;i<=x.r;i++) a[i] = -a[i];
        }
        else
        {
            int k = x.k;
            vector<ll> dp0(k + 1, 0), dp1(k + 1, -INF);
            for (int i=x.l;i<=x.r;i++)
            {
                vector<ll> nxt0(k + 1, 0), nxt1(k + 1, -INF);
                for (int j=1;j<=k;j++)
                {
                    nxt1[j] = max(dp1[j], dp0[j - 1]) + a[i];
                    nxt0[j] = max(dp0[j], nxt1[j]);
                }
                dp0 = nxt0;
                dp1 = nxt1;
            }
            cout << dp0[k] << "\n";
        }
    }
}

struct NodeBL
{
    ll dp[2][2][11];
    NodeBL()
    {
        for (int cl=0;cl<2;cl++)
            for (int cr=0;cr<2;cr++)
                for (int j=0;j<=10;j++)
                    dp[cl][cr][j] = (j == 0 && cl == 0 && cr == 0) ? 0 : -INF;
    }
};

NodeBL merge_bl(const NodeBL& L, const NodeBL& R)
{
    NodeBL res;
    for (int cl=0;cl<2;cl++)
    {
        for (int cr=0;cr<2;cr++)
        {
            for (int jl=0;jl<=10;jl++)
            {
                for (int ml=0;ml<2;ml++)
                {
                    if (L.dp[cl][ml][jl] <= -INF / 2) continue;
                    for (int mr=0;mr<2;mr++)
                    {
                        for (int jr=0;jr<=10-jl;jr++)
                        {
                            if (R.dp[mr][cr][jr] <= -INF / 2) continue;
                            int tk = jl + jr - (ml == 1 && mr == 1 ? 1 : 0);
                            if (tk >= 0 && tk <= 10)
                            {
                                res.dp[cl][cr][tk] = max(res.dp[cl][cr][tk], L.dp[cl][ml][jl] + R.dp[mr][cr][jr]);
                            }
                        }
                    }
                }
            }
        }
    }
    return res;
}

NodeBL st[17][N];

void sub3()
{
    for (int i=1;i<=n;i++)
    {
        st[0][i] = NodeBL();
        st[0][i].dp[0][0][0] = 0;
        st[0][i].dp[1][1][1] = a[i];
    }
    for (int j=1;j<17;j++)
    {
        for (int i=1;i+(1<<j)-1<=n;i++)
        {
            st[j][i] = merge_bl(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }
    for (int id=0;id<(int)qr.size();id++)
    {
        Query x = qr[id];
        if (x.type == 3)
        {
            int cur = x.l;
            int rem = x.r - x.l + 1;
            bool ok = true;
            NodeBL ans;
            for (int j=16;j>=0;j--)
            {
                if (rem & (1 << j))
                {
                    if (ok)
                    {
                        ans = st[j][cur];
                        ok = false;
                    }
                    else
                    {
                        ans = merge_bl(ans, st[j][cur]);
                    }
                    cur += (1 << j);
                }
            }
            ll best = 0;
            for (int cl=0;cl<2;cl++)
                for (int cr=0;cr<2;cr++)
                    for (int j=0;j<=x.k;j++)
                        best = max(best, ans.dp[cl][cr][j]);
            cout << best << "\n";
        }
    }
}

ll bit[N];

void update_bit(int idx, ll val)
{
    for (;idx<=n;idx+=idx&-idx) bit[idx] += val;
}

ll get_bit(int idx)
{
    ll s = 0;
    for (;idx>0;idx-=idx&-idx) s += bit[idx];
    return s;
}

void sub4()
{
    for (int i=1;i<=n;i++) update_bit(i, a[i]);
    for (int id=0;id<(int)qr.size();id++)
    {
        Query x = qr[id];
        if (x.type == 1)
        {
            ll diff = x.v - a[x.l];
            a[x.l] = x.v;
            update_bit(x.l, diff);
        }
        else if (x.type == 3)
        {
            cout << get_bit(x.r) - get_bit(x.l - 1) << "\n";
        }
    }
}

struct NodeSeg
{
    ll sum, mx_pre, mx_suf, mx_sub;
    ll mn_pre, mn_suf, mn_sub;
    bool rev;
    void apply()
    {
        rev ^= 1;
        sum = -sum;
        swap(mx_pre, mn_pre); mx_pre = -mx_pre; mn_pre = -mn_pre;
        swap(mx_suf, mn_suf); mx_suf = -mx_suf; mn_suf = -mn_suf;
        swap(mx_sub, mn_sub); mx_sub = -mx_sub; mn_sub = -mn_sub;
    }
} seg[N * 4];

NodeSeg merge_seg(const NodeSeg& l, const NodeSeg& r)
{
    NodeSeg res;
    res.rev = false;
    res.sum = l.sum + r.sum;
    res.mx_pre = max(l.mx_pre, l.sum + r.mx_pre);
    res.mx_suf = max(r.mx_suf, r.sum + l.mx_suf);
    res.mx_sub = max({l.mx_sub, r.mx_sub, l.mx_suf + r.mx_pre});
    res.mn_pre = min(l.mn_pre, l.sum + r.mn_pre);
    res.mn_suf = min(r.mn_suf, r.sum + l.mn_suf);
    res.mn_sub = min({l.mn_sub, r.mn_sub, l.mn_suf + r.mn_pre});
    return res;
}

void push(int id)
{
    if (seg[id].rev)
    {
        seg[id * 2].apply();
        seg[id * 2 + 1].apply();
        seg[id].rev = false;
    }
}

void build(int id, int l, int r)
{
    if (l == r)
    {
        seg[id] = {a[l], a[l], a[l], a[l], a[l], a[l], a[l], false};
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    seg[id] = merge_seg(seg[id * 2], seg[id * 2 + 1]);
}

void upd_pt(int id, int l, int r, int p, ll v)
{
    if (l == r)
    {
        seg[id] = {v, v, v, v, v, v, v, false};
        return;
    }
    push(id);
    int mid = (l + r) / 2;
    if (p <= mid) upd_pt(id * 2, l, mid, p, v);
    else upd_pt(id * 2 + 1, mid + 1, r, p, v);
    seg[id] = merge_seg(seg[id * 2], seg[id * 2 + 1]);
}

void upd_rev(int id, int l, int r, int u, int v)
{
    if (v < l || r < u) return;
    if (u <= l && r <= v)
    {
        seg[id].apply();
        return;
    }
    push(id);
    int mid = (l + r) >> 1;
    upd_rev(id * 2, l, mid, u, v);
    upd_rev(id * 2 + 1, mid + 1, r, u, v);
    seg[id] = merge_seg(seg[id * 2], seg[id * 2 + 1]);
}

NodeSeg get_seg(int id, int l, int r, int u, int v)
{
    if (u <= l && r <= v) return seg[id];
    push(id);
    int mid = (l + r) / 2;
    if (v <= mid) return get_seg(id * 2, l, mid, u, v);
    if (u > mid) return get_seg(id * 2 + 1, mid + 1, r, u, v);
    return merge_seg(get_seg(id * 2, l, mid, u, v), get_seg(id * 2 + 1, mid + 1, r, u, v));
}

void sub2()
{
    build(1, 1, n);
    for (int id=0;id<(int)qr.size();id++)
    {
        Query x = qr[id];
        if (x.type == 1) upd_pt(1, 1, n, x.l, x.v);
        else if (x.type == 2) upd_rev(1, 1, n, x.l, x.r);
        else
        {
            NodeSeg res = get_seg(1, 1, n, x.l, x.r);
            cout << max(0LL, res.mx_sub) << "\n";
        }
    }
}

void solve()
{
    cin >> n >> q;
    bool ok_pos = true;
    for (int i=1;i<=n;i++)
    {
        cin >> a[i];
        if (a[i] <= 0) ok_pos = false;
    }
    bool has1 = false, has2 = false, ok_k1 = true;
    for (int i=1;i<=q;i++)
    {
        Query x;
        cin >> x.type;
        if (x.type == 1)
        {
            cin >> x.l >> x.v;
            has1 = true;
            if (x.v <= 0) ok_pos = false;
        }
        else if (x.type == 2)
        {
            cin >> x.l >> x.r;
            has2 = true;
        }
        else
        {
            cin >> x.l >> x.r >> x.k;
            if (x.k > 1) ok_k1 = false;
        }
        qr.pb(x);
    }

    if (n <= 300 && q <= 300) sub1();
    else if (ok_k1) sub2();
    else if (!has1 && !has2) sub3();
    else if (!has2 && ok_pos) sub4();
    else return ;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen(task".INP", "r")) {
        freopen(task".INP", "r", stdin);
        freopen(task".OUT", "w", stdout);
    }
    int t = 1;
    while (t--) solve();
    return 0;
}