/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年06月26日 星期三 09时36分09秒
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

const int maxn = 2010;
const int INF = 1 << 29;

int n, dp[maxn][maxn], f[maxn][maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%d", &n) )
    {
        if ( n == 0 ) return 0;
        REP(i, 0, n) REP(j, 0, n) scanf("%d", &f[i][j]);
        REP(k, 0, n) REP(i, 0, n) REP(j, 0, n) f[i][j] = min(f[i][j], f[i][k] + f[k][j]);       
        int num = 1 << n;
        mem(dp);
        REP(i, 1, num - 1)
        {
            REP(j, 1, n)
            {
                if ( ((i >> (n - j)) & 1) == 0 ) continue ;
                int x = i & ~(1 << (n - j));
                if ( i == (1 << (n - j)) ) { dp[i][j] = f[0][j]; continue ; }
                dp[i][j] = INF;
                REP(k, 1, n) 
                {
                    if ( k == j || ((i >> (n - k)) & 1) == 0 ) continue ;
                    dp[i][j] = min(dp[i][j], dp[x][k] + f[k][j]);
                }
            }
        }
//        REP(i, 0, n) { REP(j, 0, n) printf("%d ", f[i][j]); puts(""); }
//        REP(i, 1, num - 1) printf("%d %d\n", i, dp[i]);
        int ans = INF;
        REP(i, 1, n) ans = min(ans, dp[num - 1][i] + f[i][0]);
        printf("%d\n", ans);
//        printf("%d\n", dp[num - 1]);
    }
    return 0;
}
