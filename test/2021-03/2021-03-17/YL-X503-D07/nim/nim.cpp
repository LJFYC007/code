/***************************************************************
	File name: nim.cpp
	Author: ljfcnyali
	Create time: 2021年03月17日 星期三 19时38分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3e3 + 10;
const int maxm = 5e6 + 10;
const int Mod = 1e9 + 7;
const int inv2 = (Mod + 1) / 2;

int n, m, L, fac[maxn], inv[maxn], f[maxn][maxn], g[maxn][maxn], h[maxn][maxn], a[maxm], F[maxn], G[maxn], k;
char s[maxm];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; } 
inline int sgn(int x) { return x & 1 ? -1 : 1; } 

inline void Solve()
{
	F[0] = 1; int a = -1, b = 1;
	for ( int i = L; i >= 1; -- i ) if ( s[i] == '1' ) 
	{
		a = (a + b) % Mod; b = power(2, L - i);
		int x = 1, y = 1, z = 1, inv = power(b, Mod - 2);
		for ( int j = 2; j <= n; j += 2 ) 
		{
			x = x * (a + b) % Mod * (a + b) % Mod;
			y = y * (b - a) % Mod * (b - a) % Mod;
			z = z * a % Mod * a % Mod;
			F[j] = (F[j] + ((x + y) * inv2 % Mod - z) * inv) % Mod;
		}
	}
	for ( int j = 1; j <= n; j += 2 ) REP(i, 0, j - 1) if ( i % 2 == 0 ) 
		F[j] = (F[j] + C(j, i) * power(a, i) % Mod * power(b, j - i - 1)) % Mod;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("nim.in", "r", stdin);
    freopen("nim.out", "w", stdout);
#endif
	n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld", &n); scanf("%s", s + 1); L = str(s + 1); 
	REP(i, 1, L) m = (m * 2 + (s[i] - '0')) % Mod;

	Solve(); f[0][0] = g[0][0] = 1;
	REP(j, 1, n)
	{
		int sum0 = 0, sum1 = 0;
		REP(i, 0, n)
		{
			if ( i & 1 ) f[i][j] = (f[i][j] + sum0 * fac[i - 1]) % Mod;
			else f[i][j] = (f[i][j] + sum1 * fac[i - 1]) % Mod;
			if ( i & 1 ) sum1 = (sum1 + f[i][j - 1] * inv[i]) % Mod;
			else sum0 = (sum0 + f[i][j - 1] * inv[i]) % Mod;
		}
	}
	REP(j, 1, n)
	{
		int sum0 = 0, sum1 = 0;
		REP(i, 0, n)
		{
			if ( i & 1 ) g[i][j] = (g[i][j] + sum1 * fac[i - 1]) % Mod;
			else g[i][j] = (g[i][j] + sum0 * fac[i - 1]) % Mod;
			if ( i & 1 ) sum1 = (sum1 + g[i][j - 1] * inv[i]) % Mod;
			else sum0 = (sum0 + g[i][j - 1] * inv[i]) % Mod;
		}
	}

	REP(i, 0, n) REP(x, 0, i) f[i][x] = f[i][x] * F[x] * sgn(x) % Mod * inv[i] % Mod;
	REP(i, 0, n) REP(x, 0, i) g[i][x] = g[i][x] * power(m, x) * sgn(x) % Mod * inv[i] % Mod;
	mem(F); REP(i, 0, n) REP(x, 0, i) F[i] = (F[i] + f[i][x]) % Mod, G[i] = (G[i] + g[i][x]) % Mod;
	int ans = 0; REP(i, 0, n) ans = (ans + F[i] * G[n - i]) % Mod;
	ans = ans * sgn(n) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
