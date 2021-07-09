#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e3 + 10;

int n, m, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, f[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ;
		f[v] = u; DFS(v, u);
	}
}

int main()
{
	freopen("food.in", "r", stdin);
	freopen("food.out", "w", stdout);
	scanf("%d%d", &n, &m);
	if ( m == 0 ) return 0;
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	DFS(1, 0);
	REP(i, 1, m)
	{
		int u, v; scanf("%d%d", &u, &v);
		int ans = a[v], x = 1;
		while ( v != u )
		{
			ans = max(ans, a[f[v]] ^ x);
			++ x; v = f[v];
		}
		printf("%d\n", ans);
	}
	return 0;
}
