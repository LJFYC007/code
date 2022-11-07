/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

int n, a[maxn][maxn], b[maxn][maxn], num;
struct node { int x, y, d; } p[maxn * maxn];
vector<node> ans1, ans2;

bool operator == (const node &a, const node &b) { return a.x == b.x && a.y == b.y && a.d == b.d; }

inline vector<node> Solve()
{
	vector<node> ans;
	node x = {1, 1, 0}; int m = 0;
	while ( 1 )
	{
		if ( x.x > n + n + 2 ) break ;
		if ( (x.d == 0 && x.x <= n && x.y <= n + 1) || (x.d == 1 && x.x <= n + 1 && x.y <= n) ) p[++ m] = x;
		if ( x.d == 1 && x.x == 1 ) { x.x = x.y + 1; x.y = 1; x.d = 0; }
		else if ( x.d == 0 ) x.d = 1;
		else { -- x.x; ++ x.y; x.d = 0; }
	}
	int now = 1;
	REP(i, 1, m)
	{
		x = p[i];
		if ( x.d == 0 && !b[x.x][x.y] ) continue ;
		if ( x.d == 1 && !a[x.x][x.y] ) continue ;
		if ( x == p[now] ) { ++ now; continue ; }

		++ now;
	}
	return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n + 1) REP(j, 1, n) { scanf("%d", &a[i][j]); num += a[i][j]; }
	REP(i, 1, n) REP(j, 1, n + 1) { scanf("%d", &b[i][j]); num += b[i][j]; }
	ans1 = Solve();
	REP(i, 1, n + 1) REP(j, 1, n) { scanf("%d", &a[i][j]); num -= a[i][j]; }
	REP(i, 1, n) REP(j, 1, n + 1) { scanf("%d", &b[i][j]); num -= b[i][j]; }
	ans2 = Solve();
	if ( num != 0 ) { puts("NO"); return 0; }
	puts("Yes");
	for ( int i = 0; i < ans1.size(); ++ i )
		printf("%d %d %d\n", ans1[i].x, ans1[i].y, ans1[i].d);
	for ( int i = 0; i < ans2.size(); ++ i )
		printf("%d %d %d\n", ans2[i].x, ans2[i].y, 1 ^ ans2[i].d);
    return 0;
}
