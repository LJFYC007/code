#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 1e5 + 10;

int n, t, a, b, c, p[5], q[5];
pii f[maxn]; bool flag;

inline void Move(int x, int y) { REP(i ,1, 4) q[i] -= abs(f[i].first - x) + abs(f[i].second - y); }

inline int calc(int l, int r) { return (l + r) * (r - l + 1) / 2; } 

inline void Move1(int l, int r, int x, int o)
{
	int len = r - l + 1;
	q[o] -= abs(f[o].second - x) * len;
	if ( r <= f[o].first ) q[o] -= f[o].first * len - calc(l, r);
	else if ( l >= f[o].first ) q[o] -= calc(l, r) - f[o].first * len;
	else q[o] -= f[o].first * (f[o].first - l + 1) - calc(l, f[o].first) + calc(f[o].first + 1, r) - f[o].first * (r - f[o].first);
}

inline void Move2(int l, int r, int x, int o)
{
	int len = r - l + 1;
	q[o] -= abs(f[o].first - x) * len;
	if ( r <= f[o].second ) q[o] -= f[o].second * len - calc(l, r);
	else if ( l >= f[o].second ) q[o] -= calc(l, r) - f[o].second * len;
	else q[o] -= f[o].second * (f[o].second - l + 1) - calc(l, f[o].second) + calc(f[o].second + 1, r) - f[o].second * (r - f[o].second);
}

inline bool Check(int x, int y)
{
	REP(i, 1, 4) q[i] = p[i]; 
	if ( x < a ) { REP(i, 1, 4) Move1(x + 1, a, y, i); x = a; } 
	if ( y < b ) { REP(i, 1, 4) Move2(y + 1, b, x, i); y = b; } 
	REP(i, 1, 4) if ( q[i] < 0 ) return false;
	if ( x <= a + c - 1 && y <= b + c - 1)
	{
		int sum = (a + c - 1 - x) * (b + c - 1 - y);
		REP(i, 1, 4) Move1(x + 1, a + c - 1, y, i); x = a + c - 1;
		REP(i, 1, 4) Move2(y + 1, b + c - 1, x, i); y = b + c - 1;
		int num = min(sum, (q[3] - q[2] - 2) / 4);
		q[3] -= num * 2; q[2] += num * 2;
		// while ( sum && q[3] > q[2] + 1 ) { -- sum; q[3] -= 2; q[2] += 2; } 
		REP(i, 1, 4) if ( q[i] < 0 ) return false;
	}
	REP(i, 1, 4) Move2(y + 1, n, x, i); y = n;
	REP(i, 1, 4) Move1(x + 1, n, y, i); x = n;
	REP(i, 1, 4) if ( q[i] < 0 ) return false;
	return true;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("elis.in", "r", stdin);
	freopen("elis.out", "w", stdout);
#endif
	scanf("%lld%lld%lld%lld%lld", &n, &t, &a, &b, &c);
	p[1] = p[2] = p[3] = p[4] = t;
    f[1] = pii(a, b); f[2] = pii(a, b + c - 1); f[3] = pii(a + c - 1, b); f[4] = pii(a + c - 1, b + c - 1);
	if ( !Check(1, 1) ) { puts("Again"); return 0; } 
	int x = 1, y = 1;
	while ( x != n || y != n )
	{
		if ( x < n )
		{
			++ x; REP(i, 1, 4) p[i] -= abs(f[i].first - x) + abs(f[i].second - y); 
			if ( Check(x, y) ) { putchar('R'); continue ; } 
			REP(i, 1, 4) p[i] += abs(f[i].first - x) + abs(f[i].second - y); -- x;
		}
		++ y; REP(i, 1, 4) p[i] -= abs(f[i].first - x) + abs(f[i].second - y); putchar('U'); 
	}
	return 0;
}
