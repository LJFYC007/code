/***************************************************************
	File name: 3.cpp
	Author: ljfcnyali
	Create time: 2019年06月02日 星期日 08时45分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 520;

int a[maxn][maxn][9], b[maxn][maxn][9], n, m, k;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &k);
	REP(i, 1, n) REP(j, 1, n) { scanf("%d", &a[i][j][0]); b[i][j][0] = a[i][j][0]; }
	REP(o, 1, n)
		REP(j, 1, 8)
			REP(i, 1, n)
			{
				a[o][i][j] = max(a[o][i][j - 1], a[o][i + (1 << (j - 1))][j - 1]);
				b[o][i][j] = min(b[o][i][j - 1], b[o][i + (1 << (j - 1))][j - 1]);
			}
	REP(i, 1, k)
	{
		int x, y; scanf("%d%d", &x, &y);
		int Max = 0, Min = 2147483647;
		REP(o, x, x + m - 1)
		{
			int l = y, r = y + m - 1;
			for ( int j = 8; j >= 0; -- j )
			{
				if ( l + (1 << j) - 1 > r ) continue ;
				Max = max(Max, a[o][l][j]); Min = min(Min, b[o][l][j]);
				l += (1 << j);
			}
		}
		printf("%d\n", Max - Min);
	}
    return 0;
}
