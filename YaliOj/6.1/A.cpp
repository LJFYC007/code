/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月25日 星期六 10时03分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int Mod = 200907;

int t, a, b, c, k;

inline long long js(long long a, long long b)
{
	long long r = 1;
	while ( b ) 
	{
		if ( b & 1 ) { -- b; r *= a; }
		a *= a; b >>= 1;
		r %= Mod; a %= Mod;
	}
	return r;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &t);
	while ( t -- ) 
	{
		scanf("%d%d%d", &a, &b, &c); scanf("%d", &k);
		if ( (b - a) == (c - b) ) 
		{
			unsigned long long ans = a, d = (k - 1) % Mod, e = b - a;
			ans = (ans + (d * e % Mod)) % Mod;
			printf("%llu\n", ans);
			continue ;
		}
		int d = (c - b) / (b - a);		
		long long ans = js(d, k - 1);
		printf("%lld\n", (a * ans) % Mod);
	}
    return 0;
}
