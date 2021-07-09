// luogu-judger-enable-o2
/***************************************************************
	File name: P1214.cpp
	Author: ljfcnyali
	Create time: 2019年05月06日 星期一 11时23分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int n, m, a[1000010], sum, ans, k;
bool vis[1000010];

struct node
{
	int x, y;
}f[50010];

inline int cmp(node a, node b)
{
	return a.y == b.y ? a.x < b.x : a.y < b.y;
}

inline bool find(int l, int r, int x)
{
	while ( l <= r ) 
	{
		int Mid = (l + r) / 2;
		if ( x == a[Mid] ) return true;
		if ( x < a[Mid] ) r = Mid - 1;
		else l = Mid + 1;
	}
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 0, m) REP(j, 0, m) { a[++ sum] = i * i + j * j; vis[a[sum]] = true; }
	sort ( a + 1, a + sum + 1 );	
	REP(i, 1, sum - 1) if ( a[i] == a[i + 1] ) { a[i] = -1; ++ k; }
	sort ( a + 1, a + sum + 1 );
	REP(i, k + 1, sum - 1)
		REP(j, i + 1, sum)
		{
			int cha = a[j] - a[i], p = a[j];
			bool flag = true;
			REP(o, 3, n)
			{
				p += cha;
				if ( vis[p] == false ) { flag = false ; break ; }
			}
			if ( flag == true ) { f[++ ans].x = a[i]; f[ans].y = cha; }
		}
	if ( ans == 0 ) { printf("NONE\n"); return 0 ; }
	sort ( f + 1, f + ans + 1, cmp );
	REP(i, 1, ans ) printf("%d %d\n", f[i].x, f[i].y);
    return 0;
}
