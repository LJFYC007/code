/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月26日 星期日 09时13分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int prime[maxn], n, sum, v[maxn], Max = maxn - 10;

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
	while ( ~scanf("%d", &n) )
	{
		if ( n == 0 ) return 0;
		REP(i, 1, sum) 
			if ( v[n - prime[i]] == (n - prime[i]) ) 
			{ 
				printf("%d = %d + %d\n", n, prime[i], n - prime[i]);
				goto finish; 
			}
		printf("Goldbach's conjecture is wrong.\n"); 
finish: ;
	}
    return 0;
}
