/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月08日 星期三 11时18分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int a[maxn], n, m, ans = 1000000000;

inline bool check(int x)
{
	int sum = 1, num = 0;
	REP(i, 1, n)
	{
		num += a[i];
		if ( num > x )
		{
			num = a[i]; ++ sum;
		}
		if ( sum > m ) return false;
	}
	if ( sum > m ) return false;
	return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	int L = 0, R = 0;
	REP(i, 1, n) 
	{
		scanf("%d", &a[i]);
		R += a[i];
		L = max(L, a[i]);
	}
	L = max(R / m, L); 
	while ( L <= R ) 
	{
//		printf("%d %d\n", L, R);
		int Mid = (L + R) / 2;
		if ( check(Mid) )
		{
			ans = min(ans, Mid);
			R = Mid - 1;
		}
		else L = Mid + 1;
	}
	printf("%d\n", ans);
    return 0;
}
