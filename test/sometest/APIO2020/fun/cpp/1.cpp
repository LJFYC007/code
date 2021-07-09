#include "fun.h"
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, deg[maxn], Root, dis[maxn];
queue<int> Queue;
vector<int> Edge[maxn], ans, ans1, p[maxn];
bool vis[maxn];

inline void DFS(int u, int fa)
{
    for ( auto v : Edge[u] ) 
    {
        if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; DFS(v, u);
    }
}

inline void Solve(int u)
{
    vis[u] = true; ans.push_back(u);
    dis[u] = 0; DFS(u, -1);
    int nex = -1, Max = 0;
    REP(i, 0, n - 1) if ( !vis[i] && Max < dis[i] ) { nex = i; Max = dis[i]; }
    if ( nex != -1 ) Solve(nex);
}

vector<int> createFunTour(int N, int Q) 
{
    n = N; 
    REP(i, 0, n - 1)
    {
        int l = (1 << i) - 1, r = (1 << i + 1) - 2;
        if ( l > n - 1 ) break ; 
        r = min(r, n - 1)
        REP(j, l, r) p[i].push_back(j);
    }
    int now = n - 1;
    for ( int i = n - 1; i >= 0; -- i ) 
    {
        if ( !p[i].size() ) continue ;
        while ( !p[now].size() ) -- now;
    }
    for ( auto i : ans ) cout << i << " ";
    reverse(ans.begin(), ans.end());
    // REP(i, 0, n - 1) REP(j, 0, n - 1) if ( hoursRequired(i, j) == 1 ) Edge[i].push_back(j);
    // DFS(0, -1); REP(i, 0, n - 1) if ( dis[i] > dis[Root] ) Root = i;
    // mem(vis); Solve(Root);
    return ans;
}
