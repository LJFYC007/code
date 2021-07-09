/***************************************************************
	File name: panda.cpp
	Author: ljfcnyali
	Create time: 2021年05月05日 星期三 08时52分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int Mod = 998244353;

int n, m, fac[maxn], inv[maxn], ans;
vector<int> f, g; bool a[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

inline vector<int> operator * (vector<int> a, vector<int> b)
{
	int n = a.size(), m = b.size(); vector<int> c(n + m - 1);
	REP(i, 0, n - 1) REP(j, 0, m - 1) c[i + j] = (c[i + j] + a[i] * b[j]) % Mod;
	c.resize(n); return c;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("panda.in", "r", stdin);
    freopen("panda.out", "w", stdout);
#endif
	scanf("%lld", &n); fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	f.resize(n + 1); g.resize(n + 1); 
	scanf("%lld", &m); REP(i, 1, m) { int x; scanf("%lld", &x); a[x] = true; } 
	scanf("%lld", &m); REP(i, 1, m) { int x; scanf("%lld", &x); g[x] = inv[x - 1]; } 
	ans = (a[1] && g[n]) ? 1 : 0;	f = g;
	REP(i, 2, n)
	{
		f = f * g;
		if ( a[i] ) ans = (ans + f[n] * fac[n] % Mod * inv[i] % Mod * power(n, i - 2)) % Mod;
	}
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
