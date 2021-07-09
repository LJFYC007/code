#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 1e5 + 10;
const int n = 300;

int k, m, Mod, fac[maxn], inv[maxn], ans, c[310][310];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int sgn(int x) { return x & 1 ? -1 : 1; } 

inline int C(int n, int m)
{
	if ( n < m || n < 0 || m < 0 ) return 0; 
	if ( n <= Mod && m <= Mod ) return c[n][m];
	return C(n / Mod, m / Mod) * c[n % Mod][m % Mod] % Mod;
}

inline int Solve(int n, int m)
{
	int ret = 0;
	REP(i, 0, m) ret = (ret + C(m, i) * sgn(i) * C(n + m - 1 - i * k, m - 1)) % Mod;
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
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

	REP(i, 1, m + 2) REP(j, 1, k - 1)
	{
		int x = m + 2 - i - j;
		ans = (ans + Solve(x, i - 1)) % Mod;
	}
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
