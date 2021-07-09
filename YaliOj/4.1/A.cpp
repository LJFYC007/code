/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月28日 星期二 15时01分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;

LL c[maxn], n, q;

inline LL lowbit(LL x) { return x & (-x); }

inline void Insert(LL x, LL val)
{
	for ( LL i = x; i <= n; i += lowbit(i) ) c[i] += val;
}

inline LL Get_Sum(LL x)
{
	LL sum = 0;
	for ( LL i = x; i >= 1; i -= lowbit(i) ) sum += c[i];
	return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &q);
	REP(i, 1, n) { LL x; scanf("%lld", &x); Insert(i, x); }
	REP(i, 1, q)
	{
		LL p, x, y; scanf("%lld%lld%lld", &p, &x, &y);
		if ( p == 1 ) Insert(x, y);
		else printf("%lld\n", Get_Sum(y) - Get_Sum(x - 1));
	}
    return 0;
}
