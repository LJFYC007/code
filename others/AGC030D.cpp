/***************************************************************
	File name: AGC030D.cpp
	Author: ljfcnyali
	Create time: 2021年03月16日 星期二 16时31分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3010;
const int Mod = 1e9 + 7;
const int inv2 = (Mod + 1) / 2;

int n, q, a[maxn], f[maxn][maxn], ans, g[maxn][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &q); REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 1, n) REP(j, 1, n) f[i][j] = a[i] > a[j];
	REP(o, 1, q)
	{
		int x, y; scanf("%lld%lld", &x, &y);
		REP(i, 1, n) { g[i][x] = f[i][x]; g[x][i] = f[x][i]; g[i][y] = f[i][y]; g[y][i] = f[y][i]; } 
		REP(i, 1, n) if ( i != x && i != y ) 
		{
			f[x][i] = (f[x][i] + g[y][i]) * inv2 % Mod;
			f[i][x] = (f[i][x] + g[i][y]) * inv2 % Mod;
			f[y][i] = (f[y][i] + g[x][i]) * inv2 % Mod;
			f[i][y] = (f[i][y] + g[i][x]) * inv2 % Mod;
		}
		f[x][y] = (f[x][y] + g[y][x]) * inv2 % Mod;
		f[y][x] = (f[y][x] + g[x][y]) * inv2 % Mod;
	}
	REP(i, 1, n) REP(j, i + 1, n) ans = (ans + f[i][j]) % Mod;
	ans = ans * power(2, q) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
