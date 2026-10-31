#include<bits/stdc++.h>
#define ll long long 
#define task "THAPPHAO"
using namespace std;


const int N = 1e5+20;
const int M = 17;

int n,q;
string s;
ll pre[N];

struct sparse{
    struct block{
       ll val_min;
       ll val_max;
    };
    block table[N][M];
    void build(ll pre[],int n)
    {
        for(int i=1;i<=n;i++)
        {
 
            table[i][0].val_max=pre[i];
            table[i][0].val_min=pre[i];
        }
        for(int j=1;j<=log2(n);j++)
        {
 
            for(int i=1;i+(1<<j)-1<=n;i++)
            {
                table[i][j].val_min=min(table[i][j-1].val_min,table[i+(1<<(j-1))][j-1].val_min);
                table[i][j].val_max=max(table[i][j-1].val_max,table[i+(1<<(j-1))][j-1].val_max);
            }
        }
 
    }
    ll get_min(int l,int r)
    {
 
        int j=(int) log2(r-l+1);
        return min(table[l][j].val_min,table[r-(1<<j)+1][j].val_min);
    }
    ll get_max(int l,int r)
    {
        int j=(int) log2(r-l+1);
        return max(table[l][j].val_max,table[r-(1<<j)+1][j].val_max);
    }
} tab;

void solve()
{
    cin>>n>>q;
    cin>>s;
    s = '#' + s;
    pre[n+1] = 0;
    for(int i=n;i>=1;i--)
    {
        pre[i] = pre[i+1];
        if(s[i] == 'R') pre[i]--;
        else pre[i]++;
    }
    tab.build(pre,n+1);
    for(int i=1;i<=q;i++)
    {
        int l,r; cin>>l>>r;
        cout<<tab.get_max(l,r+1) - tab.get_min(l,r+1)<<'\n';
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