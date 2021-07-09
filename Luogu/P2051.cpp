/***************************************************************
	File name: P2051.cpp
	Author: ljfcnyali
	Create time: 2019年07月02日 星期二 08时26分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 110;
const int Mod = 9999973;

long long dp[maxn][maxn][maxn], n, m;

inline int C(int n)
{
    return (n * (n - 1) / 2) % Mod;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    dp[0][0][0] = 1;
    REP(i, 1, n)
        REP(j, 0, m)
            REP(k, 0, m - j)
            {
                dp[i][j][k] = dp[i - 1][j][k];
                if ( k >= 1 ) dp[i][j][k] += dp[i - 1][j + 1][k - 1] * (j + 1);
                if ( j >= 1 ) dp[i][j][k] += dp[i - 1][j - 1][k] * (m - j - k + 1);
                if ( k >= 1 ) dp[i][j][k] += dp[i - 1][j][k - 1] * j * (m - j - k + 1);
                if ( j >= 2 ) dp[i][j][k] += dp[i - 1][j - 2][k] * C(m - k - j + 2);
                if ( k >= 2 ) dp[i][j][k] += dp[i - 1][j + 2][k - 2] * C(j + 2);
                dp[i][j][k] %= Mod;
            }
    int ans = 0;
    REP(i, 0, m) REP(j, 0, m) ans = (ans + dp[n][i][j]) % Mod;
    printf("%d\n", ans % Mod);
    return 0;
}
