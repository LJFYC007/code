#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, x, y;
int dis[maxn], dis1[maxn], dis2[maxn], a[maxn], ans;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ;
		dis[v] = dis[u] + 1;
		DFS(v, u);
	}
}

inline int Find(int u)
{
	mem(dis);
	DFS(u, 0);
	REP(i, 1, n) if ( dis[i] > dis[u] ) u = i;
	return u;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
	x = Find(1); y = Find(x);
	mem(dis); DFS(x, 0); REP(i, 1, n) dis1[i] = dis[i];
	mem(dis); DFS(y, 0); REP(i, 1, n) dis2[i] = dis[i];
	REP(i, 1, n)
	{
		if ( a[i] >= a[x] ) ans = max(ans, a[i] * dis1[i]);
		if ( a[i] >= a[y] ) ans = max(ans, a[i] * dis2[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
