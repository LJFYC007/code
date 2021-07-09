#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

typedef long long LL;
const int maxn = 2010, mod = 1e9 + 7;
char str[maxn];
int dp[maxn][maxn];

int main()
{
	freopen("trip.in", "r", stdin);
	freopen("trip.out", "w", stdout);

	scanf("%s", str + 1);
	int n = strlen(str + 1); int s, e;
	scanf("%d%d", &s, &e);

	dp[0][0] = 1;
	for(int i = 1, S = 0, E = 0; i <= n; ++i)
		for(int j = 1; j <= i; ++j)
		{
			if(i == s)
			{
				if(str[i] != 'L') (dp[i][j] += dp[i - 1][j - 1]) %= mod;
				if(str[i] != 'R') (dp[i][j] += dp[i - 1][j]) %= mod;
				S = 1;
			}
			else if(i == e)
			{
				(dp[i][j] += (dp[i - 1][j] + dp[i - 1][j - 1]) % mod) %= mod;
				E = 1;
			}
			else
			{
				if(str[i] != 'L') (dp[i][j] += ((LL)max(0, j - S - E) * dp[i - 1][j - 1] % mod + (LL)(j - E) * dp[i - 1][j] % mod) % mod) %= mod;
				if(str[i] != 'R') (dp[i][j] += ((LL)j * dp[i - 1][j + 1] % mod + (LL)(j - S) * dp[i - 1][j] % mod) % mod) %= mod;
			}
		}
	cout << dp[n][1] << endl;

	return 0;
}
