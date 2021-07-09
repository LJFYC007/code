/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月15日 星期三 08时42分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int n, sum, f[maxn];
struct node
{
	int s, t, w;
} a[maxn];

inline int cmp(node a, node b)
{
	return a.w < b.w;
}

inline int cha(int x)
{
	return x == f[x] ? f[x] : f[x] = cha(f[x]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) { int x; scanf("%d", &x); a[++ sum].s = 0; a[sum].t = i; a[sum].w = x; }
	REP(i, 1, n)
		REP(j, 1, n)
		{
			if ( i == j ) { int x; scanf("%d", &x); continue ; }
			scanf("%d" , &a[++ sum].w);
			a[sum].s = i; a[sum].t = j;
		}
	sort ( a + 1, a + sum + 1, cmp );
	REP(i, 0, n) f[i] = i;
	int cnt = 0, ans = 0;
	REP(i, 1, sum)
	{
		int x = a[i].s, y = a[i].t;
		int fx = cha(x), fy = cha(y);
		if ( fx != fy ) 
		{
			f[fx] = fy;
			ans += a[i].w;
//			printf("%d ", a[i].w);
			++ cnt;
		}
		if ( cnt == n ) break ; 	
	}
	printf("%d\n", ans);
    return 0;
}
