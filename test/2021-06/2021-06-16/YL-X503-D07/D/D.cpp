/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2021年06月16日 星期三 10时20分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 251;

int n; double p[5], f[maxn][maxn][maxn], g[maxn][maxn], h[maxn][maxn], a[maxn];

int main()
{
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
	scanf("%d", &n); REP(i, 1, 4) { scanf("%lf", &p[i]); p[i] /= 100; }
	f[0][0][0] = g[0][0] = h[0][0] = a[0] = 1;
	REP(m, 1, n)
	{
		// a
		double Max1 = 0, Max2 = 0;
		REP(i, 1, m) 
		{
			Max1 = max(Max1, g[i - 1][m - i]);
			Max2 = max(Max2, h[i - 1][m - i]);
		}
		a[m] = a[m - 1] * (p[1] + p[4]) + Max1 * p[2] + Max2 * p[3];
	
		// g
		REP(x, 0, m)
		{
			int y = m - x;
			if ( x >= 1 ) g[x][y] += p[1] * g[x - 1][y];
			if ( y >= 1 ) g[x][y] += p[4] * g[x][y - 1];
			g[x][y] += p[2] * max(x >= 1 ? g[x - 1][y] : 0, y >= 1 ? g[x][y - 1] : 0);
			double Max = 0; REP(i, 1, y) Max = max(Max, f[x][i - 1][y - i]);
			g[x][y] += p[3] * Max;
		}

		// h
		REP(x, 0, m)
		{
			int y = m - x;
			if ( x >= 1 ) h[x][y] += p[1] * h[x - 1][y];
			if ( y >= 1 ) h[x][y] += p[4] * h[x][y - 1];
			h[x][y] += p[3] * max(x >= 1 ? h[x - 1][y] : 0, y >= 1 ? h[x][y - 1] : 0);
			double Max = 0; REP(i, 1, x) Max = max(Max, f[i - 1][x - i][y]);
			h[x][y] += p[2] * Max;
		}
		
		// f
		REP(x, 0, m) REP(y, 0, m - x)
		{
			int z = m - x - y;
			if ( x >= 1 ) f[x][y][z] += p[1] * f[x - 1][y][z];
			if ( z >= 1 ) f[x][y][z] += p[4] * f[x][y][z - 1];
			f[x][y][z] += p[2] * max(x >= 1 ? f[x - 1][y][z] : 0, y >= 1 ? f[x][y - 1][z] : 0);
			f[x][y][z] += p[3] * max(y >= 1 ? f[x][y - 1][z] : 0, z >= 1 ? f[x][y][z - 1] : 0);
		}
	}
	printf("%.6lf\n", a[n]);
    return 0;
}
