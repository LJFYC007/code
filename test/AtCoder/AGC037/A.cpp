/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年08月17日 星期六 19时45分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

/* dp[i][2] */

const int maxn = 200010;

int n, dp[maxn][3];
char s[maxn];

int main()
{
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n)
    {
        if ( s[i] != s[i - 1] ) dp[i][1] = max(dp[i][1], dp[i - 1][1] + 1);
        if ( i > 1 ) dp[i][1] = max(dp[i][1], dp[i - 1][2] + 1);
        if ( i > 1 ) dp[i][2] = max(dp[i][2], dp[i - 2][1] + 1);
        if ( i > 2 && s[i] != s[i - 2] && s[i - 1] != s[i - 3] ) dp[i][2] = max(dp[i][2], dp[i - 2][2] + 1);
    }
    printf("%d\n", max(dp[n][1], dp[n][2]));
    return 0;
}
