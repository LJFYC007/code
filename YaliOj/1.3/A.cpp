/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月09日 星期四 15时11分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int n, k, a[210], ans;

inline void DFS(int x, int sum)
{
	if ( x == k + 1 )
	{
		if ( sum == n ) ++ ans;
		return ;
	}
	if ( sum >= n ) return ;
	REP(i, a[x - 1], n)
	{
		if ( i * (k - x + 1) + sum > n ) return ;
		a[x] = i;
		DFS(x + 1, sum + i);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	a[0] = 1;
	DFS(1, 0);
	printf("%d\n", ans);
    return 0;
}
