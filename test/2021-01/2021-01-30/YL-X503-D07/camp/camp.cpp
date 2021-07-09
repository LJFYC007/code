/***************************************************************
	File name: camp.cpp
	Author: ljfcnyali
	Create time: 2021年01月30日 星期六 11时35分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 20;

int a[maxn][maxn], tot;

inline void paint(int l, int r, int x, int y)
{
	REP(i, l, r) REP(j, i + 1, r) a[i][j] = y;
	a[l][l + 1] = a[l][l + 4] = a[l + 1][l + 3] = a[l + 2][l + 3] = a[l + 2][l + 4] = x;
	REP(i, l, r) REP(j, i + 1, r) a[j][i] = a[i][j];
}

inline void DFS(int x, int y)
{
	if ( x == 1 && y == 20 ) { ++ tot; cerr << tot << " " << x << " " << y << " " << a[x][y - 1] << endl; }
	if ( y == 26 )
	{
		if ( x < 5 ) DFS(x + 1, 6);
		else if ( x < 10 ) DFS(x + 1, 11);
		else if ( x < 15 ) DFS(x + 1, 16);
		else if ( x < 20 ) DFS(x + 1, 21);
		else 
		{
			REP(i, 1, 16) { REP(j, 1, 16) printf("%d ", a[i][j]); puts(""); }
			exit(0);
		}
		return ; 
	}
	REP(col, 1, 4)
	{
		REP(i, 1, 25) if ( i != x && i != y && a[i][x] == col && a[i][y] == col ) goto Next ;
		a[x][y] = a[y][x] = col;
		DFS(x, y + 1);
		a[x][y] = a[y][x] = 0;
Next : ;
	}
}

int main()
{
	paint(1, 5, 1, 2); 
	paint(6, 10, 2, 3);
	paint(11, 15, 3, 4);
	paint(16, 20, 1, 3);
	paint(21, 25, 2, 4);
	DFS(1, 6);
    return 0;
}
