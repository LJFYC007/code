/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2021年04月19日 星期一 16时50分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 62;

int n, k, N, f[maxn][maxn * maxn][maxn], C[maxn][maxn], ans;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &k); N = n + n + 1;
	REP(i, 0, N) { C[i][0] = 1; REP(j, 1, i) C[i][j] = C[i - 1][j - 1] + C[i - 1][j]; }
	REP(i, 1, N) f[i][i * (i - 1) / 2][i - 1] = 1;
	REP(x, 0, N) REP(y, 0, k) REP(z, 0, N) if ( f[x][y][z] ) REP(o, 0, N)
		if ( x + o <= N && y + o * (o - 1) / 2 <= k && o >= z + 2 ) 
			f[x + o][y + o * (o - 1) / 2][o - (z + 2)] += f[x][y][z] * C[o - 1][z + 1];
	ans = f[N][k][0];
	REP(x, 0, N) REP(y, 0, k) REP(z, 1, N) ans += f[x][y][z] * f[N - x][k - y][z - 1];
	printf("%lld\n", ans);
    return 0;
}
