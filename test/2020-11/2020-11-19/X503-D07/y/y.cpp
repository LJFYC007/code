/***************************************************************
	File name: y.cpp
	Author: ljfcnyali
	Create time: 2020年11月19日 星期四 11时01分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, d, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], ans;
bool f[11][91][1 << 10], g[11][91][1 << 10], a[91][91][2];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

signed main()
{
    freopen("y.in", "r", stdin);
    freopen("y.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &d);
    REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); a[u][v][w] = a[v][u][w] = true; }
    REP(i, 1, n) REP(j, 1, n) REP(k, 0, 1) if ( a[i][j][k] ) add(i, j, k);
    int x1 = d / 2, x2 = d - x1;

    f[0][1][0] = true; REP(i, 1, n) g[0][i][0] = true;
    REP(len, 0, 9) REP(j, 1, n) REP(k, 0, (1 << len) - 1)
    {
        if ( !f[len][j][k] ) continue ; 
        for ( int o = Begin[j]; o; o = Next[o] ) 
            f[len + 1][To[o]][k * 2 + W[o]] = true;
    }
    REP(len, 0, 9) REP(j, 1, n) REP(k, 0, (1 << len) - 1)
    {
        if ( !g[len][j][k] ) continue ; 
        for ( int o = Begin[j]; o; o = Next[o] ) 
            g[len + 1][To[o]][k * 2 + W[o]] = true;
    }

    REP(j, 0, (1 << x1) - 1) REP(k, 0, (1 << x2) - 1)
    {
        REP(i, 1, n) if ( f[x1][i][j] && g[x2][i][k] ) { ++ ans; goto Next ; }
Next : ;
    }
    printf("%d\n", ans);
    return 0;
}
