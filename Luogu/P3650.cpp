/***************************************************************
	File name: P3650.cpp
	Author: ljfcnyali
	Create time: 2019年05月06日 星期一 10时40分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int a[1010], n, ans = 0x3f3f3f3f, sum;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 0, 100)
	{
		sum = 0;
		REP(j, 1, n)
		{
			if ( i <= a[j] && a[j] <= i + 17 ) continue ; 
			sum += min((i - a[j]) * (i - a[j]), (i + 17 - a[j]) * (i + 17 - a[j]));
		}
		ans = min(ans, sum);
	}
	printf("%d\n", ans);
    return 0;
}
