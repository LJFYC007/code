/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月25日 星期六 09时09分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 210;

int dp[maxn][maxn], a[maxn], n, ans, tail[maxn], fail[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) { scanf("%d", &a[i]); a[n + i] = a[i]; }
	REP(i, 1, n) tail[i] = tail[i + n] = a[i], fail[i] = fail[n + i] = a[i + 1]; 
	fail[n] = fail[2 * n] = a[1];
	REP(l, 1, n - 1)
	{
		REP(i, 1, 2 * n - l)
		{
			int j = i + l;
			REP(k, i, j - 1)
			{
				dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j] + tail[i] * fail[k] * fail[j]);
			}
		}
	}
	REP(i, 1, n) ans = max(ans, dp[i][i + n - 1]);
	printf("%d\n", ans);
    return 0;
}
