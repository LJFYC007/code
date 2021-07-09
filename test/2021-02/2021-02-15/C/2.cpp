/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年02月15日 星期一 10时34分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 110;
const int Mod = 998244353;

int n, m, k, a[maxn], ans, fac[maxn], inv[maxn], f[maxn][maxn], h[2][maxn], F[maxn], G[maxn];
int g1[maxn][maxn][maxn], g2[maxn][maxn][maxn], G1[maxn][maxn], G2[maxn][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; } 
inline int Get(int n, int m)
{
	int ret = inv[m];
	REP(i, n - m + 1, n) ret = ret * i % Mod;
	return ret;
}
inline int sgn(int x) { return x & 1 ? -1 : 1; } 

inline int Solve(int n)
{
	mem(f); REP(i, 0, n) if ( i % 2 == 0 ) f[k][i] = C(n, i);
	REP(o, 0, 1) REP(i, 0, n) 
	{
		h[o][i] = 0;
		REP(j, 0, n) h[o][i] = (h[o][i] + C(n - i, j + j + o)) % Mod;
	}
	for ( int i = k - 1; i >= 1; -- i ) REP(o, 0, n)
	{
		int len = (a[i + 1] - a[i] - 1) % (Mod - 1);
		int val = f[i + 1][o] * power(h[0][o], len) % Mod;
		REP(j, 0, o)
		{
			int x = val * h[j % 2][o] % Mod;
			x = x * C(o, j) % Mod;
			f[i][j] = (f[i][j] + x) % Mod;
		}
	}
	return f[1][0] * power(h[0][0], a[1] % (Mod - 1)) % Mod;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &k); fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	REP(i, 1, k) { scanf("%lld", &a[i]); m = (m + power(2, a[i] % (Mod - 1))) % Mod; }

	g1[0][0][0] = G1[0][0] = 1;
	REP(i, 1, n / 2) REP(j, 1, i) REP(o, 0, i) REP(k, 1, i)
	{
		g1[i][j][k] = (g1[i][j][k] + g1[i - k][j - 1][o] * inv[k + k]) % Mod;
		G1[i][j] = (G1[i][j] + g1[i - k][j - 1][o] * inv[k + k]) % Mod;
	}

	g2[0][0][0] = G2[0][0] = 1;
	REP(i, 1, n / 2) REP(j, 1, i) REP(o, 0, i) REP(k, 1, i)
	{
		g2[i][j][k] = (g2[i][j][k] + g2[i - k][j - 1][o] * inv[k + k + 1]) % Mod;
		G2[i][j] = (G2[i][j] + g2[i - k][j - 1][o] * inv[k + k + 1]) % Mod;
	}

	REP(i, 0, n) G[i] = Solve(i);
	REP(i, 0, n)
	{
		F[i] = G[i] * inv[i] % Mod;
		REP(j, 0, i - 1) REP(o, 0, i) REP(s, 0, j)
		{
			if ( (i - j) % 2 != 0 ) continue ;
			int t = (i - j) / 2;
			REP(x, 0, t)
			{
				int val = F[j] * G1[x][o] % Mod * G2[t - x][s] % Mod;
				val = val * C(j, s) % Mod;
				val = val * Get(m - j, o) % Mod;
				F[i] = (F[i] - val) % Mod;
			}
		}
	}

	printf("%lld\n", (F[n] + Mod) % Mod);
    return 0;
}
