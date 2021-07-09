/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月16日 星期四 08时32分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0x3f, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 5010;

int a[maxn][maxn], n, m, f[maxn][maxn], p[maxn][maxn];
int ans = 0x3f3f3f3f;

vector<int> path;

inline void get_path(int x, int y)
{
	if ( p[x][y] == 0 ) return ;
	get_path(x, p[x][y]);
	path.push_back(p[x][y]);
	get_path(p[x][y], y);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	mem(a); mem(f);
	REP(i, 1, m)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);	
		a[x][y] = a[y][x] = min(a[x][y], z);
		f[x][y] = f[y][x] = a[x][y];
		a[i][i] = f[i][i] = 0;
	}
	REP(k, 1, n)
	{
		REP(i, 1, k - 1)
			REP(j, i + 1, k - 1)
			{	
				if ( f[i][j] == 0x3f3f3f3f || a[j][k] == 0x3f3f3f3f || a[k][i] == 0x3f3f3f3f ) continue ;
				if ( ans > f[i][j] + a[j][k] + a[k][i] )
				{
					ans = f[i][j] + a[j][k] + a[k][i];
					path.clear();
					path.push_back(i);
					get_path(i, j);
					path.push_back(j);
					path.push_back(k);
				}
			}
		REP(i, 1, n)
			REP(j, 1, n)
			{
				if ( f[i][k] == 0x3f3f3f3f || f[k][j] == 0x3f3f3f3f ) continue ;
				if ( f[i][j] > f[i][k] + f[k][j] )
				{
					f[i][j] = f[i][k] + f[k][j];
					p[i][j] = k;
				}
			}
	}
	if ( ans == 0x3f3f3f3f ) { printf("No solution.\n"); return 0; }
	REP(i, 0, path.size() - 1) printf("%d ", path[i]);	
	puts("");
    return 0;
}
