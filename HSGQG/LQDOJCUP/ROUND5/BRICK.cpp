#include<bits/stdc++.h>
#define ll long long
#define task "brick"
using namespace std;

const int N = 5005;
const ll MOD = 1e9+22071997;


int n, m, q;
string s;
int dp_pre[N][N][2];
int dp_las[N][N][2];
ll pre[N]; 
ll suff[N];

bool kt(char c, int num)
{
    if(c == 'A') return true;
    else if(c == 'O' && num%2==1) return true;
    else if(c == 'E' && num%2==0) return true;
    return false;
}

void solve()
{
    cin>>n>>m>>q>>s;
    s='#'+s;
    for(int j=1;j<=m;j++)
    {
        if(kt(s[1],j)) dp_pre[1][j][0] = 1;
        if(kt(s[n],j)) dp_las[n][j][0] = 1;
    }
    ll cnt_pre = 0;

    for(int j=1;j<=m;j++)
    {
        if(kt(s[2],j))
        {
            dp_pre[2][j][0] = cnt_pre;
            if(kt(s[1],j)) dp_pre[2][j][1] = 1;
        }
        if(kt(s[1],j)) cnt_pre++;
    }

    ll cnt_las = 0;
    for(int j=1;j<=m;j++)
    {
        if(kt(s[n-1],j))
        {
            dp_las[n-1][j][0] = cnt_las;
            if(kt(s[n],j)) dp_las[n-1][j][1] = 1;
        }
        if(kt(s[n],j)) cnt_las++;
    }

    for(int i=3;i<=n;i++)
    {
        pre[0] = 0;
        for(int z=1;z<=m;z++)
        {
            ll all_z = (1LL*dp_pre[i-1][z][0]+dp_pre[i-1][z][1])%MOD;
            pre[z] = (pre[z-1]+all_z)%MOD;
        }
        suff[m+1] = 0;
        for(int z=m;z>=1;z--)
        {
            suff[z] = (suff[z+1]+dp_pre[i-1][z][1]) % MOD;
        }
        for(int j=1;j<=m;j++)
        {
            if(kt(s[i],j) == true)
            {
                dp_pre[i][j][0] = pre[j-1];
                ll be_hon=suff[j+1];
                ll bang=(1LL*dp_pre[i-1][j][0]+dp_pre[i-1][j][1])%MOD;
                dp_pre[i][j][1] = (be_hon+bang) % MOD;
            }
        }
    }

    for(int i=n-2;i>=1;i--)
    {
        pre[0]=0;
        for(int z=1;z<=m;z++) pre[z] = (pre[z-1]+(1LL*dp_las[i+1][z][0]+dp_las[i+1][z][1]) % MOD) % MOD;
        suff[m+1]=0;
        for(int z=m;z>=1;z--) suff[z] = (suff[z+1]+dp_las[i+1][z][1]) % MOD;
        for(int j=1;j<=m;j++)
        {
            if(kt(s[i],j) == true)
            {
                dp_las[i][j][0] = pre[j-1];
                ll be_hon = suff[j+1];
                ll bang = (1LL*dp_las[i+1][j][0]+dp_las[i+1][j][1])%MOD;
                dp_las[i][j][1] = (be_hon+bang)%MOD;
            }
        }
    }
    while(q--)
    {
        int id;
        ll x;
        cin>>id>>x;
        if(kt(s[id], x) == false)
        {
            cout<<0<<'\n';
            continue;
        }
        if(id == 1)
        {
            cout<<dp_las[1][x][1]<<'\n';
            continue;
        }
        if(id == n)
        {
            cout<<dp_pre[n][x][1]<<'\n';
            continue;
        }
        ll ans=(dp_pre[id][x][1]%MOD*(dp_las[id][x][0]+dp_las[id][x][1])%MOD+dp_pre[id][x][0]%MOD*dp_las[id][x][1]%MOD)%MOD;
        cout<<ans<<'\n';
    }
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
    int t=1;
    while(t--) solve();
}