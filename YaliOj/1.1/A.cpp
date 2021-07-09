/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月07日 星期二 09时43分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1010;

struct node
{
	int s, t;
} a[maxn];

int n, ans;

inline int cmp(node a, node b)
{
	return a.t < b.t || (a.t == b.t && a.s < b.s); 
}

inline void DFS(int x)
{
	if ( x <= 0 ) return ;
	int Max = 0;
	REP(i, 1, n) 
	{
		if ( a[i].t > x ) break ; 
		Max = max(Max, a[i].s);
	}
	if ( Max == 0 ) return ;
//	printf("%d %d\n", Max, x);
	++ ans;
	DFS(Max);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) scanf("%d%d", &a[i].s, &a[i].t);
	sort ( a + 1, a + n + 1, cmp );
	DFS(0x3f3f3f3f);	
	printf("%d\n", ans);
    return 0;
}
