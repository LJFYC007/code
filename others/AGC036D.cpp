/***************************************************************
	File name: AGC036D.cpp
	Author: ljfcnyali
	Create time: 2021年02月03日 星期三 15时46分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 510;
const int INF = 1e18;

int n, f[maxn][maxn][maxn], a[maxn][maxn], pre[maxn][maxn], suf[maxn][maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) REP(j, 1, n) if ( i != j ) scanf("%lld", &a[i][j]);
	REP(j, 1, n) REP(i, 1, j - 1) pre[i][j] = pre[i - 1][j] + a[i][j];
	REP(i, 1, n) REP(j, 1, i - 1) suf[i][j] = suf[i][j - 1] + a[i][j];
	REP(i, 0, n) REP(j, 0, n) REP(k, 0, n) f[i][j][k] = INF;
	f[1][0][0] = 0;
	REP(i, 2, n) REP(l, 0, i - 2) REP(r, l, i - 2) if ( f[i - 1][l][r] < INF ) 
	{
		int sum = (l > 0 ? suf[i][l - 1] : 0);
		f[i][r + 1][i - 1] = min(f[i][r + 1][i - 1], f[i - 1][l][r] + suf[i][r]);
		f[i][l][r] = min(f[i][l][r], f[i - 1][l][r] + sum + pre[i - 1][i] - pre[r][i]);
	}
	int ans = INF; REP(l, 0, n - 1) REP(r, l, n - 1) ans = min(ans, f[n][l][r]);
	printf("%lld\n", ans);
    return 0;
}
