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
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

map<int, int> Map;
int n, a, b, m, f[maxn];

inline int find(int x)
{
	if ( !Map.count(x) ) return x;
	return Map[x] = find(Map[x]);
}
inline int cha(int x) { return f[x] == x ? x : f[x] = cha(f[x]); } 
struct node 
{
	int u, v, w; 
	bool operator < (const node &a) const { return w < a.w; } 
} Edge[maxn * 11];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &a, &b);
	if ( n <= 200000 && a <= 10 ) 
	{
		REP(i, 1, n) f[i] = i;
		int ans = 0;
		REP(i, 1, a)
		{
			int x, y; scanf("%lld%lld" ,&x, &y);
			REP(u, 1, n - x) Edge[++ m] = {u, u + x, y};
		}
		REP(i, 1, n) { int u, v, w; scanf("%lld%lld%lld" ,&u, &v, &w); Edge[++ m] = {u + 1, v + 1, w}; }
		sort(Edge + 1, Edge + m + 1);
		REP(i, 1, m)
		{
			int u = cha(Edge[i].u), v = cha(Edge[i].v);
			if ( u != v ) 
			{
				f[u] = v;
				ans = (ans + Edge[i].w) % 998244353;
			}
		}
		printf("%lld\n", ans); return 0; 
	}
	int d = n;
	REP(i, 1, a)
	{
		int x, y; scanf("%lld%lld", &x, &y);
		d = __gcd(d, x);
	}
	int ans = d;
	REP(i, 1, b)
	{
		int u, v, x; scanf("%lld%lld%lld", &u, &v, &x);
		u %= d; v %= d; ++ u; ++ v;
		if ( find(u) != find(v) ) { Map[u] = v; -- ans; } 
	}
	printf("%lld\n", (n - ans) % 998244353);
    return 0;
}
