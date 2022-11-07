/***************************************************************
	File name: G.cpp
	Author: ljfcnyali
	Create time: 2020年10月13日 星期二 14时16分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;

int n, m, Begin[maxn], Next[maxn], To[maxn], e = 1, W[maxn], c[maxn];
int id[20][20], k, s, t, dis[maxn], Edge[20][20];

inline void add(int u, int v, int w) 
{ 
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
    swap(u, v); w = 0;
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
}

inline bool BFS()
{
    queue<int> Q; Q.push(s); REP(i, 1, k) dis[i] = INF; dis[s] = 0;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( !W[i] || dis[v] != INF ) continue ;
            dis[v] = dis[u] + 1; Q.push(v);
        }
    }
    return dis[t] != INF;
}

inline int DFS(int u, int flow)
{
    if ( u == t || !flow ) return flow;
    int f = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( dis[v] != dis[u] + 1 || !W[i] ) continue ;
        int x = DFS(v, min(flow, W[i]));
        if ( x ) 
        {
            W[i] -= x; W[i ^ 1] += x;
            flow -= x; f += x;
        }
    }
    if ( !f ) dis[u] = INF; return f;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) REP(j, 0, n) id[i][j] = ++ k; s = ++ k; t = ++ k;
    REP(i, 1, n) { add(s, id[i][0], INF); add(id[i][n], t, INF); }
    REP(i, 1, m)
    {
        int u, v, w; scanf("%lld%lld%lld", &u, &v, &w);
        c[u] += w; c[v] -= w; 
        REP(j, 0, n - 1) add(id[v][j], id[u][j + 1], INF);
    }
    REP(i, 1, n) if ( c[i] > 0 ) 
        REP(j, 0, n - 1) { Edge[i][j] = e + 1; add(id[i][j], id[i][j + 1], j * c[i]); }
    else 
        REP(j, 0, n - 1) { Edge[i][j] = e + 1; add(id[i][j], id[i][j + 1], (j - n) * c[i]); }
    while ( BFS() ) while ( DFS(s, INF) ) ;
    REP(i, 1, n) 
        REP(j, 0, n - 1) 
            if ( dis[id[i][j]] && dis[id[i][j + 1]] == INF ) { printf("%lld ", j); break ; }
    puts("");
    return 0;
}
