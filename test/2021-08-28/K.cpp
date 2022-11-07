/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 210;
const int INF = 0x3f3f3f3f;

int T, f[maxn][maxn], c[maxn][maxn], dp[maxn][maxn], n, m, k;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d%d%d", &n, &m, &k); 
		REP(i, 0, 200) REP(j, 0, 200) dp[i][j] = -INF;
		dp[0][k] = 0;
		REP(i, 1, n) REP(j, 1, m) 
		{
			scanf("%d", &f[i][j]);
			getchar(); c[i][j] = getchar() == 'Y' ? 1 : 0;
		}

		REP(i, 1, m) REP(j, 0, 200)
		{
			int sum = 0, num = j;
			REP(o, 0, n)
			{
				if ( o >= 1 )
				{
					sum += f[n - o + 1][i];
					-- num;
					if ( num < 0 ) break ; 
					num += c[n - o + 1][i];
				}
				dp[i][num] = max(dp[i][num], dp[i - 1][j] + sum);
			}
		}

		int ans = 0; REP(i, 0, 200) ans = max(ans, dp[m][i]);
		printf("%d\n", ans);
	}

    return 0;
}
