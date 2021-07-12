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

const int maxn = 1e7 + 10;
const int maxm = 5010;
const int Mod = 1e9 + 7;

int n, m, fac[maxn], inv[maxn], g[maxm][maxm], h[maxm], f[maxm][maxm], a[maxn], b[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
inline int C(int n, int m) 
{ 
	if ( m < 0 ) return n == -1;
	return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; 
} 
inline int sgn(int x) { return x & 1 ? -1 : 1; } 
inline int get(int x) { return inv[x] * fac[x - 1] % Mod; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld%lld", &n, &m); n -= m;	

	f[0][0] = 1;
	REP(j, 0, m) 
	{
		REP(i, 0, m) h[i] = f[i][j] * fac[m - i] % Mod;
		int sum = 0;
		REP(i, 2, m) 
		{
			sum = (sum + h[i - 2] * get(m - i + 2)) % Mod;
			h[i] = (h[i] + sum) % Mod;
		}
		REP(i, 0, m) f[i][j] = h[i] * inv[m - i] % Mod;
		REP(i, 1, m) f[i][j + 1] = (f[i][j + 1] + f[i - 1][j]) % Mod;
	}
	REP(j, 0, m)
	{
		h[0] = fac[j]; int sum = 0;
		REP(i, 1, j) { sum = (sum + h[i - 1] * get(j - i + 1)) % Mod; h[i] = sum; }
		REP(i, 0, j) g[i][j] = h[i] * inv[j - i] % Mod;
	}
	g[m + 1][m + 1] = 1;
	int ans = g[m][m] * fac[n] % Mod * C(n + m - 1, m - 1) % Mod;

	REP(i, 0, m - 1) 
	{
		int num = 0;
		REP(k, 0, i)
		{
			int w = (C(n + m - k - 2, n - k) - C(n + i - 1 - k, i - 1)) % Mod;
			num = (num + f[i][k] % Mod * w) % Mod;
		}
		ans = (ans - g[m - i - 1][m - i - 1] * num % Mod * fac[n] % Mod) % Mod;
	}
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
