#include <iostream>
#include <iomanip>

#include <vector>
#include <array>
#include <deque>
#include <list>
#include <stack>
#include <queue>

#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include <algorithm>
#include <numeric>
#include <functional>

#include <string>
#include <cstring>

#include <utility>
#include <tuple>

#include <cmath>
#include <limits>

#include <cstdio>
#include <cstdlib>

#include <fstream>
#include <sstream>

using namespace std;

#define ll long long
#define dbl double long
#define pb push_back
#define in insert
#define fi first
#define task "TRAVEL"
#define se second
const ll MOD = 1e9+7;


const int N = 1e6+20;

bool snt[N];

void sang()
{
    for(int i=0;i<N;i++) snt[i]=1;
    snt[0]=snt[1]=1;
    for(int i=2;i*i<N;i++)
    {
        if(snt[i])
        {
            for(int j=i*i;j<N;j+=i) snt[j]=i;
        }   
    }
}

void solve()
{
    int n; cin >> n;
    ll a[n+5];
    for(int i=1;i<=n;i++) cout<<snt[i]<<' ';
}

signed main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    if(fopen(task".INP", "r")){
        freopen(task".INP", "r", stdin);
        freopen(task".OUT", "w", stdout);
    }
    
    int t=1;
    sang();
    while(t--) solve();
}
