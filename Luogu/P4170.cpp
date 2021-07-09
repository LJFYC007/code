/***************************************************************
	File name: P4170.cpp
	Author: ljfcnyali
	Create time: 2019年06月18日 星期二 15时48分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 110;

long long dp[maxn][maxn], n;
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s); n = str(s);
    memset(dp, 0x3f, sizeof(dp));
    REP(i, 0, n) dp[i][i] = 1;
    REP(len, 2, n)
        REP(i, 0, n - 1)
        {
            int j = i + len - 1;
            if ( j >= n ) break ;
            if ( s[i] == s[j] ) dp[i][j] = min(dp[i][j], min(dp[i + 1][j], dp[i][j - 1]));
            else REP(k, i, j - 1) dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
        }
    printf("%lld\n", dp[0][n - 1]);
    return 0;
}
