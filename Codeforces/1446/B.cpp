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

const int maxn = 5010;

int f[maxn][maxn], n, m, nex[2][maxn][26], ans;
char s[2][maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	scanf("%s", s[0] + 1); scanf("%s", s[1] + 1);
	/*
	REP(i, 0, 25) nex[0][n][i] = n + 1;
	for ( int i = n - 1; i >= 0; -- i )
	{
		REP(j, 0, 25) nex[0][i][j] = nex[0][i + 1][j];
		nex[0][i][s[0][i + 1] - 'a'] = i + 1;
	}
	REP(i, 0, 25) nex[1][m][i] = m + 1;
	for ( int i = m - 1; i >= 0; -- i )
	{
		REP(j, 0, 25) nex[1][i][j] = nex[1][i + 1][j];
		nex[1][i][s[1][i + 1] - 'a'] = i + 1;
	}
	*/
	REP(i, 1, n) REP(j, 1, m)
	{
		f[i][j] = max(f[i][j], f[i - 1][j - 1] - 2);
		f[i][j] = max(f[i][j], f[i][j - 1] - 1);
		f[i][j] = max(f[i][j], f[i - 1][j] - 1);
		if ( s[0][i] == s[1][j] ) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 2);
		ans = max(ans, f[i][j]);
	}
	printf("%d\n", ans);
    return 0;
}
