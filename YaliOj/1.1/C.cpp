/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月07日 星期二 10时23分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 15010;
const double eps = 0.000000001;

int T, n, l, w, ans, last, cnt;
bool flag;

struct node
{
	double s, t;
}a[maxn];

inline int cmp(node a, node b) 
{
	return a.s < b.s || (a.s == b.s && a.t < b.t);
}

inline void DFS(double x)
{
	++ cnt; if ( cnt >= 0x3f3f3f3f ) return ;
	if ( x >= l ) { printf("%d\n", ans); flag = true; return ; }
	double Max = 0;
	REP(i, 1, n) if ( a[i].s <= x ) Max = max(Max, a[i].t); 
	if ( Max < x ) return ;
	++ ans; DFS(Max + eps);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d%d%d", &n, &l, &w); ans = 0; cnt = 0;
		flag = false;
		REP(i, 1, n) 
		{ 
			int x, y; scanf("%d%d", &x, &y); 
			if ( y * 2 < w ) { a[i].s = a[i].t = -1; continue ; }
			a[i].s = x - sqrt(y * y - w * w / 4.0);
			a[i].t = x + sqrt(y * y - w * w / 4.0);
		}
		sort ( a + 1, a + n + 1, cmp ) ;
		REP(i, 1, n) if ( a[i].s == -1 ) last = i + 1;
		//REP(i, 1, n) printf("%lf %lf\n", a[i].s, a[i].t);
		DFS(0);
		if ( flag == false ) printf("-1\n");
	}
    return 0;
}
