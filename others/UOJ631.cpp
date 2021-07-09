/***************************************************************
	File name: UOJ631.cpp
	Author: ljfcnyali
	Create time: 2021年05月30日 星期日 09时32分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;
const int Delta = 5e8;

int n, m, B, t1, t2, f[maxn][maxn], g[maxn][maxn]; 
struct node { int op, a, b; } ; vector<node> ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("dispatch.in", "r", stdin);
    freopen("dispatch.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m); B = sqrt(n); 
	printf("%d\n", n); t1 = t2 = Delta;
	printf("1 1\n"); 

	int now = 0, x = 1, y = 2;
	REP(i, 2, n) if ( now == 1 ) 
	{
		f[x][y] = ++ t1;
		if ( i > n - m ) ans.push_back({now, f[x][y], y});
		++ y; if ( y == x + 1 ) { now = 0; x = 1; }
	}
	else
	{
		g[x][y] = ++ t2;
		if ( i > n - m ) ans.push_back({now, g[x][y], x});
		++ x; if ( x == y ) { now = 1; y = 1; }
	}

	now = 0; x = 1; y = 2;
	REP(i, 2, n)
	{
		if ( i <= n - m - 1 ) printf("%d %d\n", x, y);
		else if ( now == 0 ) printf("%d %d\n", g[x][y], y);
		else printf("%d %d\n", x, f[x][y]);
		if ( now == 0 ) { ++ x; if ( x == y ) { now = 1; y = 1; } }
		else { ++ y; if ( y == x + 1 ) { now = 0; x = 1; } }
	}

	printf("%zu\n", ans.size());
	for ( auto it : ans ) printf("%d %d %d\n", it.op, it.a, it.b);
    return 0;
}
