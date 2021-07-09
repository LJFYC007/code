/***************************************************************
	File name: village.cpp
	Author: ljfcnyali
	Create time: 2020年11月14日 星期六 08时51分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 310;

int n, m, a[maxn][maxn], ans, dt[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool vis[maxn][maxn];

inline void DFS(int x, int y, int x1, int y1, int x2, int y2)
{
    vis[x][y] = true;
    REP(i, 0, 3)
    {
        int u = x + dt[i][0], v = y + dt[i][1];
        if ( u < x1 || u > x2 || v < y1 || v > y2 ) continue ;
        if ( vis[u][v] || a[u][v] != a[x][y] ) continue ;
        DFS(u, v, x1, y1, x2, y2);
    }
}

inline bool Check(int x1, int y1, int x2, int y2)
{
    mem(vis);
    REP(i, x1, x2) 
    {
        if ( a[i][y1] == 0 ) DFS(i, y1, x1, y1, x2, y2); 
        if ( a[i][y2] == 0 ) DFS(i, y2, x1, y1, x2, y2); 
    }
    REP(i, y1, y2)
    {
        if ( a[x1][i] == 0 ) DFS(x1, i, x1, y1, x2, y2); 
        if ( a[x2][i] == 0 ) DFS(x2, i, x1, y1, x2, y2);
    }
    REP(i, x1, x2) REP(j, y1, y2) if ( a[i][j] == 1 ) { DFS(i, j, x1, y1, x2, y2); goto Next2 ; }
    return false;
Next2 : ;
    REP(i, x1, x2) REP(j, y1, y2) if ( !vis[i][j] ) return false;
    return true;
}

int main()
{
    freopen("village.in", "r", stdin);
    freopen("village.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) REP(j, 1, m) scanf("%1d", &a[i][j]);
    REP(i, 1, n) REP(j, 1, m) REP(x, i, n) REP(y, j, m)
        if ( Check(i, j, x, y) ) ++ ans;
    printf("%d\n", ans);
    return 0;
}
