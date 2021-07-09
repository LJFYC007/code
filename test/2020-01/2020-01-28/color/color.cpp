#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int N = 2e6;
const int Mod = 1e9 + 7;

int n, m, k, T, fac[maxn], inv[maxn], M, f[maxn], ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	fac[0] = inv[0] = 1; REP(i, 1, N) fac[i] = fac[i - 1] * i % Mod;
	inv[N] = power(fac[N], Mod - 2); for ( int i = N - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld", &T);
	while ( T -- )
	{
		scanf("%lld%lld%lld", &n, &m, &k);
		M = min(n, k);
		REP(i, 1, M)
		{
			f[i] = 0; int x = 1;
			for ( int j = i; j >= 1; -- j )
			{
				f[i] = (f[i] + x * C(i, j) * power(j, n)) % Mod;
				x *= -1;
			}
		}
		ans = 0;
		if ( m == 2 )
		{
			REP(i, 1, M) ans = (ans + (f[i] * f[i] % Mod) * C(k, i) * C(k, i)) % Mod;
			printf("%lld\n", ans);
			continue ;
		}
		if ( m == 1 )
		{
			REP(i, 1, M) ans = (ans + f[i] * C(k, i)) % Mod;
			printf("%lld\n", ans);
			continue ;
		}
		REP(i, 1, M) REP(j, 1, i)
		{
			if ( k == i && i != j ) continue ;
			int ret = (C(k, i) * C(i, j) % Mod) * C(k - i, i - j) % Mod;
			int sum = power(j, n * (m - 2) % (Mod - 1));
			//int x = ((ret * sum % Mod) * (f[i] * f[i] % Mod)) % Mod;
			//printf("%lld %lld %lld\n", i, j, x);
			ans = (ans + (ret * sum % Mod) * (f[i] * f[i] % Mod)) % Mod;
		}
		printf("%lld\n", (ans + Mod) % Mod);
	}
	return 0;
}
