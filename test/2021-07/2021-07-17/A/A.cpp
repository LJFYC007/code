/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年07月17日 星期六 09时01分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5e6 + 10;
const int Mod = 998244353;

int n, m, a, b, fac[maxn], inv[maxn], ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) 
{ 
	if ( m == -1 ) return n == -1;
	return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; 
}

inline int Solve(int n, int m, int k)
{
	n -= (m - k) * 2;
	if ( m < k || n < 0 ) return 0;
	return C(n - 1, m - 1);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = maxn - 10;
	fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld%lld%lld", &n, &a, &b);
	REP(i, 0, n) if ( a + b - i <= n && i <= min(a, b) )
	{
		int ret = 0;
		if ( i % 2 == 0 ) 
			ret = (Solve(a, i / 2 + 1, 2) * Solve(b, i / 2, 0) + Solve(b, i / 2 + 1, 2) * Solve(a, i / 2, 0)) % Mod;
		else 
			ret = Solve(a, i / 2 + 1, 1) * Solve(b, i / 2 + 1, 1) * 2 % Mod;
		ans = (ans + ret * (n - a - b + i + 1)) % Mod;
	}
	printf("%lld\n", ans);
    return 0;
}
