#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "canuc80k5020"
using namespace std;

const int N = 70000;
vector<int> adj[N];
int in_deg[N];
int out_deg[N];
string conv[N];
int n;

int conv_int(char c1, char c2)
{
    return c1 * 256 + c2;
}

void solve()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
        string s;
        cin>>s;
        int u=conv_int(s[0],s[1]);
        int v=conv_int(s[1],s[2]);
        adj[u].pb(v);
        out_deg[u]++;
        in_deg[v]++;
        conv[u] = s.substr(0, 2); 
        conv[v] = s.substr(1, 2);
    }

    int st = -1;
    int c1=0;
    int c2=0;
    for(int i=0;i<N;i++)
    {
        if(out_deg[i]-in_deg[i]==1)
        {
            st = i;
            c1++;
        }
        else if(in_deg[i]-out_deg[i]==1)
        {
            c2++;
        }
        else if(in_deg[i]!=out_deg[i])
        {
            cout<<"NO\n";
            return ;
        }
    }

    if (c1>1||c2>1)
    {
        cout<<"NO\n";
        return ;
    }

    if(st==-1)
    {
        for(int i=0;i<N;i++)
        {
            if (out_deg[i]>0)
            {
                st = i;
                break;
            }
        }
    }
    
    if(st==-1)
    {
        cout<<"NO\n";
        return ;
    }

    vector<int> path;
    vector<int> v;
    v.pb(st);
    while(!v.empty())
    {
        int u=v.back();
        if(adj[u].empty())
        {
            path.pb(u);
            v.pop_back();
        }
        else
        {
            int z=adj[u].back();
            adj[u].pop_back();
            v.pb(z);
        }
    }

    if((int)path.size()!=n+1)
    {
        cout<<"NO\n";
        return ;
    }

    cout<<"YES\n";
    reverse(path.begin(), path.end());
    cout<<conv[path[0]];
    for(int i=1;i<=n;i++) cout<<conv[path[i]][1];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    if(fopen(task".INP","r"))
    {
        freopen(task".INP","r",stdin);
        freopen(task".OUT","w",stdout);
    }
    int t=1;
    while(t--) solve();
}