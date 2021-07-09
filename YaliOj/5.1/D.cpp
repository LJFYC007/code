/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年06月07日 星期五 08时17分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 210;
const int INF = 0x3f3f3f3f;

int dp[maxn][maxn], n;
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s); n = str(s);
    REP(i, 1, n) dp[i][i] = 1;
    REP(len, 2, n)
    {
        REP(i, 1, n - len + 1)
        {
            int j = i + len - 1;
            dp[i][j] = INF;
            if ( (s[i - 1] == '[' && s[j - 1] == ']') || (s[i - 1] == '(' && s[j - 1] == ')') )
                dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
            REP(k, i, j) dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
        }
    }
//    REP(i, 1, n) REP(j, 1, n) printf("%d %d %d\n", i, j, dp[i][j]);
    printf("%d\n", dp[1][n]);
    return 0;
}
