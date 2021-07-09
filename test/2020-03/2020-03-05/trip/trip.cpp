#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;
const int Mod = 1e9 + 7;

int n, m, l, a[maxn][maxn], x[maxn * maxn], s[maxn * maxn], ans;
int dt[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

namespace Subtask1
{
	int f[maxn][maxn];

	inline void Solve(int u, int v)
	{
		f[u][v] = 0;
		int k = 1;
		while ( k <= l )
		{
			u -= dt[s[k]][0]; v -= dt[s[k]][1]; ++ k;
			if ( u < 1 || v < 1 || u > n || v > n ) continue ;
			f[u][v] = min(f[u][v], k - 2);
		}
	}

	inline int main()
	{
		REP(i, 1, n) REP(j, 1, n) f[i][j] = l;
		REP(i, 1, m)
		{
			int y = x[i] % (n * n);
			int u = y / n + 1, v = y % n + 1;
			Solve(u, v);
		}
		REP(i, 0, n + 1) { Solve(0, i); Solve(n + 1, i); Solve(i, 0); Solve(i, n + 1); }
		REP(i, 1, n) REP(j, 1, n) ans = ans ^ f[i][j];
		printf("%lld\n", ans);
		return 0;
	}
}

signed main()
{
	freopen("trip.in", "r", stdin);
	freopen("trip.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &l);
	int A, B; scanf("%lld%lld%lld", &x[0], &A, &B);
	REP(i, 1, m + l) x[i] = (x[i - 1] * A + B) % Mod;
	REP(i, 1, m)
	{
		int y = x[i] % (n * n);
		a[y / n + 1][y % n + 1] = 1;
	}
	REP(i, 0, n + 1) a[0][i] = a[n + 1][i] = a[i][0] = a[i][n + 1] = 1;
	REP(i, 1, l) s[i] = x[i + m] % 4;
	if ( m <= 5000 ) return Subtask1 :: main();
	REP(i, 1, n) REP(j, 1, n)
	{
		if ( a[i][j] ) continue ;
		int u = i, v = j, k = 1;
		while ( k <= l )
		{
			u += dt[s[k]][0]; v += dt[s[k]][1];
			if ( a[u][v] ) break ;
			++ k;
		}
		ans ^= k - 1;
	}
	printf("%lld\n", ans);
	return 0;
}
