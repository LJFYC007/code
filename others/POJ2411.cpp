/***************************************************************
	File name: POJ2411.cpp
	Author: ljfcnyali
	Create time: 2019年06月27日 星期四 08时23分03秒
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
typedef long long LL;

const int maxn = 1 << 12;

LL dp[15][maxn], n, m;

inline bool pd(LL x)
{
    REP(j, 0, m - 1)
        if ( (x >> j) & 1 )
        {
            if ( j == m - 1 ) return false; 
            if ( (x >> (j + 1)) & 1 ) ++ j;
            else return false; 
        }
    return true;
}

inline bool check(LL nxt, LL pre)
{
    REP(j, 0, m - 1)
    {
        if ( (nxt >> j) & 1 )
        {
            if ( (pre >> j) & 1 ) 
            {
                if ( !((pre >> (j + 1)) & 1) || !((nxt >> (j + 1)) & 1) || j == m - 1 ) return false;
                ++ j;
            }
        }
        else if ( !((pre >> j) & 1) ) return false;
    }
    return true;
}
       
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%lld%lld", &n, &m) && n + m )
    {
        if ( (n & 1) && (m & 1) ) { printf("0\n"); continue ; }
        mem(dp);
        if ( n < m ) swap(n, m);
        LL num = 1 << m;
        REP(i, 0, num - 1) if ( pd(i) ) dp[1][i] = 1;
        REP(i, 2, n)
            REP(j, 0, num - 1)
            {
                if ( !dp[i - 1][j] ) continue ;
                REP(k, 0, num - 1)
                    if ( check(k, j) )
                        dp[i][k] += dp[i - 1][j];
            }
        printf("%lld\n", dp[n][num - 1]);
    }
    return 0;
}
