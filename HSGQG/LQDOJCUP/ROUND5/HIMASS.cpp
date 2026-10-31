#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "himass"
using namespace std;

const int N=1e5+20;
const int M=16;
const int INF=1e9;

vector<int> pos[M];
int dp[(1<<15)][M];
int a[N];
int n,m;
int lim = -1; 

int get(int i, int lim, int cnt)
{
    if(cnt==0) return lim;
    int l=0;
    int r=(int)pos[i].size()-1;
    int best_pos=-1;
    while(l<=r)
    {
        int mid = (l + r) >> 1;
        if(pos[i][mid]>lim)
        {
            best_pos=mid;
            r=mid-1;
        }
        else l=mid+1;
    }
    if(best_pos==-1) return INF;
    if(best_pos+cnt-1>=(int)pos[i].size()) return INF;
    return pos[i][best_pos+cnt-1];
}

bool kt(int k)
{
    int gh=(1<<m);
    for(int mask=0; mask<gh;mask++) for(int c=0;c<=m;c++) dp[mask][c]=INF;
    dp[0][0]=0;
    for(int mask=0;mask<gh;mask++)
    {
        int op=__builtin_popcount(mask);
        for(int c=0;c<=op;c++)
        {
            int lim=dp[mask][c];
            if(lim==INF) continue;
            for(int i=1;i<=m;i++)
            {
                if(((mask>>(i-1))&1)==0)
                {
                    int n_mask=(mask|(1<<(i-1)));
                    int next_k=get(i,lim,k);
                    if(next_k<dp[n_mask][c]) dp[n_mask][c]=next_k;
                    int next_k1=get(i,lim,k+1);
                    if(next_k1<dp[n_mask][c+1]) dp[n_mask][c+1]=next_k1;
                }
            }
        }
    }
    lim=-1;
    for(int c=m;c>=0;c--)
    {
        if(dp[gh-1][c]<=n)
        {
            lim = c;
            return true;
        }
    }
    return false;
}

void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        pos[a[i]].pb(i);
    }

    int l=0;
    int r=n/m;
    int ans=0;
    while(l<=r)
    {
        int mid = (l+r)>>1;
        if(kt(mid)==true)
        {
            ans = max(ans,mid*m+lim);
            l=mid+1;
        }
        else r=mid-1;
    }
    cout<<ans<<'\n';
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if(fopen(task".inp","r"))
    {
        freopen(task".inp","r",stdin);
        freopen(task".out","w",stdout);
    }
    int t = 1;
    while(t--) solve();
}