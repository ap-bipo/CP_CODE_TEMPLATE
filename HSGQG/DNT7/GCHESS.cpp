#include<bits/stdc++.h>
#define task "GCHESS"
#define fi first
#define se second
#define ll long long
using namespace std;

const int N= 1e6+20;
int n,m,k;
int x_pawn;
int y_pawn;
pair<int,int> ma[N];
int idx[]={1,-1,2,-2,2,-2,-1,1};
int idy[]={2,2,1,1,-1,-1,-2,-2};

struct node
{
    int x,y,d;
};

bool kt(int x,int y)
{
    if(x>=1 && x<=n && y>=1 && y<=m) return true;
    else return false;
}

void solve()
{
    cin>>n>>m>>k;
    cin>>x_pawn>>y_pawn;
    int dp[n+5][m+5];
    bool knight[n+5][m+5];
    int pawn_col[m+5];
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) 
    {
        dp[i][j] = 1e9;
        knight[i][j] = false;
    }
    
    queue<node> q;

    for(int i=1;i<=k;i++)
    {
        cin>>ma[i].fi>>ma[i].se;
        knight[ma[i].fi][ma[i].se] = true;
        dp[ma[i].fi][ma[i].se] = 0;
        q.push({ma[i].fi,ma[i].se,0});
    }

    while(!q.empty())
    {
        node u = q.front();
        q.pop();
        for(int i=0; i<8; i++)
        {
            int x = u.x + idx[i];
            int y = u.y + idy[i];
            if(kt(x,y) == true)
            {
                if(dp[x][y] > u.d + 1)
                {
                    dp[x][y] = u.d+1;
                    q.push({x,y,u.d+1});
                }
            }
        }
    }

    bool dir = true;
    
    for(int i=1;i<N;i++)
    {
        // ptrinh
        if(x_pawn == n) dir = false;
        else if(x_pawn == 1) dir = true;
        if(dir == true) x_pawn++;
        else x_pawn--;

        if(i == 1)
        {
            bool ap = false;
            for(int j=0;j<8;j++)
            {
                int u = x_pawn + idx[j];
                int v = y_pawn + idy[j];
                if(kt(u,v) == true)
                {
                    if(knight[u][v] == true) 
                    {
                        ap = true;
                        break;
                    }
                }
            }
            if(ap==true)
            {
                cout<<i;
                return ;
            }
        }else
        {
            if(k==1)
            {
                bool ap = false;
                for(int j=0;j<8;j++)
                {
                    int u = x_pawn + idx[j];
                    int v = y_pawn + idy[j];
                    if(kt(u,v) == true)
                    {
                        if(dp[u][v]%2 != i%2 && dp[u][v] < i)
                        {
                            ap = true;
                        }
                    }
                }
                if(ap==true)
                {
                    cout<<i;
                    return ;
                }
            }
            else
            {
                bool ap = false;
                for(int j=0;j<8;j++)
                {
                    int  u = x_pawn + idx[j];
                    int v = y_pawn + idy[j];
                    if(kt(u,v) == true)
                    {
                        if(dp[u][v] < i)
                        {
                            ap = true;
                        }
                    }
                }
                if(ap==true)
                {
                    cout<<i;
                    return ;
                }              
            }
        }
    }
    cout<<-1;
    return ;
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