#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 19;
const int Mod = 998244353;

int n, m, N, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
	freopen("fft.in", "r", stdin);
	freopen("fft.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	N = n + m;
	fac[0] = inv[0] = 1; REP(i, 1, N) fac[i] = fac[i - 1] * i % Mod;
	inv[N] = power(fac[N], Mod - 2); for ( int i = N - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	int sum = 0;
	if ( n > m ) swap(n, m);
	REP(i, 1, n) sum = (sum + C(i + i, i) * C(n + m - i - i, n - i)) % Mod;
	int ans = n;
	ans = (ans - ((Mod + 1 >> 1) * sum % Mod) * power(C(n + m, n), Mod - 2)) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
