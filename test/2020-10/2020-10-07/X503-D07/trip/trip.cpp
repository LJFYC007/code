/***************************************************************
	File name: trip.cpp
	Author: ljfcnyali
	Create time: 2020年10月07日 星期三 21时07分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;
const int INF = 0x3f3f3f3f;

int n, m, C, T, p[maxn], c[maxn], a[20][maxn][maxn], w[maxn][maxn], b[maxn];
int f[maxn][maxn * maxn];

inline int Solve(int u, int val)
{
    if ( val < p[u] ) { f[u][val] = 0; return 0; }
    if ( f[u][val] != -1 ) return f[u][val];
    f[u][val] = 0;
    REP(k, 1, n) f[u][val] = max(f[u][val], Solve(k, val - p[u]) + w[u][k]);
    return f[u][val];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("trip.in", "r", stdin);
    freopen("trip.out", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &C, &T);
    REP(i, 1, n) { scanf("%d%d", &p[i], &c[i]); c[i] = min(c[i], C); }
    REP(i, 1, n) REP(j, 1, n) a[0][i][j] = -INF;
    REP(i, 1, n) a[0][i][i] = 0;
    REP(i, 1, m)
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        a[0][u][v] = max(a[0][u][v], w);
    }
    REP(t, 1, 18)
    {
        REP(i, 1, n) REP(j, 1, n) a[t][i][j] = -INF;
        REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) a[t][i][j] = max(a[t][i][j], a[t - 1][i][k] + a[t - 1][k][j]);
    }
    REP(x, 1, n) 
    {
        REP(i, 1, n) w[x][i] = -INF; w[x][x] = 0;
        REP(t, 0, 18) if ( (c[x] >> t) & 1 ) 
        {
            REP(i, 1, n) b[i] = -INF; 
            REP(i, 1, n) REP(j, 1, n) b[j] = max(b[j], w[x][i] + a[t][i][j]);
            REP(i, 1, n) w[x][i] = b[i];
        }
    }
    /*
    REP(i, 1, n) REP(j, 1, n) a[0][i][i] = 0;
    REP(t, 1, 18)
    {
        REP(i, 1, n) REP(j, 1, n) a[t][i][j] = -INF;
        REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) a[t][i][j] = max(a[t][i][j], a[t - 1][i][k] + a[t - 1][k][j]);
    }
    */

    memset(f, -1, sizeof(f));
    REP(i, 1, n) REP(j, 0, n * n) Solve(i, j);

    while ( T -- ) 
    {
        int s, q, d; scanf("%d%d%d", &s, &q, &d);
        int ans = -1, l = 1, r = q;
        while ( l <= r ) 
        {
            int Mid = l + r >> 1;
            if ( f[s][Mid] >= d ) { ans = q - Mid; r = Mid - 1; }
            else l = Mid + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
