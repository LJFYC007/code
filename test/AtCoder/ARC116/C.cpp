/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年03月28日 星期日 20时12分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int Mod = 998244353;

int n, m, f[maxn][21], fac[maxn], inv[maxn], ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m); fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	REP(i, 1, m) f[i][1] = 1;
	REP(j, 1, 20) REP(i, 1, m) if ( f[i][j] ) 
	{
		for ( int x = 1; x * x <= i; ++ x ) if ( i % x == 0 ) 
		{
			if ( x != 1 ) f[i / x][j + 1] = (f[i / x][j + 1] + f[i][j]) % Mod;
			int y = i / x; if ( x == y ) continue ; 
			if ( y != 1 ) f[i / y][j + 1] = (f[i / y][j + 1] + f[i][j]) % Mod;
		}
	}

	REP(i, 1, m) REP(j, 1, 20) ans = (ans + f[i][j] * C(n - 1, j - 1)) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
