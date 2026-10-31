#include<bits/stdc++.h>
#define ll long long
#define task "PHOTO"
#define pb push_back
using namespace std;

const int N = 20005;
int n;
int a[5][N];
int pos[5][N];
vector<int> v;

bool kt(int u, int v)
{
    int cnt=0;
    for(int i=0;i<5;i++) if(pos[i][u]<pos[i][v]) cnt++;
    return cnt>=3;
}

void solve()
{
    cin >> n;
    for(int i=0;i<5;i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cin >> a[i][j];
            if(i==0) v.pb(a[i][j]);
        }
    }
    sort(v.begin(),v.end());
    for(int i=0;i<5;i++)
    {
        for(int j=1;j<=n;j++)
        {
            int id=lower_bound(v.begin(), v.end(), a[i][j]) - v.begin();
            pos[i][id]=j;
        }
    }
    vector<int> res(n);
    for(int i=0;i<n;i++) res[i] = i;

    sort(res.begin(),res.end(),kt);

    for(int i=0;i<n;i++)
    {
        cout << v[res[i]] << " ";
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
    solve();
}