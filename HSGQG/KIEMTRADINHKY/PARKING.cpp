#include<bits/stdc++.h>
#define ll long long
#define task "PARKING"
#define fi first
#define se second
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;

struct Car
{
    int A, B;
};

Car xe[MAXN];
int deps[MAXN];
int B_par[2 * MAXN];
int A_par[MAXN];
int R_par[MAXN];
int N;

bool cmpA(const Car &a, const Car &b)
{
    return a.A < b.A;
}

bool cmpB(int i, int j)
{
    return xe[i].B < xe[j].B;
}

int find_B(int i)
{
    return B_par[i] < 0 ? i : B_par[i] = find_B(B_par[i]);
}

void union_B(int u, int v)
{
    u = find_B(u);
    v = find_B(v);
    if(u != v)
    {
        if(B_par[u] > B_par[v]) swap(u, v);
        B_par[u] += B_par[v];
        B_par[v] = u;
    }
}

void add_conflict(int u, int v)
{
    union_B(u, v + N);
    union_B(u + N, v);
}

void add_same(int u, int v)
{
    union_B(u, v);
    union_B(u + N, v + N);
}

int find_A(int i)
{
    return A_par[i] == i ? i : A_par[i] = find_A(A_par[i]);
}

int find_R(int i)
{
    return R_par[i] == i ? i : R_par[i] = find_R(R_par[i]);
}

void solve()
{
    cin>>N;
    for(int i=1;i<=N;i++) cin>>xe[i].A>>xe[i].B;
    
    sort(xe+1,xe+N+1,cmpA);
    
    for(int i=1;i<=N;i++) deps[i] = i;
    sort(deps+1,deps+N+1,cmpB);
    
    for(int i=1;i<=2*N;i++) B_par[i] = -1;
    for(int i=1;i<=N+1;i++)
    {
        A_par[i] = i;
        R_par[i] = i;
    }
    
    for(int i=1;i<=N;i++)
    {
        int c_idx = deps[i];
        int curr = find_A(c_idx + 1);
        while(curr <= N && xe[curr].A < xe[c_idx].B)
        {
            curr = find_R(curr);
            add_conflict(c_idx, curr);
            int next_v = find_A(curr + 1);
            if(next_v <= N && xe[next_v].A < xe[c_idx].B)
            {
                add_same(curr, next_v);
                R_par[curr] = find_R(next_v);
                curr = next_v;
            }
            else
            {
                break;
            }
        }
        A_par[c_idx] = c_idx + 1;
    }
    
    for(int i=1;i<=N;i++)
    {
        if(find_B(i) == find_B(i + N))
        {
            cout << 0 << "\n";
            return;
        }
    }
    
    int comps = 0;
    for(int i=1;i<=2*N;i++)
    {
        if(B_par[i] < 0) comps++;
    }
    comps/=2;
    ll ans = 1;
    for(int i=0;i<comps;i++)
    {
        ans = (ans * 2) % MOD;
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