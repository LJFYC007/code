/***************************************************************
	File name: P2563.cpp
	Author: ljfcnyali
	Create time: 2019年06月25日 星期二 19时02分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 210;

int prime[maxn], n, cnt, dp[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    REP(i, 2, 200) 
    {
        int x = i;
        for ( int j = 2; j * j <= x; ++ j ) if ( x % j == 0 ) x /= j;
        if ( x == i ) prime[++ cnt] = i;
    }
    while ( ~scanf("%d", &n) )
    {
        mem(dp);
        dp[0] = 1;
        REP(i, 1, cnt)
            REP(j, 1, n)
                if ( j >= prime[i])
                    dp[j] += dp[j - prime[i]];
        printf("%d\n", dp[n]);
    }
    return 0;
}
