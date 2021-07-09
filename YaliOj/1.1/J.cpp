/***************************************************************
	File name: J.cpp
	Author: ljfcnyali
	Create time: 2019年05月07日 星期二 13时07分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 3010;

int dp[maxn][maxn], n, h, a[maxn], b[maxn], t[maxn], ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &h); h *= 12;
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, n) scanf("%d", &b[i]);
	REP(i, 2, n) { scanf("%d", &t[i]); t[i] += t[i - 1]; }
	REP(i, 1, n)
	{
		REP(j, 1, h - t[i])
		{
			dp[i][j] = dp[i][j - 1];
			REP(k, 0, j)
			{
				int sum = 0;
				if ( a[i] < b[i] * (k - 1) ) break ;
				REP(o, 0, k - 1) sum += a[i] - b[i] * (o);
				dp[i][j] = max(dp[i][j], dp[i - 1][j -  k] + sum);
			}
			ans = max(ans, dp[i][j]);
		}
	}
	printf("%d\n", ans);	
    return 0;
}
