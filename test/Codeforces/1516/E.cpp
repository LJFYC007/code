/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2021年04月22日 星期四 09时26分14秒
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
const int Mod = 1e9 + 7;

int n, k, C[maxn][maxn], fac[maxn], inv[maxn], f[maxn][maxn], ans[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline int Solve(int n, int m)
{
	if ( n < m ) return 0;
	int ret = 1; REP(i, n - m + 1, n) ret = ret * i % Mod;
	return ret * inv[m] % Mod;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = 400; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 0; -- i ) inv[i] = inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld%lld", &n, &k);
	REP(i, 0, 400) REP(j, 0, 400) C[i][j] = Solve(n - i, j);
	f[0][0] = 1;		
	REP(x, 2, k + 1) for ( int i = k + k; i >= 0; -- i ) for ( int j = k; j >= 0; -- j ) if ( f[i][j] ) 
	{
		int val = 1, num = 0;
		for ( int o = x; o <= k + k; o += x ) 
		{
			num += x - 1;
			if ( i + o > n || j + num > k ) continue ; 
			val = val * C[i + o - x][x] % Mod; if ( x > 2 ) val = val * fac[x - 1] % Mod;
			f[i + o][j + num] = (f[i + o][j + num] + f[i][j] * val % Mod * inv[o / x]) % Mod;
		}
	}
	REP(i, 0, k + k) REP(j, 0, k) for ( int o = j; o <= k; o += 2 ) ans[o] = (ans[o] + f[i][j]) % Mod;
	REP(i, 1, k) printf("%lld ", (ans[i] + Mod) % Mod);
    return 0;
}
