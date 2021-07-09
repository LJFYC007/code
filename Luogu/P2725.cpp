/***************************************************************
	File name: P2725.cpp
	Author: ljfcnyali
	Create time: 2019年05月07日 星期二 14时39分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0x3f, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2000010;

int dp[maxn], n, k, a;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &k, &n);
	mem(dp);
	dp[0] = 0;
	REP(i, 1, n)
	{
		scanf("%d", &a);
		REP(j, a, maxn - 1) 
		{
			if ( dp[j - a] + 1 <= k ) dp[j] = min(dp[j], dp[j - a] + 1);
		}
	}
	REP(i, 1, maxn - 1) if ( dp[i] > k ) { printf("%d\n", i - 1); return 0; }
    return 0;
}
