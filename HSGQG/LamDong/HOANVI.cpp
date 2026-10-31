#include<bits/stdc++.h>
#define ll long long
#define task "HOANVI"
#define pb push_back
using namespace std;

const ll MOD = 1e9+7;
const int N = 300005;

ll fact[N];
int B[N];

struct FEN
{
    int n;
    vector<ll> tree;
    FEN(int n) : n(n) { tree.assign(n+1,0); }
    void add(int i, ll delta)
    {
        for (; i <= n; i += i & -i)
        {
            tree[i]=(tree[i]+delta)%MOD;
        }
    }
    ll query(int i)
    {
        ll sum = 0;
        for (; i > 0; i -= i & -i)
        {
            sum=(sum+tree[i])%MOD;
        }
        return sum;
    }
};

struct query
{
    int id;
    int sign;
    int val;
    ll factor;
    int type;
};

ll ans[N];
vector<query> v[N];

void solve()
{
    fact[0]=1;
    for(int i=1;i<N;i++) fact[i] = (fact[i-1]*i)%MOD;

    int k,n; cin>>k>>n;
    
    for(int i = 1; i <= k; i++) cin >> B[i];
    
    FEN FEN_base(k);
    ll br = 1;
    for(int i=k;i>=1;i--)
    {
        ll c_i = FEN_base.query(B[i]-1);
        br= (br+ c_i * fact[k - i]) % MOD;
        FEN_base.add(B[i], 1);
    }
    
    for (int i = 1; i <= n; i++)
    {
        int a, b;
        cin >> a >> b;
        
        ll term1 = ((B[b]>B[a])-(B[a]>B[b])) * fact[k-a]%MOD;
        ans[i] = term1;
        
        ll f_a = fact[k - a];
        ll f_diff = (fact[k - a] - fact[k - b] + MOD) % MOD;
        
        v[a].pb({i, -1, B[b], f_a, 1});
        v[a].pb({i, 1, B[a], f_a, 1});
        v[b - 1].pb({i, 1, B[b], f_a, 1});
        v[b - 1].pb({i, -1, B[a], f_a, 1});
        
        v[a].pb({i, -1, B[a], 1, 2});
        v[a].pb({i, 1, B[b], 1, 2});
        v[b - 1].pb({i, 1, B[a], 1, 2});
        v[b - 1].pb({i, -1, B[b], 1, 2});

        v[b].pb({i, -1, B[b], f_diff, 1});
        v[b].pb({i, 1, B[a], f_diff, 1});
        v[k].pb({i, 1, B[b], f_diff, 1});
        v[k].pb({i, -1, B[a], f_diff, 1});
    }
    
    FEN FEN_count(k);
    FEN FEN_weight(k);
    
    for (int i = 1; i <= k; i++)
    {
        FEN_count.add(B[i], 1);
        FEN_weight.add(B[i], fact[k - i]);
        
        for (query ev : v[i])
        {
            ll val = 0;
            if (ev.type == 1)
            {
                val = FEN_count.query(ev.val - 1);
            }
            else
            {
                val = (FEN_weight.query(k)-FEN_weight.query(ev.val)+MOD)%MOD;
            }
            ll term=(val*ev.factor)%MOD;
            if (ev.sign==1) ans[ev.id]=(ans[ev.id]+term)%MOD;
            else ans[ev.id]=(ans[ev.id]-term+MOD)%MOD;
        }
    }
    
    for (int i=1;i<=n;i++)
    {
        ll f=(br + ans[i])%MOD;
        if (f<0) f+=MOD;
        cout<<f<<'\n';
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