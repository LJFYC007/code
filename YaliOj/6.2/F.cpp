/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年05月26日 星期日 11时00分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int prime[maxn], sum, n, v[maxn], num[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int Max = maxn - 10;
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
	REP(i, 2, n)
	{
		int x = i;
		while ( v[x] != x && x != 1 )
		{
			num[v[x]] ++;
			x /= v[x];
		}
		if ( x != 1 ) num[x] ++;
	}
//	REP(i, 2, n) printf("%d ", num[i]);
	long long ans = 1;	
	REP(i, 2, n) ans = (ans * (num[i] * 2 + 1)) % 1000000007;
	printf("%lld\n", ans);
    return 0;
}
