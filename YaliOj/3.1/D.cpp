/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月15日 星期三 09时05分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10000010;

struct node
{
	int s, t, w;
} a[maxn];

int n, sum, f[maxn], cnt[maxn];
unsigned long long ans;

inline int cmp(node a, node b)
{
	return a.w < b.w;
}

inline int cha(int x)
{
	return x == f[x] ? x : f[x] = cha(f[x]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n - 1) { scanf("%d%d%d", &a[i].s, &a[i].t, &a[i].w); ans += a[i].w; }
	sort ( a + 1, a + n, cmp );
	REP(i, 1, n) f[i] = i, cnt[i] = 1;
	REP(i, 1, n - 1)
	{
		int x = a[i].s, y = a[i].t;
		int fx = cha(x), fy = cha(y);
		if ( fx != fy ) 
		{
			f[fx] = fy;
			ans += (unsigned long long)(cnt[fx] * cnt[fy] - 1) * (a[i].w + 1);
			cnt[fy] += cnt[fx];
		}
	}
	printf("%llu\n", ans);
	return 0;
}
