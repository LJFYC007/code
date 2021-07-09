/***************************************************************
	File name: AGC026D.cpp
	Author: ljfcnyali
	Create time: 2021年04月23日 星期五 16时13分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 110;
const int Mod = 1e9 + 7;
const int INF = 1e18;

int n, a[maxn], f[maxn][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline int Solve(int l, int r, int lst, int L, int R)
{
	int ret = 1, Min = INF; REP(i, l, r) Min = min(Min, a[i]);
	if ( L <= l && r <= R ) ret = power(2, Min - lst + 1);
	for ( int i = l, j; i <= r; i = j + 1 ) 
	{
		j = i; if ( a[i] == Min ) continue ; 
		while ( j < r && a[j + 1] > Min ) ++ j;
		ret = ret * Solve(i, j, Min + 1, L, R) % Mod;
	}
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);
	f[1][1] = 2;
	REP(i, 1, n) REP(j, i, n)
	{
		f[j + 1][j + 1] = (f[j + 1][j + 1] + f[i][j] * Solve(1, n, 2, i, j)) % Mod;
		f[i][j + 1] = (f[i][j + 1] + f[i][j]) % Mod;
	}
	int ans = 0; REP(i, 1, n) ans = (ans + f[i][n] * Solve(1, n, 2, i, n)) % Mod;
	printf("%lld\n", ans);
    return 0;
}
