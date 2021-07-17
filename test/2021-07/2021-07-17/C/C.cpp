/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年07月17日 星期六 09时51分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int maxm = 5010;
const int Mod = 998244353;

int n, f[maxn], s[maxm][maxm], c[maxm][maxm], fac[maxn], inv[maxn], r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; }
inline int sgn(int x) { return x & 1 ? -1 : 1; }

inline void NTT(vector<int> &f, int inv)
{
	int n = f.size();
	REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
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

inline vector<int> operator *(vector<int> a, vector<int> b)
{
	int n = a.size(), m = b.size(), len = 1;
	while ( len < n + m - 1 ) len <<= 1; a.resize(len); b.resize(len);
	NTT(a, 1); NTT(b, 1); REP(i, 0, len - 1) a[i] = a[i] * b[i] % Mod; NTT(a, -1);
	a.resize(n + m - 1); return a;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &f[i]);
	bool flag = true;
	REP(i, 1, n) if ( f[i] != 1 ) flag = false;
	if ( flag ) 
	{
		vector<int> a(n + 1), b(n + 1);
		REP(i, 0, n) 
		{
			a[i] = sgn(i) * inv[i] % Mod;
			b[i] = power(i, n) * inv[i] % Mod;
		}
		a = a * b;
		REP(i, 1, n) printf("%lld ", (a[i] * i % Mod + Mod) % Mod);
		puts("");
		return 0;
	}
	s[0][0] = 1;
	REP(i, 1, n) REP(j, 1, i) s[i][j] = (s[i - 1][j - 1] + j * s[i - 1][j]) % Mod;
	REP(k, 0, n - 1)
	{
		int ans = 0;
		REP(i, 1, n) ans = (ans + f[i] * C(n, i) % Mod * s[n - i][k]) % Mod;
		printf("%lld ", ans);
	}
	puts("");
    return 0;
}
