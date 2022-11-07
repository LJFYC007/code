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

const int maxn = 4e5 + 10;
const int INF = 1e18;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
struct node
{
	int Min, Max, len, id;
	node ( int a = INF, int b = INF, int c = 0, int d = 0 ) { len = a; Min = b; Max = c; id = d; }
	bool operator < (const node &a) const { return len > a.len; }
} dis[maxn], ans[maxn];
bool vis[maxn];
priority_queue<node> Q;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

node operator + (node a, int b) { return node(a.len + b, min(a.Min, b), max(a.Max, b), a.id); }

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld",&n,&m);
	REP(i, 1, m) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
	dis[1] = node(0, INF, 0, 1); Q.push(dis[1]);
	REP(i, 2, n) dis[i] = ans[i] = node(INF, INF, 0, i);
	while (!Q.empty())
	{
		node u = Q.top(); Q.pop();
		if (vis[u.id] ) continue ; vis[u.id] = true;
		for ( int i = Begin[u.id]; i; i = Next[i] )
		{
			int v = To[i];
			if ( dis[v].len > u.len + W[i] )
			{
				dis[v] = u + W[i]; dis[v].id = v;
				Q.push(dis[v]);
			}

			if ( ans[v].len > u.len + W[i] - W[i] + min(u.Min, W[i]) )
				ans[v] = node(u.len + min(u.Min, W[i]), min(u.Min, W[i]), max(u.Max, W[i]), ans[v].id);
			if ( ans[v].len > u.len + W[i] + W[i] - max(u.Max, W[i]) )
				ans[v] = node(u.len + W[i] + W[i] - max(u.Max, W[i]), min(u.Min, W[i]), max(u.Max, W[i]), ans[v].id);
		}
	}
	ans[1] = node(0, INF, 0, 1); Q.push(ans[1]);
	mem(vis);
	while (!Q.empty())
	{
		node u = Q.top(); Q.pop();
		if (vis[u.id] ) continue ; vis[u.id] = true;
		for ( int i = Begin[u.id]; i; i = Next[i] )
		{
			int v = To[i];
		//	if ( W[i] <= u.Max && W[i] >= u.Min &&
			if ( ans[v].len > u.len + W[i] )
			{
				ans[v] = u + W[i]; ans[v].id = v;
				Q.push(ans[v]);
			}
		}
	}
	REP(i, 2, n) printf("%lld ", ans[i].len); puts("");
    return 0;
}
