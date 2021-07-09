#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4010;
const int INF = 2e9;

int n, m, a[maxn], b[maxn], f[maxn][maxn], g[maxn][maxn], ans[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); m = n; n *= 2;
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, n) scanf("%d", &b[i]);
	REP(i, 0, n) REP(j, 0, n) f[i][j] = INF;
	f[0][0] = 0;
	REP(i, 1, n) REP(j, 0, i)
	{
		if ( j > 0 && f[i - 1][j - 1] <= a[i] && a[i] < f[i][j] ) { f[i][j] = a[i]; g[i][j] = 1; }
		if ( f[i - 1][j] <= b[i] && b[i] < f[i][j] ) { f[i][j] = b[i]; g[i][j] = 2; }
	}
	if ( f[n][m] == INF ) { puts("-1"); return 0; }
	for ( int x = n, y = m; x >= 1; -- x )
	{
		ans[x] = g[x][y];
		if ( g[x][y] == 1 ) -- y;
	}
	REP(i, 1, n) printf("%c", ans[i] == 1 ? 'A' : 'B'); puts("");
	return 0;
}
