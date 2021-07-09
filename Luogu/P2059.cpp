/***************************************************************
	File name: P2059.cpp
	Author: ljfcnyali
	Create time: 2019年06月12日 星期三 14时48分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 110;

int a[maxn], n, m;
double dp[maxn][maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) scanf("%d", &a[i]);
    dp[1][1] = 1.0;
    REP(i, 2, n)
        REP(j, 1, i)
            REP(k, 1, m)
            {
                int c = (a[k] % i != 0) ? (a[k] % i) : i;
                if ( c > j ) dp[i][j] += dp[i - 1][i - c + j] * 1.0 / m;
                else dp[i][j] += dp[i - 1][j - c] * 1.0 / m;
            }
    REP(i, 1, n) printf("%.2lf%% ", dp[n][i] * 100.0);
    return 0;
}
