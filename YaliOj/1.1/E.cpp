/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年05月07日 星期二 11时24分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1010;

int m, n, v[maxn];

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
	scanf("%d%d", &m, &n);
	REP(i, 1, n) scanf("%d", &a[i].a);
	REP(i, 1, n) scanf("%d", &a[i].b);
	sort ( a + 1, a + n + 1, cmp ) ;
	REP(i, 1, n)
	{
		int k = a[i].a;
		while ( v[k] == 1 ) -- k;
		if ( k < 1 ) { m -= a[i].b; continue ; }
		v[k] = 1;
	}
	printf("%d\n", m);
    return 0;
}
