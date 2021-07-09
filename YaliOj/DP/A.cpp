/***************************************************************
    File name: P1879.cpp
    Author: ljfcnyali
    Create time: 2019年06月16日 星期日 11时18分43秒
***************************************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
#include<stack>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;
const int Mod = 100000000;

int n, m, a[20], Max;
long long ans, dp[20][maxn];
bool f[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n)
        REP(j, 1, m)
        {
            int x; scanf("%d", &x);
            a[i] = (a[i] << 1) + x;
        }
    Max = (1 << m) - 1;
    REP(i, 0, Max) f[i] = ((i & (i << 1)) == 0) && ((i & (i >> 1)) == 0);
    dp[0][0] = 1;
    REP(i, 1, n)
    {
        REP(j, 0, Max)
        {
            if ( f[j] == false ) continue ;
            if ( (j & a[i]) != j ) continue ;
            REP(k, 0, Max)
                if ( (k & j) == 0 ) dp[i][j] = (dp[i][j] + dp[i - 1][k]) % Mod;
        }
    }
    REP(i, 0, Max) ans = (ans + dp[n][i]) % Mod;
    printf("%lld\n", ans);
    return 0;
}
