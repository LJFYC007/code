/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2021年05月04日 星期二 22时15分14秒
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

int n, Mod, f[maxn][maxn], p[maxn], ans, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &Mod); 
	p[0] = fac[0] = inv[0] = 1; REP(i, 1, n) p[i] = p[i - 1] * 2 % Mod, fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	f[0][0] = 1;
	REP(i, 0, n - 1) REP(j, 0, i) if ( f[i][j] ) REP(k, 1, n) if ( i + k <= n ) 
		f[i + k + 1][j + k] = (f[i + k + 1][j + k] + f[i][j] * p[k - 1] % Mod * C(j + k, k)) % Mod;
	REP(i, 1, n) ans = (ans + f[n + 1][i]) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
