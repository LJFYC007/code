/***************************************************************
	File name: P2693.cpp
	Author: ljfcnyali
	Create time: 2019年05月06日 星期一 10时46分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 110;

int n, a[maxn][maxn][maxn], ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	int x, y, z; 
	scanf("%d %d %d", &x, &y, &z);
	REP(i, x - 2, x + 2)
	{
		REP(j, y - 2, y + 2)
		{
			REP(k, z - 2, z + 2)
			{
				int X = i, Y = j, Z = k;
				while ( X <= 0 ) X += n; while ( X > n ) X -= n;
				while ( Y <= 0 ) Y += n; while ( Y > n ) Y -= n;
				while ( Z <= 0 ) Z += n; while ( Z > n ) Z -= n;
				if ( a[X][Y][Z] == 0 ) { a[X][Y][Z] = 1; ++ ans; } 
			}
		}
	}
	scanf("%d %d %d", &x, &y, &z);
	REP(i, x - 2, x + 2)
	{
		REP(j, y - 2, y + 2)
		{
			REP(k, z - 2, z + 2)
			{
				int X = i, Y = j, Z = k;
				while ( X <= 0 ) X += n; while ( X > n ) X -= n;
				while ( Y <= 0 ) Y += n; while ( Y > n ) Y -= n;
				while ( Z <= 0 ) Z += n; while ( Z > n ) Z -= n;
				if ( a[X][Y][Z] == 0 ) { a[X][Y][Z] = 1; ++ ans; } 
			}
		}
	}
	printf("%d\n", ans);
    return 0;
}
