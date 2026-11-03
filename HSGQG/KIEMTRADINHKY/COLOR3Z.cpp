#include <bits/stdc++.h>
#include "color3lib.h"
#define ll long long
#define fi first
#define se second
using namespace std;

namespace personA
{
    string Alice(int n, int m, const vector<pair<int, int>>& edges, const vector<int>& colors)
    {
        string s(n, '0');
        for (int i = 0; i < n; i++)
        {
            if(colors[i] == 3)
            {
                s[i] = '1'; 
            }
        }
        return s;
    }
}

namespace personB
{
    void Bob(int n, int m, const vector<pair<int, int>>& edges, const string& bits)
    {
        vector<vector<int>> adj(n + 1);
        for (pair<int,int> edge : edges)
        {
            int u = edge.fi;
            int v = edge.se;
            if (bits[u - 1] == '0' && bits[v - 1] == '0')
            {
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }

        vector<int> color(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            if(bits[i-1]=='1')
            {
                color[i] = 3;
            }else if(color[i]==0)
            {
                queue<int> q;
                q.push(i);
                color[i] = 1;
                
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    for (int v : adj[u]) {
                        if (color[v] == 0) {
                            color[v] = 3 - color[u]; 
                            q.push(v);
                        }
                    }
                }
            }
        }
        for (int u = 1; u <= n; u++) {
            paint(u, color[u]);
        }
    }
}