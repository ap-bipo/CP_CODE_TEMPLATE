#include<bits/stdc++.h>
#define ll long long
#define task "task"
#define pb push_back
#define fi first
#define se second
using namespace std;

const int N = 2e5+20;
int n,k;

struct Point
{
    double x,y;
    bool operator<(const Point& o)
    {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
} a[N];

double dis(Point A, Point B) {
    return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y));
}

double ccw(Point O, Point A, Point B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y)*(B.x - O.x);
}

double cal(Point p)
{
    double res = 0;
    for(int i = 1; i <= n; i++) res += dis(p, a[i]);
    return res;
}


pair<Point,double> bfs(Point op)
{
    vector<pair<double,int>> v;
    int lim = min(100,k);
    for(int i=1;i<=n;i++)  v.pb({dis(a[i],op),i});
    nth_element(v.begin(), v.begin()+lim, v.end());
    Point cur = {0.0, 0.0};
    for(int i = 0; i < lim; i++)
    {
        cur.x += a[v[i].se].x;
        cur.y += a[v[i].se].y;
    }
    cur.x /= lim;
    cur.y /= lim;
    double st = 100;
    double cw = 0;
    for(int i=0;i<lim;i++) cw += dis(a[v[i].se],cur); 
    double dx[] = {0, 0, -1, 1, -1, 1, -1, 1};
    double dy[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    while(st>1e-7)
    {
        bool ok = 0;
        for(int i=0;i<8;i++)
        {
            Point nx = {cur.x + dx[i] * st, cur.y + dy[i] * st};
            double nw = 0;
            for(int j=0;j<lim;j++) nw += dis(a[v[j].se],nx); 
            if(nw<cw)
            {
                cw=nw;
                cur=nx;
                ok=1;
                break; 
            }
        }
        if(!ok) st*=0.6;
    }
    return {cur,cw};
}

void solve()
{  
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
    double ans = 1e9;
    Point ans_p = {0,0};

    for(int i=1;i<=min(300,n);i++)
    {   
        pair<Point,double> cur = bfs({a[i].x,a[i].y});
        if(ans > cur.se)
        {
            ans = cur.se;
            ans_p = cur.fi;
        }
    }
    cout<<fixed<<setprecision(6)<<ans_p.x<<' '<<ans_p.y;
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
