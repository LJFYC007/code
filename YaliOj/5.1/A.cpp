/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月24日 星期五 11时19分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 410;

int dp1[maxn][maxn], sum[maxn], n, a[maxn], dp2[maxn][maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); 
	REP(i, 1, n) { scanf("%d", &a[i]); a[i + n] = a[i]; }
	REP(i, 1, n * 2) sum[i] = sum[i - 1] + a[i];
	int ans2 = 0x3f3f3f3f, ans1 = 0;
	memset ( dp2, 0x3f, sizeof(dp1) ); mem(dp1);
	REP(i, 1, 2 * n) dp1[i][i] = dp2[i][i] = 0;
	REP(l, 2, n)
	{
		REP(i, 1, 2 * n - l + 1)
		{
			int j = i + l - 1;
			REP(k, i, j - 1)
			{
				dp1[i][j] = max(dp1[i][j], dp1[i][k] + dp1[k + 1][j] + sum[j] - sum[i - 1]);
				dp2[i][j] = min(dp2[i][j], dp2[i][k] + dp2[k + 1][j] + sum[j] - sum[i - 1]);
			}
		}
	}
	REP(i, 1, n)
	{
		ans1 = max(ans1, dp1[i][i + n - 1]);
		ans2 = min(ans2, dp2[i][i + n - 1]);
	}
	printf("%d\n%d\n", ans2, ans1);
    return 0;
}
