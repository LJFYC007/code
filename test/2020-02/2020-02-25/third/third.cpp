#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 30;
const int maxm = 5e4 + 10;
const int Mod = 998244353;

int n, m, q, a[maxm];

struct matrix
{
	int n, m, a[maxn][maxn];
	matrix operator * (const matrix b) const
	{
		matrix c; c.n = n; c.m = b.m;
		REP(i, 1, c.n) REP(j, 1, c.m)
		{
			c.a[i][j] = 0;
			REP(k, 1, m) c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j]) % Mod;
		}
		return c;
	}
} suf[maxm], pre[maxm], f[maxm], g;

matrix Solve(

signed main()
{
	freopen("third.in", "r", stdin);
	freopen("third.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &q);
	REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 1, n)
	{
		f[i].n = f[i].m = m + 1;
		REP(j, 1, m + 1) f[i].a[j][j] = 1;
		REP(j, 1, m + 1) f[i].a[j][a[i]] = 1;
	}
	pre[1] = f[1];
	REP(i, 2, n) pre[i] = pre[i - 1] * f[i];
	suf[n] = f[n];
	for ( int i = n - 1; i >= 1; -- i ) suf[i] = f[i] * suf[i + 1];

	REP(i, 1, m + 1) { REP(j, 1, m + 1) printf("%lld ", f[1].a[i][j]); puts(""); } puts("");
	REP(i, 1, m + 1) { REP(j, 1, m + 1) printf("%lld ", f[2].a[i][j]); puts(""); } puts("");
	REP(i, 1, m + 1) { REP(j, 1, m + 1) printf("%lld ", pre[2].a[i][j]); puts(""); } puts("");

	while ( q -- )
	{
		int b, c, d; scanf("%lld%lld%lld", &b, &c, &d);
		g.n = g.m = m + 1;
		REP(i, 1, m + 1) REP(j, 1, m + 1) g.a[i][j] = 0;
		REP(i, 1, m + 1) g.a[i][i] = 1;
		REP(i, 1, m + 1) g.a[i][c] = 1;
		if ( b < n ) g = g * suf[b + 1];
		if ( b > 1 ) g = g * pre[b - 1];
		int x = m + 1, y = d;
		printf("%lld\n", (g.a[x][y] + Mod) % Mod);
	}
	return 0;
}
