/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年03月09日 星期二 11时26分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;
const int Mod = 998244353;

int n, p, fac[maxn], inv[maxn], ans, f[maxn][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int sgn(int x) { return x & 1 ? -1 : 1; } 
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &p); fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	ans = power(p - 1, n) % Mod;
	if ( n & 1 ) ans = (ans - (power(p - 1, n) - (p - 1)) * power(p, Mod - 2)) % Mod;
	else ans = (ans - (power(p - 1, n) + (p - 1)) * power(p, Mod - 2)) % Mod;
	if ( p <= n ) 
	{
		f[0][0] = 1;	
		REP(i, 1, n) 
		{
			int sum = 0;
			REP(j, 1, n) 
			{
				sum = (sum + f[i - 1][j - 1]) % Mod;
				if ( j > p - 2 ) sum = (sum - f[i - 1][j - p + 1]) % Mod;
				f[i][j] = sum;
			}
		}
		REP(i, 0, n) REP(j, 0, n) if ( (i + (n - i) * p - j) % p && j + p <= i ) 
			ans = (ans - f[n - i][j] * C(n, i) % Mod * (p - 1)) % Mod;
	}
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
