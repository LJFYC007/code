/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年02月23日 星期二 14时56分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int n1, n2, m1, m2, L, f[maxn], g[maxn], n, ans[maxn], fac[maxn], inv[maxn], r[maxn];
struct Matrix 
{
	int n, m, a[11][11];
} f1, f2, t1, t2;

Matrix operator * (Matrix a, Matrix b)
{
	Matrix c; c.n = a.n; c.m = b.m;
	REP(i, 1, c.n) REP(j, 1, c.m) c.a[i][j] = 0;
	REP(i, 1, c.n) REP(k, 1, a.m) REP(j, 1, c.m) c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % Mod;
	return c;
}

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return fac[n] * inv[m] % Mod * inv[n - m] % Mod; }

inline void NTT(int *f, int n, int inv)
{
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
	REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
	for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
	{
		int tmp = power(3, (Mod - 1) / (Mid << 1));
		if ( inv == -1 ) tmp = power(tmp, Mod - 2); 
		for ( int i = 0; i < n; i += (Mid << 1) ) 
		{
			int sum = 1;
			for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod ) 
			{
				int x = f[i + j], y = f[i + Mid + j] * sum % Mod;
				f[i + j] = (x + y) % Mod; f[i + Mid + j] = (x - y) % Mod;
			}
		}
	}
	if ( inv == -1 ) 
	{
		inv = power(n, Mod - 2); 
		REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld", &L);
	scanf("%lld%lld", &n1, &m1); REP(i, 1, m1) { int u, v; scanf("%lld%lld", &u, &v); f1.a[u][v] = f1.a[v][u] = 1; }
	scanf("%lld%lld", &n2, &m2); REP(i, 1, m2) { int u, v; scanf("%lld%lld", &u, &v); f2.a[u][v] = f2.a[v][u] = 1; }
	f1.n = f1.m = n1; f2.n = f2.m = n2;
	t1 = f1; t2 = f2; f[0] = n1; g[0] = n2;
	REP(i, 1, L)
	{
		REP(j, 1, n1) f[i] = (f[i] + t1.a[j][j]) % Mod;
		REP(j, 1, n2) g[i] = (g[i] + t2.a[j][j]) % Mod;
		t1 = t1 * f1; t2 = t2 * f2;
	}
	n = 1; while ( n < L + L ) n <<= 1;
	REP(i, 0, n - 1) f[i] = f[i] * inv[i] % Mod;
	REP(i, 0, n - 1) g[i] = g[i] * inv[i] % Mod;
	NTT(f, n, 1); NTT(g, n, 1); REP(i, 0, n - 1) f[i] = f[i] * g[i] % Mod; NTT(f, n, -1);
	REP(i, 0, L) printf("%lld\n", (f[i] * fac[i] % Mod + Mod) % Mod);
    return 0;
}
