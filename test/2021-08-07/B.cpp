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

const int maxn = 1e5 + 10;

int T, n, a[11][11], ans;
char s[11];
bool vis[11][11];

inline void DFS(int x, int y, int num)
{
	if ( x == n && y == n ) 
	{
		vis[x][y] = false;
		++ num; ans = max(ans, num);
		DFS(1, 1, num);
		return ;
	}
	if ( a[x + 1][y] && !vis[x + 1][y] ) { vis[x + 1][y] = true; DFS(x + 1, y, num); vis[x + 1][y] = false; } 
	if ( a[x][y + 1] && !vis[x][y + 1] ) { vis[x][y + 1] = true; DFS(x, y + 1, num); vis[x][y + 1] = false; } 
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		mem(a);
		scanf("%d", &n);
		REP(i, 1, n)
		{
			scanf("%s", s + 1);
			REP(j, 1, n) a[i][j] = s[j] == '.';
		}
		ans = 0;
		if ( a[1][1] == 0 || a[n][n] == 0 ) { puts("0"); continue ; } 
		DFS(1, 1, 0);
		printf("%d\n", ans);
	}
    return 0;
}
