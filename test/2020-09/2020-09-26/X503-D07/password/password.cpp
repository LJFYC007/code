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
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int N = 1e9;
const double eps = 1e-10;
const int seed = 107;
const int Mod = 998244353;

int n, m, a[maxn][10], s[maxn], t[maxn];
int Hash[2][maxn], p[maxn], inv[maxn];
double c[maxn], ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Get(int l, int r, int op)
{
	int ret = (Hash[op][r] - Hash[op][l - 1]) % Mod;
	ret = ret * inv[l - 1] % Mod;
	return (ret + Mod) % Mod;
}

inline int Find(int x, int y)
{
	int l = 1, r = m - y + 1, len = 0;
	while ( l <= r )
	{
		int Mid = l + r >> 1;
		if ( Get(y, y + Mid - 1, 0) == Get(x, x + Mid - 1, 1) ) { len = Mid; l = Mid + 1; }
		else r = Mid - 1;
	}
	return len;
}

signed main()
{
	freopen("password.in", "r", stdin);
	freopen("password.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	p[0] = inv[0] = 1; REP(i, 1, n) { p[i] = p[i - 1] * seed % Mod; inv[i] = inv[i - 1] * power(seed, Mod - 2) % Mod; }
	c[0] = 1;
	REP(i, 1, n)
	{
		t[i] = 10; c[i] = 1;
		 REP(j, 0, 9)
		{
			scanf("%lld", &a[i][j]);
			if ( a[i][j] > N / 2 ) { t[i] = j; c[i] = c[i - 1] * a[i][j] / N; }
		}
	}
	REP(i, 1, m) scanf("%1lld", &s[i]);

	REP(i, 1, m) Hash[0][i] = (Hash[0][i - 1] + s[i] * p[i]) % Mod;
	REP(i, 1, n) Hash[1][i] = (Hash[1][i - 1] + t[i] * p[i]) % Mod;

	REP(i, 1, n - m + 1)
	{
		int now = 1; ans = 1;
		while ( ans >= eps && now <= m )
		{
			int len = Find(i + now - 1, now);
			if ( len >= 1 )
			{
				ans = ans * c[i + now + len - 2] / c[i + now - 2];
				now += len;
			}
			else { ans = ans * a[i + now - 1][s[now]] / N; ++ now; }
		}
		printf("%.9lf\n", ans);
	}
    return 0;
}
