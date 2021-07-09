/***************************************************************
	File name: P1457.cpp
	Author: ljfcnyali
	Create time: 2019年05月07日 星期二 09时19分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 110;

int map[maxn][maxn][4], dt[4][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}}, n, m, sum;
bool vis[maxn][maxn];

inline void DFS(int x, int y)
{
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n)
		REP(j, 1, m)
		{
			int x; scanf("%d", &x);
			if ( x % 2 == 1 ) 
			{
				map[i][j][0] = 1;
				x -= 1;
			}
			if ( x % 4 == 2 )
			{
				map[i][j][2] = 1;
				x -= 2;
			}
			if ( x % 8 == 4 ) 
			{
				map[i][j][3] = 1;
				x -= 4;
			}
			if ( x % 16 == 8 )
			{
				map[i][j][1] = 1;
				x -= 8;
			}
		}
	REP(i, 1, n)
		REP(j, 1, n)
		{
			if ( vis[i][j] == true ) continue ;
			sum = 1;
			DFS(i, j);
		}
    return 0;
}
