/***************************************************************
	File name: P1216.cpp
	Author: ljfcnyali
	Create time: 2019年05月06日 星期一 15时02分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1010;

int n, a[maxn][maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) REP(j, 1, i) scanf("%d", &a[i][j]);
	for ( int i = n - 1; i >= 1; -- i )
		REP(j, 1, i)
			a[i][j] += max(a[i + 1][j], a[i + 1][j + 1]);
	printf("%d\n", a[1][1]);
    return 0;
}
