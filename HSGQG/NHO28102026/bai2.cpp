#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2")
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define in insert
#define task "task"
using namespace std;

const int N = 200005;

int n; 
ll A, B;

struct Edge { int to; ll w, c; };
vector<Edge> adj[N];

bool removed_node[N];
int par_[N], sz_[N];
int order_[N], olen;
int stkU[N], stkP_[N];
ll stkX[N], stkY[N];

struct Pt { ll x, y; int tag; };
Pt allPts[N];
int rk_[N], hi_[N];
ll ys_[N];

Pt subPts[N];
int subRk[N], subHi[N];

ll bitV[N];
int bitT[N], curT = 0;
ll answer;

inline void bitAdd(int i, int ysz) {
    while (i <= ysz) {
        if (bitT[i] != curT) { bitT[i] = curT; bitV[i] = 1; }
        else bitV[i]++;
        i += i & -i;
    }
}

inline ll bitQ(int i) {
    ll s = 0;
    while (i > 0) {
        if (bitT[i] == curT) s += bitV[i];
        i -= i & -i;
    }
    return s;
}

int getCentroid(int start)
{
    olen = 0;
    order_[olen++] = start;
    par_[start] = 0;
    for (int i = 0; i < olen; ++i)
    {
        int u = order_[i];
        for (auto &e : adj[u])
        {
            int v = e.to;
            if (v != par_[u] && !removed_node[v]) { par_[v] = u; order_[olen++] = v; }
        }
    }
    for (int i = 0; i < olen; ++i) sz_[order_[i]] = 1;
    for (int i = olen - 1; i > 0; --i) sz_[par_[order_[i]]] += sz_[order_[i]];
    
    int cen = start, best = olen + 1;
    for (int i = 0; i < olen; ++i)
    {
        int u = order_[i];
        int mx = olen - sz_[u];
        for (auto &e : adj[u])
        {
            int v = e.to;
            if (!removed_node[v] && par_[v] == u && sz_[v] > mx) mx = sz_[v];
        }
        if (mx < best) { best = mx; cen = u; }
    }
    return cen;
}

void decompose(int start) {
    int c = getCentroid(start);
    removed_node[c] = true;

    int m = 0;
    allPts[m++] = {0, 0, -1};
    int tag = 0;
    for (auto &e : adj[c])
    {
        int v = e.to;
        if (removed_node[v]) continue;
        int top = 0;
        stkU[top] = v; stkP_[top] = c; stkX[top] = e.w; stkY[top] = e.c; top++;
        while (top > 0)
        {
            --top;
            int u = stkU[top], pp = stkP_[top];
            ll x = stkX[top], y = stkY[top];
            allPts[m++] = {x, y, tag};
            for (auto &ne : adj[u]) {
                int to = ne.to;
                if (to != pp && !removed_node[to]) {
                    stkU[top] = to; stkP_[top] = u;
                    stkX[top] = x + ne.w; stkY[top] = y + ne.c; top++;
                }
            }
        }
        ++tag;
    }

    sort(allPts, allPts + m, [](const Pt &a, const Pt &b) { return a.x < b.x; });

    int ysz = 0;
    for (int i = 0; i < m; ++i) ys_[ysz++] = allPts[i].y;
    sort(ys_, ys_ + ysz);
    ysz = unique(ys_, ys_ + ysz) - ys_;

    for (int i = 0; i < m; ++i)
    {
        rk_[i] = lower_bound(ys_, ys_ + ysz, allPts[i].y) - ys_ + 1;
        ll Y = B - allPts[i].y;
        hi_[i] = (Y < 0) ? 0 : (int)(upper_bound(ys_, ys_ + ysz, Y) - ys_);
    }

    if (m <= 40) {
        ll cnt = 0;
        for (int i = 0; i < m; ++i)
            for (int j = i + 1; j < m; ++j)
                if (allPts[i].x + allPts[j].x <= A && allPts[i].y + allPts[j].y <= B) cnt++;
        answer += cnt;
    } else {
        ++curT;
        int p = 0; ll total = 0;
        for (int i = m - 1; i >= 0; --i)
        {
            ll X = A - allPts[i].x;
            while (p < m && allPts[p].x <= X) { bitAdd(rk_[p], ysz); ++p; }
            total += bitQ(hi_[i]);
        }
        ll self = 0;
        for (int i = 0; i < m; ++i)
            if (allPts[i].x <= A - allPts[i].x && allPts[i].y <= B - allPts[i].y) ++self;
        answer += (total - self) / 2;
    }

    static int cntArr[N], ptrArr[N], flatIdx[N];
    for (int t = 0; t <= tag; ++t) cntArr[t] = 0;
    for (int i = 0; i < m; ++i)
    {
        int t = allPts[i].tag;
        if (t >= 0) cntArr[t + 1]++;
    }
    for (int t = 0; t < tag; ++t) cntArr[t + 1] += cntArr[t];
    for (int t = 0; t <= tag; ++t) ptrArr[t] = cntArr[t];
    for (int i = 0; i < m; ++i)
    {
        int t = allPts[i].tag;
        if (t >= 0) flatIdx[ptrArr[t]++] = i;
    }

    for (int t = 0; t < tag; ++t)
    {
        int bm = cntArr[t + 1] - cntArr[t];
        if (bm < 2) continue;
        if (bm <= 40) {
            ll cnt = 0;
            for (int a = 0; a < bm; ++a)
            {
                int ia = flatIdx[cntArr[t] + a];
                for (int b = a + 1; b < bm; ++b)
                {
                    int ib = flatIdx[cntArr[t] + b];
                    if (allPts[ia].x + allPts[ib].x <= A && allPts[ia].y + allPts[ib].y <= B) cnt++;
                }
            }
            answer -= cnt;
            continue;
        }
        for (int i = 0; i < bm; ++i) {
            int idx = flatIdx[cntArr[t] + i];
            subPts[i] = allPts[idx];
            subRk[i] = rk_[idx];
            subHi[i] = hi_[idx];
        }
        ++curT;
        int p = 0; ll total = 0;
        for (int i = bm - 1; i >= 0; --i) {
            ll X = A - subPts[i].x;
            while (p < bm && subPts[p].x <= X) { bitAdd(subRk[p], ysz); ++p; }
            total += bitQ(subHi[i]);
        }
        ll self = 0;
        for (int i = 0; i < bm; ++i)
            if (subPts[i].x <= A - subPts[i].x && subPts[i].y <= B - subPts[i].y) ++self;
        answer -= (total - self) / 2;
    }

    for (auto &e : adj[c]) {
        int v = e.to;
        if (!removed_node[v]) decompose(v);
    }
}

void solve()
{
    cin >> n >> A >> B;
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v; ll w, c;
        cin >> u >> v >> w >> c;
        adj[u].pb({v, w, c});
        adj[v].pb({u, w, c});
    }
    
    answer = 0;
    curT = 0;
    decompose(1);
    cout << answer << '\n';
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
    
    return 0;
}