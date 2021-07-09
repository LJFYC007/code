/***************************************************************
	File name: CF1404E.cpp
	Author: ljfcnyali
	Create time: 2020年10月12日 星期一 16时04分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 1e18;

int n, m, s, t, Begin[maxn], Next[maxn], To[maxn], e = 1, W[maxn];
int dis[maxn], a[210][210], id1[210][210], id2[210][210], ans;
char S[210];

inline void add(int u, int v, int w) 
{
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; 
    swap(u, v); w = 0;
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; 
}

inline bool BFS()
{
    queue<int> Q; Q.push(s); 
    REP(i, 1, t) dis[i] = INF; dis[s] = 0;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] )
        {
            int v = To[i]; if ( !W[i] ) continue ;
            if ( dis[v] == INF ) { dis[v] = dis[u] + 1; Q.push(v); }
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
    REP(i, 1, n) { scanf("%s", S + 1); REP(j, 1, m) { a[i][j] = (S[j] == '#'); ans += a[i][j]; } }
    int tot = 0; 
    REP(i, 1, n) REP(j, 1, m - 1)
    {
        if ( !a[i][j] || !a[i][j + 1] ) continue ;
        id1[i][j] = ++ tot;
    }
    REP(i, 1, n - 1) REP(j, 1, m)
    {
        if ( !a[i][j] || !a[i + 1][j] ) continue ;
        id2[i][j] = ++ tot;
    }
    s = ++ tot; t = ++ tot;

    REP(i, 1, n) REP(j, 1, m - 1)
    {
        if ( !id1[i][j] ) continue ;
        add(s, id1[i][j], 1);
        if ( id2[i][j] ) add(id1[i][j], id2[i][j], 1);
        if ( id2[i][j + 1] ) add(id1[i][j], id2[i][j + 1], 1);
        if ( id2[i - 1][j] ) add(id1[i][j], id2[i - 1][j], 1);
        if ( id2[i - 1][j + 1] ) add(id1[i][j], id2[i - 1][j + 1], 1);
    }
    REP(i, 1, n - 1) REP(j, 1, m)
        if ( id2[i][j] ) add(id2[i][j], t, 1);

    int flow = 0; while ( BFS() ) while ( int x = DFS(s, INF) ) flow += x;
    printf("%lld\n", ans - (tot - 2 - flow));
    return 0;
}
