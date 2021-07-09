/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;
const int Mod = 998244353;

int n, m, ans[maxn], fac[maxn], inv[maxn], r[maxn];
vector<int> f, g, h;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int sgn(int x) { return x & 1 ? -1 : 1; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

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

inline vector<int> operator * (vector<int> a, vector<int> b)
{
	int n = a.size(), m = b.size(), len = 1;
	while ( len <= (n + m) ) len <<= 1; a.resize(len); b.resize(len);
	NTT(a, 1); NTT(b, 1); REP(i, 0, len - 1) a[i] = a[i] * b[i] % Mod; NTT(a, -1);
	a.resize(n + m - 1); return a;
}

signed main()
{
	freopen("perm.in", "r", stdin);
	freopen("perm.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	f.resize(1); f[0] = 1;
	REP(i, 1, m)
	{
		int len = 0;
		for ( int j = i; j <= n; j += m ) ++ len;
		g.resize(len / 2 + 2); REP(j, 0, len / 2 + 1) g[j] = C(len - j, j);
		g = g * g;
		f = f * g;
	}
	f.resize(n + 1);
	REP(k, 0, n) f[k] = f[k] * fac[n - k] % Mod;

	g.resize(n + 1); h.resize(n + 1);
	REP(i, 0, n) { h[n - i] = f[i] * fac[i] % Mod; g[i] = sgn(i) * inv[i]; }
	f = h * g;
	for ( int i = n; i >= 0; -- i ) printf("%lld\n", (f[i] * inv[n - i] % Mod + Mod) % Mod);
    return 0;
}
