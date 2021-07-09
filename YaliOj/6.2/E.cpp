/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年05月26日 星期日 09时34分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int prime[maxn], sum, n, v[maxn], Max = maxn - 10;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	REP(i, 2, Max)
	{
		if ( !v[i] ) 
		{
			prime[++ sum] = i; v[i] = i;
		}
		REP(j, 1, sum)
		{
			if ( prime[j] > i || prime[j] * i > Max ) break ;
			v[prime[j] * i] = prime[j];
		}
	}
	scanf("%d", &n);
	if ( n == 1 || n == 2 ) 
	{
		printf("1\n");
		REP(i, 1, n) printf("1 "); puts("");
		return 0;
	}
	printf("2\n");
	REP(i, 2, n + 1)	
	{
		if ( v[i] == i ) printf("1 ");
		else printf("2 ");
	}
	puts("");
    return 0;
}
