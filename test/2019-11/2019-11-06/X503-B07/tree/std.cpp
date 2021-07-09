/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年11月06日 星期三 14时18分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;

int n, s, l, Begin[maxn], Next[maxn], To[maxn], e;
long double f[maxn][maxn], g[maxn][maxn], ans, p[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    f[u][0] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        g[u][0] = f[u][0]; REP(j, 1, s) g[u][j] = g[u][j - 1] + f[u][j];
        g[v][0] = f[v][0]; REP(j, 1, s) g[v][j] = g[v][j - 1] + f[v][j];
        REP(j, 0, s) p[j] = 0;
        for ( int j = s; j >= 0; -- j ) REP(k, 0, l)
        {
            if ( k > j ) break ;
            p[j] += f[v][j - k] * g[u][min(j, s - j)] / (l + 1);
            if ( j + k <= s ) 
            {
                p[j] += f[u][j] * g[v][min(j - k, s - j - k)] / (l + 1);
                if ( 2 * j <= s ) p[j] -= f[u][j] * f[v][j - k] / (l + 1);
            }
        }
        REP(j, 0, s) f[u][j] = p[j];
    }
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d%d%d", &n, &l, &s);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    DFS(1, 0);
    REP(i, 0, s) ans += f[1][i];
    printf("%.6Lf\n", ans);
    return 0;
}

