/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年03月07日 星期日 09时20分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e6 + 10;
const int Mod = 998244353;

int T, n, fac[maxn], inv[maxn], g[maxn], r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int sgn(int x) { return x & 1 ? -1 : 1; } 
inline int add(int x, int y) { return x + y >= Mod ? x + y - Mod : x + y; }

inline void NTT(vector<int> &f, int inv)
{
	int n = f.size(); REP(i, 0, n - 1) f[i] = (f[i] + Mod) % Mod;
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
				f[i + j] = add(x, y); f[i + Mid + j] = add(x, Mod - y);
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
	scanf("%lld", &T); n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	g[1] = 1; REP(i, 2, n) g[i] = g[i - 1] * (i + i - 3) % Mod;

	while ( T -- ) 
	{
		scanf("%lld", &n); int ans = 0;
		vector<int> a(n + 1), b(n + 1);
		REP(i, 0, n) { a[i] = sgn(i) * inv[i] % Mod; b[i] = power(i, n) * inv[i] % Mod; } 
		a = a * b;
		REP(i, 2, n) ans = (ans + a[i] * g[i]) % Mod;
		printf("%lld\n", (ans + Mod) % Mod);
	}
    return 0;
}
