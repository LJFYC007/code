/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月29日 星期三 08时31分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 500010;

int a[maxn][20], n, m;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n) scanf("%d", &a[i][0]);
	REP(j, 1, 17)
		REP(i, 1, n)
			a[i][j] = max(a[i][j - 1], a[i + (1 << (j - 1))][j - 1]);
	REP(i, 1, m)
	{
		int l, r, Max = 0; scanf("%d%d", &l, &r);
		for ( int j = 17; j >= 0; -- j )
		{
			if ( l + (1 << j) - 1 > r ) continue ;
			Max = max(Max, a[l][j]);	
			l += (1 << j);
		}
		printf("%d\n", Max);
	}
    return 0;
}
