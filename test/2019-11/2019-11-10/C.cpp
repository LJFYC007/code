/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年11月10日 星期日 21时44分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 510;

int dis[maxn][maxn], f[maxn][maxn], n, m, ans = 10000000000;

signed main()
{
    freopen("circle.in", "r", stdin);
    freopen("circle.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) REP(j, 1, n) f[i][j] = 10000000000;
    REP(i, 1, n) f[i][i] = 0;
    REP(i, 1, m) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); f[u][v] = f[v][u] = min(f[u][v], w); }
    REP(i, 1, n) REP(j, 1, n) dis[i][j] = f[i][j];
    REP(k, 1, n)
    {
        REP(i, 1, k - 1)
            REP(j, i + 1, k - 1)
                ans = min(ans, dis[i][j] + f[i][k] + f[k][j]);
        REP(i, 1, n)
            REP(j, 1, n)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    }
    // REP(i, 1, n) REP(j, 1, n) printf("%lld %lld %lld\n", i, j, f[i][j]);
    printf("%lld\n", ans);
    return 0;
}
