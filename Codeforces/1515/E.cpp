/***************************************************************
	File name: HaHa
	Author: ljfcnyali
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

int n, Mod, f[maxn][maxn][2][2], fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &Mod);
	fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;

	REP(x, 0, 1) REP(y, 0, 1) f[0][0][x][y] = 1;
	f[1][0][1][1] = 1;

	REP(i, 1, n) REP(j, 1, i) REP(x, 0, 1) REP(y, 0, 1)
	{
		if ( i == 1 && j == 1 && x == 1 && y == 1 ) continue ; 
		REP(s, 1, i) REP(o, 0, j - 1)
			f[i][j][x][y] = (f[i][j][x][y] + f[s - 1][o][x][1] * f[i - s][j - 1 - o][1][y]) % Mod;
		f[i][j][x][y] = f[i][j][x][y] * power(j, Mod - 2) % Mod;
	}

	REP(i, 1, n) REP(j, 1,i) printf("%lld %lld %lld\n", i, j, f[i][j][1][1] * fac[i] % Mod);

	int ans = 0;
	REP(i, 1, n) ans = (ans + f[n][i][0][0] * fac[i]) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
