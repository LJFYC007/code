/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年07月17日 星期六 10时06分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, q, a[maxn];
struct node { int op, l, r, x, y; } Q[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("ansput.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &q);
	bool flag = true;
	REP(i, 1, m)
	{
		scanf("%d", &Q[i].op);
		if ( Q[i].op == 1 ) scanf("%d%d", &Q[i].x, &Q[i].y);
		if ( Q[i].op == 2 ) scanf("%d%d%d", &Q[i].l, &Q[i].r, &Q[i].x);
		if ( Q[i].op == 2 ) flag = false;
		if ( Q[i].op == 3 ) scanf("%d", &Q[i].x);
	}

	if ( flag ) 
	{
		REP(i, 1, q) puts("0");
		return 0;
	}

	while ( q -- ) 
	{
		int l, r; scanf("%d%d", &l, &r); 
		REP(i, 1, n) a[i] = 0;
		LL ans = 0;
		REP(o, l, r)
		{
			if ( Q[o].op == 1 ) swap(a[Q[o].x], a[Q[o].y]);
			if ( Q[o].op == 2 ) REP(j, Q[o].l, Q[o].r) a[j] = Q[o].x;
			if ( Q[o].op == 3 ) ans += a[Q[o].x];
		}
		printf("%lld\n", ans);
	}
    return 0;
}
