#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const double eps = 1e-9;

int n, a, b, k, g[6][maxn], f[2][maxn], *pre = f[0], *nex = f[1], p[maxn], ans1, ans2;
double ans, dp[6][110];
pii block[110];

inline void Solve(int o, int i)
{
	int x = p[i], y = g[o][x];
	double A = dp[o - 1][x - y], B = dp[o - 1][x + y];
	int L = block[y].first, R = block[y].first;
	int l = 0, r = L - 1;
	while ( l <= r )
	{
		int Mid = l + r >> 1;
		if ( dp[o - 1][p[i - Mid]] == A && (dp[o - 1][p[i + Mid]] == B || i + Mid >= b) ) { r = Mid - 1; L = Mid; }
		else l = Mid + 1;
	}
	l = R + 1; r = i;
	while ( l <= r )
	{
		int Mid = l + r >> 1;
		if ( dp[o - 1][p[i - Mid]] == A && (dp[o - 1][p[i + Mid]] == B || i + Mid >= b) ) { l = Mid + 1; R = Mid; }
		else r = Mid - 1;
	}
	printf("%d %d %d %d %d\n", x, y, i, L, R);
	if ( L == 0 ) { ++ nex[i]; -- nex[i + 1]; ++ L; }
	nex[i - L + 1] -= pre[i]; nex[i - R] += pre[i]; nex[i + L] += pre[i]; nex[i + R + 1] -= pre[i];
}

int main()
{
	freopen("best.in", "r", stdin);
	freopen("best.out", "w", stdout);
	scanf("%d%d%d", &a, &b, &k);
	n = 1 << k; int last = -1;
	REP(i, 0, n - 1)
	{
		block[i].first = last + 1;
		block[i].second = (b * (i + 1) * 1.0) / n - eps;
		REP(j, block[i].first, block[i].second) p[j] = i;
		last = block[i].second;
	}
	block[n].first = block[n].second = b; p[b] = n;
	REP(i, 0, n) printf("%d %d\n", block[i].first, block[i].second);
	dp[0][n] = 1;
	REP(o, 1, k) REP(i, 0, n)
	{
		double Max = 0;
		for ( int j = 0; j <= i && i + j <= n; ++ j )
		{
			if ( 0.5 * (dp[o - 1][i + j] + dp[o - 1][i - j]) > Max )
			{
				Max = 0.5 * (dp[o - 1][i + j] + dp[o - 1][i - j]);
				g[o][i] = j;
			}
		}
		dp[o][i] = Max;
	}
	puts(""); REP(i, 1, k) { REP(j, 0, n) printf("%.6lf ", dp[i][j]); puts(""); }
	puts(""); REP(i, 1, k) { REP(j, 0, n) printf("%d ", g[i][j]); puts(""); }
	pre[a] = 1;
	for ( int o = k; o >= 2; -- o )
	{
		REP(i, b, 2 * b) ans1 += pre[i];
		REP(i, 0, 2 * b) nex[i] = 0;
		REP(i, 0, b - 1) if ( pre[i] ) Solve(o, i);
		REP(i, 1, 2 * b) nex[i] += nex[i - 1];
		swap(pre, nex);
	}
	REP(i, b, 2 * b) ans1 += pre[i];
	REP(i, (b + 1) / 2, b - 1) ans1 += pre[i] * (i + i - b + 1);
	printf("%d\n", ans1);
	mem(f); pre[a] = 1;
	for ( int o = k; o >= 2; -- o )
	{
		REP(i, b, 2 * b) ans2 += pre[i];
		REP(i, 0, 2 * b) nex[i] = 0;
		REP(i, 0, b - 1) if ( pre[i] )
		{
			int L = 0, R = i;
			if ( L == 0 ) { ++ nex[i]; -- nex[i + 1]; ++ L; }
			nex[i - L + 1] -= pre[i]; nex[i - R] += pre[i]; nex[i + L] += pre[i]; nex[i + R + 1] -= pre[i];
		}
		REP(i, 1, 2 * b) nex[i] += nex[i - 1];
		swap(nex, pre);
	}
	REP(i, b, 2 * b) ans2 += pre[i];
	REP(i, 0, b - 1) ans2 += (i + 1) * pre[i];
	printf("%d\n", ans2);
	printf("%.8lf\n", ans1 * 1.0 / ans2);
	return 0;
}
