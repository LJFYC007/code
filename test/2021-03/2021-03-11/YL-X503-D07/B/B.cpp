#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 1e5 + 10;
const int n = 600;

int k, m, Mod, fac[maxn], inv[maxn], ans, c[610][610];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int sgn(int x) { return x & 1 ? -1 : 1; } 

inline int C(int n, int m)
{
	if ( n < m || n < 0 || m < 0 ) return 0; 
	if ( n <= Mod && m <= Mod ) return c[n][m];
	return C(n / Mod, m / Mod) * c[n % Mod][m % Mod] % Mod;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	cin >> k >> m >> Mod; 
	if ( m == 1 ) 
	{ 
		if ( k <= 2 ) puts("1");
		else puts("2"); 
		return 0; 
	} 
	c[0][0] = 1; 
	REP(i, 1, n) { c[i][0] = 1; REP(j, 1, i) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % Mod; } 

	REP(t, 1, k - 1)
	{
		int M = m - t, pos = (M - k - Mod) / (k + 1);
		REP(i, 0, M) REP(j, 0, i + 1)
		// REP(i, max(0ll, pos - Mod), min(M, pos + Mod + Mod)) 
		// REP(j, , i + 1)
			ans = (ans + C(i + 1, j) * sgn(j) * C(M - j * k, i)) % Mod;
	}

	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
