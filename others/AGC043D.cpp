/***************************************************************
	File name: AGC043D.cpp
	Author: ljfcnyali
	Create time: 2021年07月06日 星期二 16时03分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6010;
const int Delta = 6000;

int f[maxn][maxn * 2], n, Mod;

inline int A(int n, int m)
{
	if ( m == 1 ) return n;
	return 1ll * n * (n - 1) % Mod; 
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &Mod);
	f[0][Delta] = 1;
	REP(i, 0, n * 3) REP(j, Delta - i, Delta + i) 
	{
		f[i + 1][j + 1] = (f[i + 1][j + 1] + f[i][j]) % Mod;
		f[i + 2][j - 1] = (f[i + 2][j - 1] + 1ll * f[i][j] * (i + 1)) % Mod;
		f[i + 3][j] = (f[i + 3][j] + 1ll * f[i][j] * (i + 1) % Mod * (i + 2)) % Mod;
	}
	int ans = 0;
	REP(i, Delta, Delta + n + n + n) ans = (ans + f[n + n + n][i]) % Mod;
	printf("%d\n", (ans + Mod) % Mod);
    return 0;
}
