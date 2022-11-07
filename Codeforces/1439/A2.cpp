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

int T, n, m, ans;
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
		ans = 0;
		REP(i, 1, n) { scanf("%s", s[i] + 1); REP(j, 1, m) t[i][j] = s[i][j]; }
		REP(i, 1, n) REP(j, 1, m)
		{
			if ( i < n && s[i][j] == '1' && s[i + 1][j] == '1' )
			{
				if ( j > 1 && s[i + 1][j - 1] == '1' )
				{
					++ ans; s[i][j] = s[i + 1][j] = s[i + 1][j - 1] = '0';
					continue ;
				}
				if ( j < m && s[i + 1][j + 1] == '1' )
				{
					++ ans; s[i][j] = s[i + 1][j] = s[i + 1][j + 1] = '0';
					continue ;
				}
			}
		}
		REP(i, 1, n) REP(j, 1, m)
		{
			if ( i < n && s[i][j] == '1' && s[i + 1][j] == '1' ) { ans += 2; s[i][j] = s[i + 1][j] = '0'; continue ; }
			if ( j < m && s[i][j] == '1' && s[i][j + 1] == '1' ) { ans += 2; s[i][j] = s[i][j + 1] = '0'; continue ; }
		}
		REP(i, 1, n) REP(j, 1, m) if ( s[i][j] == '1' ) ans += 3;
		printf("%d\n", ans);
	}
    return 0;
}
