/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年05月29日 星期三 08时23分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 5050;

long long c[maxn][maxn], n, m;

inline int lowbit(int x) { return x & (-x); }

inline void add(int x, int y, int val)
{
	for ( int i = x; i <= n; i += lowbit(i) )
		for ( int j = y; j <= m; j += lowbit(j) )
			c[i][j] += val;
}

inline long long getsum(int x, int y)
{
	long long sum = 0;
	for ( int i = x; i >= 1; i -= lowbit(i) ) 
		for ( int j = y; j >= 1; j -= lowbit(j) )
			sum += c[i][j];
	return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	int k, x, y, val;
	while ( ~scanf("%d", &k) )
	{
		scanf("%d%d", &x, &y);
		if ( k == 1 )
		{
			scanf("%d", &val);
			add(x, y, val);
		}
		else 
		{
			int a, b; scanf("%d%d", &a, &b);
			long long sum = getsum(a, b) + getsum(x - 1, y - 1);
//			printf("%d\n", sum);
			sum = sum - getsum(a, y - 1) - getsum(x - 1, b);
			printf("%lld\n", sum);
		}
	}
    return 0;
}
