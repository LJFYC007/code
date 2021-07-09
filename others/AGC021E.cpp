/***************************************************************
	File name: AGC021E.cpp
	Author: ljfcnyali
	Create time: 2021年06月22日 星期二 21时29分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 998244353;

int n, m, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m || m < 0 ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; }

inline int Solve(int r, int b)
{
	if ( r < b || r < n ) return 0;
	if ( r >= b + n ) return C(r + b, r);
	if ( r == b ) return Solve(r, b - 1);
	return (C(r + b, r) - C(r + b, r + r - n + 1)) % Mod;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld%lld", &n, &m);
	int ans = 0;
	REP(r, 0, m) ans = (ans + Solve(r, m - r)) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
