/***************************************************************
	File name: trip.cpp
	Author: ljfcnyali
	Create time: 2019年08月02日 星期五 10时01分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 2020;
const int Mod = 1e9 + 7;

LL dp[maxn][maxn], n, s, t, a[maxn], num;
char S[maxn];

int main()
{
    freopen("trip.in", "r", stdin);
    freopen("trip.out", "w", stdout);
    scanf("%s", S); n = str(S);
    REP(i, 1, n) if ( S[i - 1] == 'R' ) a[i] = 1; else if ( S[i - 1] == 'L' ) a[i] = 2;
    scanf("%lld%lld", &s, &t);
    bool flag1 = false, flag2 = false;
    dp[0][0] = 1;
    REP(i, 1, n)
    {
        REP(j, 1, i)
        {
            if ( i == s ) 
            {
                if ( a[i] != 2 ) dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % Mod;
                if ( a[i] != 1 ) dp[i][j] = (dp[i][j] + dp[i - 1][j]) % Mod;
                flag1 = true;
            }
            else if ( i == t ) 
            {
                dp[i][j] = (dp[i][j] + dp[i - 1][j] + dp[i - 1][j - 1]) % Mod;
                flag2 = true;
            }
            else 
            {
                if ( a[i] != 2 ) dp[i][j] = (dp[i][j] + (j - flag1 - flag2) * dp[i - 1][j - 1] + (j - flag2) * dp[i - 1][j]) % Mod;
                if ( a[i] != 1 ) dp[i][j] = (dp[i][j] + j * dp[i - 1][j + 1] + (j - flag1) * dp[i - 1][j]) % Mod;
            }
        }
    }
    // REP(i, 1, n) REP(j, 1, n) cerr << dp[i][j] << endl;
    printf("%lld\n", dp[n][1]);
    return 0;
}
