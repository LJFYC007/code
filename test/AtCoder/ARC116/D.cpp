/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2021年03月28日 星期日 20时37分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int Mod = 998244353;
const int maxn = 5010;

int n, m, f[maxn][maxn], fac[maxn], inv[maxn];

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
	f[13][m] = 1;	
	for ( int i = 12; i >= 0; -- i ) REP(j, 0, m) if ( f[i + 1][j] ) 
	{
		int val = (1 << i);
		REP(k, 0, n) if ( !(k & 1) ) 
		{
			if ( k * val > j ) break ; 
			f[i][j - k * val] = (f[i][j - k * val] + f[i + 1][j] * C(n, k)) % Mod;
		}
	}
	printf("%lld\n", (f[0][0] + Mod) % Mod);
    return 0;
}
