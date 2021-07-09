/***************************************************************
	File name: query.cpp
	Author: ljfcnyali-akioi
	Create time: 2020年11月28日 星期六 09时13分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], anc[maxn][20];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u; DFS(v, u);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int i = 18; i >= 0; -- i ) if ( dis[anc[x][i]] >= dis[y] ) x = anc[x][i];
    if ( x == y ) return x;
    for ( int i = 18; i >= 0; -- i ) if ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; }
    return anc[x][0];
}

int main()
{
    freopen("query.in", "r", stdin);
    freopen("query1.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS(1, 0); REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, m)
    {
        int u, v; scanf("%d%d", &u, &v);
        int t = LCA(u, v), ans = (dis[u] - dis[t]) == t, x = 0, len = dis[u] + dis[v] - 2 * dis[t];
        while ( u != t ) 
        {
            ans += (x == u);
            ++ x; u = anc[u][0];
        }
        x = len;
        while ( v != t ) 
        {
            ans += (x == v);
            -- x; v = anc[v][0];
        }
        printf("%d\n", ans);
    }
    return 0;
}
