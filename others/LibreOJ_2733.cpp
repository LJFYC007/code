/***************************************************************
	File name: LibreOJ_2733.cpp
	Author: ljfcnyali
	Create time: 2021年07月14日 星期三 10时33分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 510;
const int INF = 0x3f3f3f3f;

int n, m, a[maxn][maxn], ret, ans[maxn][maxn];
char s[maxn]; bool vis[maxn][maxn], use[maxn][maxn];

inline void DFS(int x, int y, int op)
{
	if ( use[x][y] ) ret = INF;
	if ( x < 1 || x > n || y < 1 || y > m || vis[x][y] ) return ;
	vis[x][y] = true; ++ ret; use[x][y] = true;
	if ( op == 0 ) DFS(x - 1, y, 0); else DFS(x + 1, y, 1);
	if ( op == a[x][y] ) DFS(x, y + 1, a[x][y + 1]);
	else DFS(x, y - 1, a[x][y - 1] ^ 1);
	use[x][y] = false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n)
	{
		scanf("%s", s + 1);
		REP(j, 1, m) a[i][j] = (s[j] == 'Z');
	}
	REP(i, 1, n) REP(j, 1, m) ans[i][j] = INF;
	REP(i, 1, n) 
	{
		ret = 0; mem(vis);
		REP(j, 1, m)
		{
			DFS(i, j, a[i][j] ^ 1); 
			ans[i][j] = min(ans[i][j], ret);
		}
	}
	REP(i, 1, n) 
	{
		ret = 0; mem(vis);
		for ( int j = m; j >= 1; -- j ) 
		{
			DFS(i, j, a[i][j]); 
			ans[i][j] = min(ans[i][j], ret);
		}
	}
	REP(i, 1, n) { REP(j, 1, m) printf("%d ", ans[i][j] == INF ? -1 : ans[i][j] * 2); puts(""); }
    return 0;
}
