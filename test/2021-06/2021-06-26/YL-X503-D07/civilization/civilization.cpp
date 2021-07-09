/***************************************************************
	File name: civilization.cpp
	Author: ljfcnyali
	Create time: 2021年06月26日 星期六 09时02分45秒
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

int n, k, v[maxn], g[maxn], fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

inline int Solve(int n, int t)
{
	if ( n == 0 ) return t == 0;
	int ret = C(n + t - 1, n - 1);
	REP(i, 0, t - 2) ret = (ret - g[i] * C(t - 2 - i + n - i - 1, n - i - 1)) % Mod;
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("civilization.in", "r", stdin);
    freopen("civilization.out", "w", stdout);
#endif
	n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 0; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld%lld", &n, &k);
	REP(i, 0, k - 1) scanf("%lld", &v[i]);
	g[0] = 1;
	REP(i, 1, n + k)
	{
		g[i] = C(i + i, i);
		REP(j, 0, i - 1) g[i] = (g[i] - g[j] * C(i - j + i - j - 2, i - j)) % Mod;
	}

	REP(t, 0, n)
	{
		int ans = 0;
		REP(x, 0, k - 1)
			ans = (ans + Solve(x + t, t) * v[x]) % Mod;
		printf("%lld\n", (ans + Mod) % Mod);
	}
    return 0;
}
