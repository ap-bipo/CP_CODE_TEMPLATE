#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define in insert
#define task "I"
using namespace std;

const int N = 502;
const int P = 2e4+20; 
const int M = 2500005;

int a[N][N];
bitset<P> b[P];   
bitset<P> here[P]; 
int nxt[P];
bool visited[P];
pair<int,int> q[M];
int idx[]={0,0,-1,1};
int idy[]={1,-1,0,0};
int conv[N][N];
int id = 0;
int n,m,k;

bool kt(int x,int y)
{
    if(1<=x && x<=n && 1<=y && y<=m && a[x][y] == 1) return true;
    else return false;
}

void solve()
{
    memset(visited,false,sizeof(visited));
    cin>>n>>m;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
    {
        cin>>a[i][j];
        if(a[i][j] == 1)
        {
            conv[i][j] = ++id;
            b[id].set(id,1);
            nxt[id] = id;
            here[id].set(id,1);

        }
    }
    cin>>k;
    for(int i=1;i<=k;i++) cin>>q[i].fi>>q[i].se;
    if(id <= 1)
    {
        cout << 0;
        return;
    }
    int sl=0;
    for(int i=1;i<=k;i++)
    {
        if(a[q[i].fi][q[i].se] == 0) continue;
        int cur_id = conv[q[i].fi][q[i].se];
        bool any = false;
        for(int j=0;j<4;j++)
        {
            int n_x = q[i].fi+idx[j];
            int n_y = q[i].se+idy[j];
            if(kt(n_x,n_y)== false) continue;
            if(a[n_x][n_y] == false) continue;
            int adj_id = conv[n_x][n_y];
            if(nxt[adj_id] == 0) continue;
            any = true;
            if(nxt[cur_id] == 0)
            {
                // neu cur_id rong -> gan voi adj_id
                nxt[cur_id] = nxt[adj_id];
            }else
            {
                // neu cur_id khong rong -> ghep voi adj_id
                here[nxt[cur_id]] |= here[nxt[adj_id]]; 
            }    
            nxt[adj_id] = 0;
        }
        if(any==true)
        {
            if(visited[cur_id] == true) continue;
            b[cur_id] |= here[nxt[cur_id]];
            if(b[cur_id].count() == id)
            {
                visited[cur_id] = true; 
                sl++;
                if(sl == id)
                {
                    cout<<i;
                    return ;
                }
            }
        }
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