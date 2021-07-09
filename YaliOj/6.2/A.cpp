/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月25日 星期六 16时00分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;

LL prime[maxn], L, R, sum, n, v[maxn], Min, Max, ans1, ans2, ans3, ans4, ans[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	REP(i, 2, 46430)
	{
		if ( !v[i] ) 
		{
			prime[++ n] = i;
			v[i] = i;
		}
		REP(j, 1, n)
		{
			if ( prime[j] > i || prime[j] * i > 46430 ) break ; 
			v[i * prime[j]] = prime[j];
		}
	}	
	while ( cin >> L >> R )
	{
		Min = R + 1; Max = 0; mem(v); mem(ans); sum = 0;
		if ( L == 1 ) v[1] = 1;
		REP(i, 1, n)
			REP(j, L / prime[i], R / prime[i])
			{
				if ( j == 0 || j == 1 ) continue ; 
				v[prime[i] * j - L + 1] = 1;
//				printf("%d %d\n", j, prime[i]);
			}
		REP(i, 1, R - L + 1)
			if ( !v[i] ) ans[++ sum] = i + L - 1;
//		REP(i, 1, sum) printf("%d ", ans[i]); puts("");
		REP(i, 2, sum) 
		{
			LL x = ans[i] - ans[i - 1];
			if ( x < Min ) 
			{
				Min = x; ans1 = ans[i - 1]; ans2 = ans[i];
			}
			if ( x > Max ) 
			{
				Max = x; ans3 = ans[i - 1]; ans4 = ans[i];
			}
		}
		if ( Min == R + 1 ) printf("There are no adjacent primes.\n"); 
		else printf("%lld,%lld are closest, %lld,%lld are most distant.\n", ans1, ans2, ans3, ans4);
	}
    return 0;
}
