/***************************************************************
	File name: AGC045D.cpp
	Author: ljfcnyali
	Create time: 2021年07月11日 星期日 16时35分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 60;
const int Mod = 1e9 + 7;

int n, m, fac[maxn], inv[maxn], f[maxn][maxn], g[maxn], h[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
inline int C(int n, int m) 
{ 
	if ( m < 0 ) return n == -1;
	return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; 
} 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = maxn - 1; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1 ] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld%lld", &n, &m); 
	f[0][0] = 1; n -= m;	
	REP(i, 0, n) REP(j, 0, m) REP(x, i, n) REP(y, j + 1, m)
	{
		// if ( i < n && x == i && y == j + 1 ) continue ; 
		f[x][y] = (f[x][y] + f[i][j] * C(n - i, x - i) % Mod * C(m - j - 1, y - j - 1) % Mod * fac[x + y - i - j - 1]) % Mod;
	}
	printf("%lld\n", f[n][m]);
	g[0] = 1;
	REP(i, 0, m) REP(k, 1, m - i)
		g[i + k] = (g[i + k] + g[i] * C(m - i - 1, k - 1) % Mod * fac[k - 1]) % Mod;
	h[0] = 1;
	REP(i, 1, m)
	{
		int w = fac[n] * C(n + i - 1, i - 1)% Mod;
		h[i] = g[i] * w % Mod;
		REP(j, 0, i - 1) REP(k, 0, n - 1)
		{
			int ret = h[j] * fac[k] % Mod * C(k + j - 1, j - 1) % Mod;
			ret = ret * g[i - j - 1] % Mod * fac[n - k] % Mod * C(n - k + i - j - 2, i - j - 2) % Mod;
			ret = ret * C(i, j) % Mod;
			ret = ret * (i - j) % Mod;
			h[i] = (h[i] - ret) % Mod;
		}
		cerr << h[i] << endl;
		h[i] = h[i] * power(w, Mod - 2) % Mod;
	}
	printf("%lld\n", (h[m] + Mod) % Mod);
    return 0;
}
