#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define int long long
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 110;
const int maxm = 2e5 + 10;
const int Mod = 998244353;

int n, a[maxm], f[maxn][maxn][maxn], fac[maxm], inv[maxm];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

inline void Solve()
{
	int m = n + a[1]; fac[0] = inv[0] = 1; REP(i, 1, m) fac[i] = fac[i - 1] * i % Mod;
	inv[m] = power(fac[m], Mod - 2); for ( int i = m - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	for ( int i = n; i >= 0; -- i ) printf("%lld ", C(a[1] + i - 1, i)); puts("");
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);
	if ( n > 100 ) { Solve(); return 0; }
	f[0][0][0] = 1;
	REP(i, 0, n - 1) REP(j, 0, i) REP(k, 0, a[i]) if ( f[i][j][k] ) 
	{
		REP(o, k, a[i + 1] - 1) f[i + 1][j][o] = (f[i + 1][j][o] + f[i][j][k]) % Mod;
		f[i + 1][j + 1][a[i + 1]] = (f[i + 1][j + 1][a[i + 1]] + f[i][j][k]) % Mod;
	}
	REP(i, 0, n)
	{
		int ans = 0;
		REP(j, 0, a[n]) ans = (ans + f[n][i][j]) % Mod;
		printf("%lld ", ans);
	}
	puts("");
	return 0;
}
