/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月26日 星期日 15时36分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int a0, a1, b0, b1, n;

inline int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1 ,n)
	{
		scanf("%d%d%d%d", &a0, &a1, &b0, &b1);
		int a = a0 / a1, b = b1 / b0, ans = 0;
		for ( int j = 1; j * j <= b1; ++ j )
			if ( b1 % j == 0 )
			{
				if ( j % a1 == 0 && gcd(j / a1, a) == 1 && gcd(b, b1 / j) == 1 ) ++ ans;
				int x = b1 / j;
				if ( x == j ) continue ;
				if ( x % a1 == 0 && gcd(x / a1, a) == 1 && gcd(b, b1 / x) == 1 ) ++ ans;
			}
		printf("%d\n", ans);
	}
    return 0;
}
