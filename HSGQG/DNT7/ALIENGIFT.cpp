/*
dp[N][MASK]

-> max toi i va lua chon la MASK
THOA MAN: mask ko co 2 bit 1 lien tiep
THOA MAN: n_mask and mask == 0


for(i -> n)
for 2 lan mask
j thoa man:    j+l[j] <= i <= j+r[j];
voi moi mask luu 1 dp? -> 4*N*mask

dp[i][mask] = max(dp[j][pre_mask])
*/

#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define in insert
#define task "ALIENGIFT"
using namespace std;

const int N = 1e5+20;

ll n;
ll dp[N][(1LL<<4)][2];
struct query
{
    ll l,r;
    ll a[4];
};

struct node
{
    ll val;
    ll l,r;
    bool operator<(const node& other) const
    {
        if(val != other.val) return val > other.val; 
        if(r != other.r) return r < other.r;
        return l < other.l;
    }
};

multiset<node> st[16][2];

bool kt(int mask, int n_mask)
{
    if(mask & n_mask) return false;        
    if(mask & (mask >> 1)) return false;    
    if(n_mask & (n_mask >> 1)) return false;     
    return true;
}

ll get_sum(query &x, int mask)
{
    ll sum = 0;
    for(int i=0;i<4;i++) if((((mask>>i)&1)==true)) sum += x.a[i];
    return sum;
}

void solve()
{
    cin>>n;
    vector<query> a(n+2);
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].l>>a[i].r>>a[i].a[0]>>a[i].a[1]>>a[i].a[2]>>a[i].a[3];
    }
    

    
    for(int i=0;i<N;i++) for(int j=0;j<(1LL<<4);j++) for(int z=0;z<=1;z++) dp[i][j][z]=-1e18;
    
    for(int mask = 0;mask<(1LL<<4);mask++)
    {
        if(kt(mask,0) == true)
        {
            int picked = (mask > 0 ? 1 : 0);
            dp[1][mask][picked] = max(dp[1][mask][picked],get_sum(a[1],mask));
            int left = min(n+1,1+a[1].l);
            int right = min(n+1,1+a[1].r);
            st[mask][picked].in({dp[1][mask][picked],left,right});
            //st[mask].upd(1,1,n+1,left,right,dp[1][mask]);
        }
    }

    for(int i=2;i<=n;i++)
    {
        for(int mask = 0;mask < (1LL<<4);mask++)
        {
            for(int picked=0;picked<=1;picked++)
            {
                if(kt(mask,0) == false) continue;
                ll op = -1e18;
                multiset<node>::iterator it;
                for(it = st[mask][picked].begin(); it != st[mask][picked].end(); )
                {
                    if(it->r < i) it = st[mask][picked].erase(it); 
                    else if(it->l > i) ++it;
                    else 
                    {
                        op = it->val;
                        break;
                    }
                }
                for(int n_mask = 0;n_mask < (1LL<<4);n_mask++)
                {
                    if(kt(mask,n_mask) == true)
                    {
                        int n_picked = picked | (n_mask > 0 ? 1 : 0);
                        if(op!=-1e18) dp[i][n_mask][n_picked] = max(dp[i][n_mask][n_picked],op + get_sum(a[i],n_mask));
                    }
                }
            }
        }
        for(int mask = 0;mask<(1LL<<4);mask++)
        {
            if(kt(mask,0) == false) continue;
            for(int picked=0;picked<=1;picked++)
            {
                if(dp[i][mask][picked] == -1e18) continue;
                int left = min(n+1,i+a[i].l);
                int right = min(n+1,i+a[i].r);
                st[mask][picked].in({dp[i][mask][picked],left,right});                
            }

        }
    }
    
    ll ans = -1e18;
    for(int i=1;i<=n;i++)
    {
        if(i+a[i].r > n)
        {
            for(int mask=0;mask<(1LL<<4);mask++) ans=max(ans,dp[i][mask][1]); 
        }
    }
    cout<<ans;
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