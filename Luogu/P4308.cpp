/***************************************************************
	File name: P4308.cpp
	Author: ljfcnyali
	Create time: 2019年08月20日 星期二 08时59分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 110;
const double eps = 1e-10;

double f[maxn][maxn], dp[maxn][maxn], p, w[maxn], ans;
int n, m, s;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m); 
    REP(i, 1, n) scanf("%lf", &w[i]);
    REP(i, 1, n) REP(j, 1, n) if ( i != j ) f[i][j] = -1e100;
    scanf("%d%lf", &s, &p);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); f[u][v] = w[v] * p; }
    while ( p > eps ) 
    {
        REP(i, 1, n) REP(j, 1, n) dp[i][j] = -1e100;
        REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) dp[i][j] = max(dp[i][j], f[i][k] + p * f[k][j]);
        memcpy(f, dp, sizeof(dp));
        p *= p;
    }
    REP(i, 1, n) ans = max(ans, f[s][i]); printf("%.1lf\n", ans + w[s]);
    return 0;
}
