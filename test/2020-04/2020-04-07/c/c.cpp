#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int T, n, m, k, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return (n < 0 || m < 0 || n < m) ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
	int N = maxn - 10;
	inv[0] = fac[0] = 1; REP(i, 1, N) fac[i] = fac[i - 1] * i % Mod;
	inv[N] = power(fac[N], Mod - 2); for ( int i = N - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld", &T);
	while ( T -- )
	{
		scanf("%lld%lld%lld", &n, &m, &k);
		printf("%lld\n", C((n + m + 1) / 2, n - k - n / 2) * C((n + m) / 2, k + n / 2) % Mod);
	}
	return 0;
}

