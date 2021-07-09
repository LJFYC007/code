/***************************************************************
	File name: P2657.cpp
	Author: ljfcnyali
	Create time: 2019年06月22日 星期六 14时57分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 110;

int dp[maxn][maxn], n, m, len, a[maxn];

inline int Solve(int x)
{
    len = 0;
    while ( x ) { a[++ len] = x % 10; x /= 10; }
    int ans = 0;
    REP(i, 1, len - 1) REP(j, 1, 9) ans += dp[i][j];
    REP(i, 1, a[len] - 1) ans += dp[len][i]; 
    for ( int i = len - 1; i >= 1; -- i ) 
    {
        REP(j, 0, a[i] - 1)
            if ( abs(a[i + 1] - j) >= 2 ) 
                ans += dp[i][j];
        if ( abs(a[i + 1] - a[i]) < 2 ) break ;
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    REP(i, 0, 9) dp[1][i] = 1;
    REP(i, 2, 10) REP(j, 0, 9) REP(k, 0, 9) if ( abs(j - k) >= 2 ) dp[i][j] += dp[i - 1][k];
    scanf("%d%d", &n, &m);
    printf("%d\n", Solve(m + 1) - Solve(n));
    return 0;
}
