/***************************************************************
	File name: I.cpp
	Author: ljfcnyali
	Create time: 2019年05月07日 星期二 13时02分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int m, n, v[maxn], p[maxn];

struct node
{
	int a, b;
} a[maxn];

inline int cmp(node a, node b) 
{
	return a.b > b.b || (a.b == b.b && a.a < b.a) ;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) { scanf("%d%d", &a[i].a, &a[i].b); m += a[i].b; }
	sort ( a + 1, a + n + 1, cmp ) ;
	REP(i, 1, n)
	{
		int k = a[i].a;
		while ( v[k] == 1 )
		{
			if ( p[k] == 1 ) { k = 0; break ; }
			-- k;
		}
		if ( k < 1 ) { p[a[i].a] = 1; m -= a[i].b; continue ; }
		v[k] = 1;
	}
	printf("%d\n", m);
    return 0;
}
