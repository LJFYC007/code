#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define int long long

const long double eps = 0.0000000001;
int n, m, k;

namespace Subtask1
{
	const int maxn = 500010;
	
	int y[maxn], c[maxn], a[maxn], s[maxn], z[maxn];
	
	inline void Solve()
	{
		REP(i, 1, m) scanf("%lld", &y[i]);
		REP(i, 1, k - 1) scanf("%lld", &c[i]);
		REP(i, 1, k) scanf("%lld%lld%lld", &a[i], &s[i], &z[i]);
		int last = 0; long double ans = 0;
		REP(i, 1, k)
		{
			long double x = y[s[i]];
			if ( last ) x = x * (1 - c[i - last] * 1.0 / 100);
			x = 1 - (x * 1.0) / z[i];
			x = max(x, (long double)0); x = 1 - x * x;
			if ( x < 0.64 + eps ) last = i;
			ans += x * a[i];
		}
		printf("%.2Lf\n", ans);
	}
}

namespace Subtask2
{
	const int maxn = 110;
	const int maxm = 1100;
	const int INF = 0x3f3f3f3f;
	
	long double dp[maxm][maxn][maxn];
	int x[maxn], y[maxn], c[maxn], a[maxn], ss[maxn], z[maxn];
	
	inline void Solve()
	{
		REP(i, 1, n) scanf("%lld", &x[i]);
		REP(i, 1, m) scanf("%lld", &y[i]);
		REP(i, 1, k - 1) scanf("%lld", &c[i]);
		REP(i, 1, k) scanf("%lld%lld%lld", &a[i], &ss[i], &z[i]);
		int num = 1 << n;
		REP(i, 0, num - 1) REP(j, 0, k) REP(o, 0, k) dp[i][j][o] = -INF;
		dp[0][0][0] = 0;
		REP(i, 1, k)
			REP(s, 0, num - 1)
				for ( int S = s; ; S = (S - 1) & s)
				{
					long double p = y[ss[i]];
					REP(j, 1, n)
						if ( ((1 << (j - 1)) & s) && !((1 << (j - 1)) & S) ) p = p * (1 + x[j] / 100.0);
					REP(j, 0, i - 1)
					{
						if ( dp[S][i - 1][j] == -0x3f3f3f3f ) continue ;
						long double q = p;
						if ( j != 0 ) q = q * (1 - c[i - j] / 100.0);
						q = max((long double)0, 1 - q / z[i]); q = 1 - q * q;
						if ( q < 0.64 + eps ) dp[s][i][i] = max(dp[s][i][i], dp[S][i - 1][j] + q * a[i]);
						else dp[s][i][j] = max(dp[s][i][j], dp[S][i - 1][j] + q * a[i]);
					}
					if ( S == 0 ) break ; 
				}
		long double ans = 0;
		REP(i, 0, k) ans = max(ans, dp[num - 1][k][i]);
		printf("%.2Lf\n", ans);
	}
}

signed main()
{
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &k);	
	if ( n == 0 ) { Subtask1 :: Solve(); return 0; }
	Subtask2 :: Solve();
	return 0;
}

