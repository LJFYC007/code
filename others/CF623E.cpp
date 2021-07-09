/***************************************************************
	File name: CF623E.cpp
	Author: ljfcnyali
	Create time: 2021年04月01日 星期四 08时34分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3e4 + 10;
const int Mod = 1e9 + 7;

int n, m, k, fac[maxn], inv[maxn], p[maxn], ans, r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

vector<int> operator *(vector<int> a, vector<int> b)
{
	int n = a.size(), m = b.size(), len = 1, pos = m;
	vector<int> c(k + 1); 
	REP(i, 0, m - 1) if ( b[i] > 0 ) { pos = i; break ; } 
	REP(i, 0, n - 1) if ( a[i] ) REP(j, pos, m - 1) 
	{
		if ( i + j > k ) break ; 
		c[i + j] = (c[i + j] + a[i] * b[j]) % Mod;
	}
	return c;
}

inline vector<int> Solve(int n)
{
	if ( n == 1 ) { vector<int> f(k + 1); f[0] = 0; REP(i, 1, k) f[i] = inv[i]; return f; } 
	int Mid = n / 2, x = 1; vector<int> f = Solve(Mid), g = f;
	REP(i, 0, k) { g[i] = g[i] * x % Mod; x = x * p[Mid] % Mod; } 
	f = f * g; 
	if ( n & 1 ) 
	{
		x = 1; REP(i, 0, k) { g[i] = x * inv[i] % Mod; x = x * p[n - 1] % Mod; }
		-- g[0]; f = f * g; 
	}
	return f;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	p[0] = 1; REP(i, 1, n) p[i] = p[i - 1] * 2 % Mod;
	scanf("%lld%lld", &n, &k); m = n;
	if ( n > k ) { puts("0"); return 0; } 
	vector<int> f = Solve(n);
	REP(i, n, k) ans = (ans + f[i] * fac[k] % Mod * inv[k - i]) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
