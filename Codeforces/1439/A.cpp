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
typedef long long LL;

const int maxn = 110;

int T, n, m, ans, p[maxn][maxn], a[maxn][maxn];
pii belong[maxn][maxn];
char s[maxn][maxn], t[maxn][maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- )
	{
		scanf("%d%d", &n, &m);
		REP(i, 1, n) scanf("%s", s[i] + 1);
		REP(i, 1, n) REP(j, 1, m) { p[i][j] = 0; a[i][j] = s[i][j] - '0'; }
		int ans = 0;
		for ( int i = 1; i <= n; i += 2 ) for ( int j = 1; j <= m; j += 2 )
		{
			belong[i][j] = pii(i + 1, j + 1);
			belong[i + 1][j] = pii(i, j + 1);
			belong[i][j + 1] = pii(i + 1, j);
			belong[i + 1][j + 1] = pii(i, j);
		}
		ans = 0;
		if ( n % 2 == 1 && m % 2 == 1 && a[n][m] ) { ++ ans; a[n][m] ^= 1; a[n - 1][m] ^= 1; a[n][m - 1] ^= 1; }
		if ( m % 2 == 1 ) REP(i, 1, n) if ( s[i][m] == '1' ) { ++ ans; a[i][m] ^= 1; a[
		int N = n % 2 == 1 ? n - 1 : n;
		int M = m % 2 == 1 ? m - 1 : m;
		REP(i, 1, N) REP(j, 1, M)
		{
			int x = belong[i][j].first, y = belong[i][j].second;
			if ( s[i][j] == '1') { p[i][j] ^= 1; p[i][y] ^= 1; p[x][j] ^= 1; }
		}
	}
    return 0;
}
