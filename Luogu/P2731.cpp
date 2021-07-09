/***************************************************************
	File name: P2731.cpp
	Author: ljfcnyali
	Create time: 2019年05月09日 星期四 09时18分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2010;

int a[maxn][maxn], n, digree[maxn];
int Min = 0x3f3f3f3f, Max;
int ans[maxn], sum;

inline void DFS(int x)
{
	REP(i, Min, Max)
	{
		if ( a[x][i] ) 
		{
			a[x][i] --;
			a[i][x] --;
			DFS(i);
		}
	}
	ans[++ sum] = x;
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
		int u, v; scanf("%d%d", &u, &v);
		a[u][v] ++; a[v][u] ++;
		digree[u] ++; digree[v] ++;
		Max = max(Max, max(u, v));
		Min = min(Min, min(u, v));
	}
	int s = Min;
	REP(i, Min, Max) if ( digree[i] % 2 == 1 ) { s = i; break ; }
	DFS(s);
	for ( int i = sum; i >= 1; -- i ) printf("%d\n", ans[i]);
    return 0;
}
