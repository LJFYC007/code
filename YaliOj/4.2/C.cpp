/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月29日 星期三 10时36分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 500010;

int dp[maxn], n, m, a[maxn], num[maxn * 10], Max = 1000000, f[maxn], p[maxn][20];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m); REP(i, 1, n) scanf("%d", &a[i]);
	num[a[1] + Max] = 1; dp[1] = 1;
	REP(i, 2, n) 
	{
		if ( num[a[i] + Max] >= dp[i - 1] ) dp[i] = num[a[i] + Max] + 1;
		else dp[i] = dp[i - 1];
		num[a[i] + Max] = i;
	}
	REP(i, 1, n) { f[i] = i - dp[i] + 1; p[i][0] = f[i]; }
	REP(j, 1, 18)
		REP(i, 1, n)
			p[i][j] = max(p[i][j - 1], p[i + (1 << (j - 1))][j - 1]);
//	REP(i, 1, n) printf("%d ", dp[i]); puts("");
//	REP(i, 1, n) printf("%d ", f[i]); puts("");
	REP(i, 1, m)
	{
		int l, r, ans = 0; scanf("%d%d", &l, &r);
		++ l; ++ r;
		int L = l, R = r, k = 0;
		while ( L <= R ) 
		{
			int Mid = (L + R) / 2;
			if ( dp[Mid] < l ) { k = Mid; L = Mid + 1; }
			else R = Mid - 1;
		}
		ans = max(1, k - l + 1);
		L = k + 1; R = r;
//		printf("%d %d\n", L, R);
		for ( int j = 18; j >= 0; -- j )
		{
			if ( L + (1 << j) - 1 > R ) continue ;
//			printf("%d %d %d\n", L, R, p[L][j]);
			ans = max(ans, p[L][j]);	
			L += (1 << j);
		}
		printf("%d\n", ans);
	}
 	return 0;
}
