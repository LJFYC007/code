/***************************************************************
	File name: AGC024E.cpp
	Author: ljfcnyali
	Create time: 2021年06月19日 星期六 16时07分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 310;

int n, Mod, k, f[maxn][maxn], g[maxn], h[maxn][maxn], C[maxn][maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &k, &Mod); 
	C[0][0] = 1; REP(i, 1, n) { C[i][0] = 1; REP(j, 1, i) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mod; }
	REP(i, 0, k + 1) f[0][i] = 1, h[0][i] = k + 2 - i; g[0] = 1;
	for ( int j = k; j >= 1; -- j ) REP(i, 0, n)
	{
		REP(o, 1, i) f[i][j] = (f[i][j] + h[o - 1][j + 1] * f[i - o][j] % Mod * C[i - 1][o - 1]) % Mod;
		h[i][j] = (h[i][j + 1] + f[i][j]) % Mod;
	}
	REP(i, 1, n) REP(o, 1, i) REP(j, 1, k)
		g[i] = (g[i] + f[o - 1][j + 1] * g[i - o] % Mod * C[i - 1][o - 1]) % Mod;
	printf("%lld\n", (g[n] + Mod) % Mod);
    return 0;
}
