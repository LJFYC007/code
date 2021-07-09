/***************************************************************
	File name: P1444.cpp
	Author: ljfcnyali
	Create time: 2019年05月06日 星期一 08时33分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int n, d[15][3], ans;

int f[15][15], a[15][15];
bool use[15], flag, vis[15];

inline void dfs(int x)
{
	if ( flag == false ) return ;
//	printf("%d ", x);
	REP(i, 1, n)
	{
		if ( i == x ) continue ;
		if ( a[x][i] == 0 && f[x][i] == 0 ) continue ;
		if ( vis[i] == true ) { flag = false ; return ; }
		if ( f[x][i] == 0 ) a[i][x] = 0;
		vis[i] = true;
		dfs(i);
		vis[i] = false;
		if ( f[x][i] == 0 ) a[i][x] = 1;
	}
}

inline bool pd()
{
	flag = true;
//	REP(i, 1, n) { REP(j, 1, n) printf("%d ", f[i][j] + a[i][j]); puts(""); }
//	puts("");
	REP(i, 1, n)
	{
		mem(vis); vis[i] = true;
		dfs(i);
		if ( flag == false ) return false;
	}
	return true;
}

inline void DFS(int x)
{
//	printf("%d ", x);
//	REP(i, 1, n) printf("%d ", use[i]); puts("");
	if ( x == n + 1 )
	{
		if ( pd() == false ) ++ ans;
//		puts("");
		return ;
	}
	if ( use[x] ) { DFS(x + 1) ; return ; }
	use[x] = true;
	REP(i, 1, n)
	{
		if ( use[i] ) continue ;
		a[i][x] = a[x][i] = 1;
		use[i] = true;
//		printf("%d:: ", i);
		DFS(x + 1);
		use[i] = false;
		a[i][x] = a[x][i] = 0;
	}
	use[x] = false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) 
	{
		scanf("%d%d", &d[i][1], &d[i][2]);
		REP(j, 1, i - 1) if ( d[i][2] == d[j][2] ) 
		{
			if ( d[i][1] < d[j][1] ) f[i][j] = 2;
			else f[j][i] = 2;
		}
	}
	DFS(1);
	printf("%d\n", ans);
    return 0;
}
