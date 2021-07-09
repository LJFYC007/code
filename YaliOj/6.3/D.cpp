/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月27日 星期一 08时40分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1500010;
typedef long long LL;

LL x, prime[maxn], sum, v[maxn], num[maxn], p[maxn];

inline int js(LL x)
{
	return p[x];
	int ans = 1;
	REP(i, 2, x) ans *= i;
	return ans;
}

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
	p[1] = 1; REP(i, 2, 40) p[i] = p[i - 1] * i;
	while ( ~scanf("%lld", &x) ) 
	{
		LL sum = 1, ans = 0;
		for ( LL i = 2; i * i <= x; ++ i ) 
			if ( x % i == 0 )
			{
				LL cnt = 0;
				while ( x % i == 0 )
				{
					x /= i; ++ cnt; ++ ans;
				}
				sum *= p[cnt];
			}
		if ( x > 1 ) ++ ans;
		printf("%lld %lld\n", ans, p[ans] / sum);
	}
    return 0;
}
