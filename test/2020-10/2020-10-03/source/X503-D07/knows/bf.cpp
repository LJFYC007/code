/***************************************************************
	File name: know.cpp
	Author: ljfcnyali
	Create time: 2020年10月03日 星期六 09时14分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 310;
const int INF = 2e9 + 10;

int n, p[maxn], q[maxn], c[maxn], f[maxn][maxn][maxn];

int main()
{
    freopen("knows.in", "r", stdin);
    freopen("knows1.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d", &p[i]); q[p[i]] = i; }
    REP(i, 1, n) scanf("%d", &c[i]);
    REP(i, 0, n) REP(j, 0, n) REP(k, 0, n) f[i][j][k] = INF; f[0][0][0] = 0;
    REP(i, 1, n) REP(j, 0, n) REP(k, 0, n)
    {
        if ( q[i] < k ) { f[i][j][k] = min(f[i][j][k], f[i - 1][j][k]); continue ; }
        if ( q[i] > k ) f[i][j ? min(j, q[i]) : q[i]][k] = min(f[i][j ? min(j, q[i]) : q[i]][k], f[i - 1][j][k]);
        if ( q[i] < j ) f[i][0][max(q[i], k)] = min(f[i][0][max(q[i], k)], f[i - 1][j][k] + c[q[i]]);
        f[i][j][max(q[i], k)] = min(f[i][j][max(q[i], k)], f[i - 1][j][k] + c[q[i]]);
    }
    int ans = INF;
    // REP(i, 1, n) printf("%d ", f[n][0][i]); puts("");
    REP(i, 0, n) ans = min(ans, f[n][0][i]);
    printf("%d\n", ans);
    return 0;
}
