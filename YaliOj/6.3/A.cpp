/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月26日 星期日 11时19分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

LL a[11] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29}, ans, n, ans1 = 2147483647;

inline void DFS(LL x, LL sum, LL last, LL num)
{
//	printf("%d %d %d %d\n", a[x], sum, last, num);
	if ( x == 11 ) return ;
	LL s = 1;
	REP(i, 1, last)
	{
		sum *= a[x]; ++ s;
		if ( sum > n ) return ;
		if ( num * s == ans ) ans1 = min(ans1, sum);
		else if ( num * s > ans ) { ans = num * s; ans1 = sum; }
		DFS(x + 1, sum, i, num * s);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	DFS(1, 1, 31, 1);
	printf("%lld\n", ans1);
    return 0;
}
