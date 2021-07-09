/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月30日 星期四 15时15分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;

LL c[maxn], n, m, f[maxn], a[maxn];

inline LL lowbit(LL x) { return x & -x; }

inline void add(LL x, LL val)
{
	for ( LL i = x; i <= n; i += lowbit(i) ) c[i] += val;
}

inline LL getsum(LL x)
{
	LL sum = 0;
	for ( LL i = x; i >= 1; i -= lowbit(i) ) sum += c[i];
	return sum;
}

inline LL cha(LL x)
{
	return x == f[x] ? f[x] : f[x] = cha(f[x]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n)
	{
		scanf("%lld", &a[i]); add(i, a[i]);
		f[i] = i;
	}
	f[n + 1] = n + 1;
	scanf("%lld", &m);
	REP(j, 1, m)
	{
		LL k, l, r; scanf("%lld%lld%lld", &k, &l, &r);
		if ( l > r ) swap(l, r);
		if ( k == 1 ) printf("%lld\n", getsum(r) - getsum(l - 1));
		else 
		{
			for ( int i = l; i <= r; i = cha(i) == i ? i + 1 : f[i] )
			{
				int t = sqrt(a[i]); add(i, t - a[i]); a[i] = t;
				f[i] = a[i] <= 1 ? i + 1 : i;
			}
		}
	}
    return 0;
}
