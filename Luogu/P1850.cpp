/***************************************************************
	File name: P1850.cpp
	Author: ljfcnyali
	Create time: 2019年07月01日 星期一 15时46分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2010;

int dis[maxn][maxn], n, m, v, e, c[maxn], d[maxn];
double f[maxn], dp[maxn][maxn][2];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &v, &e);
    REP(i, 1, n) scanf("%d", &c[i]);
    REP(i, 1, n) scanf("%d", &d[i]);
    REP(i, 1, n) scanf("%lf", &f[i]);
    memset(dis, 0x3f, sizeof(dis));
    REP(i, 1, v) dis[i][i] = 0;
    REP(i, 1, e) { int u, v, w; scanf("%d%d%d", &u, &v, &w); dis[u][v] = dis[v][u] = min(dis[u][v], w); }
    REP(k, 1, v)
        REP(i, 1, v)
            REP(j, 1, i - 1)
                if ( dis[i][j] > dis[i][k] + dis[k][j] ) 
                dis[i][j] = dis[j][i] = dis[i][k] + dis[k][j];
//    REP(i, 1, n) { REP(j, 1, n) printf("%d ", dis[i][j]); puts(""); }
    REP(i, 1, n) REP(j, 0, m) dp[i][j][0] = dp[i][j][1] = 2147483647;
    dp[1][0][0] = dp[1][1][1] = 0;
    REP(i, 2, n)
        REP(j, 0, m)
        {
            double sum = dp[i - 1][j][0];
            dp[i][j][0] = min(dp[i][j][0], sum + dis[c[i - 1]][c[i]]);
            sum = dp[i - 1][j][1];
            sum += f[i - 1] * dis[d[i - 1]][c[i]];
            sum += (1 - f[i - 1]) * dis[c[i - 1]][c[i]];
            dp[i][j][0] = min(dp[i][j][0], sum);
            if ( j == 0 ) continue ;
            sum = dp[i - 1][j - 1][0];
            sum += f[i] * dis[c[i - 1]][d[i]];
            sum += (1 - f[i]) * dis[c[i - 1]][c[i]];
            dp[i][j][1] = min(dp[i][j][1], sum);
            sum = dp[i - 1][j - 1][1];
            sum += f[i] * f[i - 1] * dis[d[i - 1]][d[i]];
            sum += f[i] * (1 - f[i - 1]) * dis[c[i - 1]][d[i]];
            sum += (1 - f[i]) * f[i - 1] * dis[d[i - 1]][c[i]];
            sum += (1 - f[i]) * (1 - f[i - 1]) * dis[c[i - 1]][c[i]];
            dp[i][j][1] = min(dp[i][j][1], sum);
        }
//    REP(i, 1, n) { REP(j, 0, m) printf("%.2lf ", dp[i][j][1]); puts(""); }
    double ans = 2147483647;
    REP(i, 0, m) ans = min(ans, min(dp[n][i][0], dp[n][i][1]));
    printf("%.2lf\n", ans);
    return 0;
}
