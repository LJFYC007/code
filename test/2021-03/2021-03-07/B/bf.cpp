/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年03月07日 星期日 09时20分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;
const int Mod = 998244353;

int T, n, f[maxn][maxn], fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
	scanf("%lld", &T); n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	while ( T -- ) 
	{
		scanf("%lld", &n); mem(f);
		f[0][0] = 1;
		REP(i, 1, n) REP(j, 1, i) REP(k, 1, i)
			f[i][j] = (f[i][j] + f[i - k][j - 1] * (j + j - 3) % Mod * inv[k]) % Mod;
		int ans = 0; REP(i, 2, n) ans = (ans - f[n][i] * inv[i]) % Mod;		
		ans = ans * fac[n] % Mod;
		printf("%lld\n", (ans + Mod) % Mod);
	}
    return 0;
}
