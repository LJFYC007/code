/***************************************************************
	File name: AGC041F.cpp
	Author: ljfcnyali
	Create time: 2021年07月04日 星期日 19时52分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 410;
const int Mod = 998244353;

int n, a[maxn], p[maxn], fac[maxn], inv[maxn]; 
struct node { vector<int> f, g, h; } ;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

vector<int> operator *(vector<int> a, vector<int> b)
{
	int n = a.size(), m = b.size(); vector<int> c(n + m - 1);
	REP(i, 0, n - 1) REP(j, 0, m - 1) c[i + j] = (c[i + j] + a[i] * b[j]) % Mod;
	return c;
}

vector<int> operator +(vector<int> a, vector<int> b)
{
	for ( int i = 0; i < a.size(); ++ i ) a[i] = (a[i] + b[i]) % Mod;
	return a;
}

inline node Solve(int l, int r, int height)
{
	if ( l > r ) { vector<int> a(1); a[0] = 1; return {a, a, a}; }
	if ( l == r && a[l] < height ) { vector<int> a(2), b(2); a[0] = b[1] = 1; return {a, b, a}; }
	vector<int> f(1) , g(1), h(1); f[0] = g[0] = h[0] = 1;
	for ( int L = l, R; L <= r; L = R + 1 ) 
	{
		R = L; if ( a[L] > height ) while ( R < r && a[R + 1] > height ) ++ R; 
		node x = Solve(L, R, height + 1);
		f = f * x.f; g = g * x.g; h = h * x.h;
	}

	int len = r - l + 1; vector<int> a(len + 1), b(len + 1), c(len + 1);
	REP(i, 0, len) REP(j, 0, i) 
	{
		a[i - j] = (a[i - j] + C(i, j) * f[i] % Mod * (p[len - i] - (j == 0))) % Mod;
		b[i - j] = (b[i - j] + C(i, j) * g[i] % Mod * p[len - i]) % Mod;
		c[i - j] = (c[i - j] + C(i, j) * h[i] % Mod * (p[len - i] - (j == 0))) % Mod;
	}
	REP(i, 0, len) a[i] = (a[i] + g[i]) % Mod;	
	
	return {a, b, c};
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);
	p[0] = 1; REP(i, 1, n) p[i] = p[i - 1] * 2 % Mod;
	fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	node x = Solve(1, n, 1);
	int ans = x.f[0];
	REP(i, 1, n) ans = (ans + x.h[i]) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
