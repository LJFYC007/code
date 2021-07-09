#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>
#define int long long

const int maxn = 1e7 + 10;
const int Mod = 998244353;

int n, a[maxn], b[maxn], fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

signed main()
{
    freopen("tros.in", "r", stdin);
    freopen("tros.out", "w", stdout);
	n = maxn - 7; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;

	REP(i, 1, n) a[i] = (a[i - 1] + (-i * i + i - 1) % Mod * inv[i] % Mod * fac[i - 1]) % Mod;
	REP(i, 1, n) b[i] = (b[i - 1] + i * inv[i + 1] % Mod * fac[i]) % Mod;
	REP(i, 1, n) a[i] = a[i] * fac[i] % Mod;
	REP(i, 1, n) b[i] = b[i] * fac[i + 1] % Mod;

	int l, r; scanf("%lld%lld", &l, &r);
	int ans = 0; REP(i, l, r) ans ^= ((a[i] + b[i]) % Mod + Mod) % Mod;
	printf("%lld\n", ans);
    return 0;
}
