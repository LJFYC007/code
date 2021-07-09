#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 410;
const int INF = 0x3f3f3f3f;

int n, k, a[maxn], Begin[maxn], Next[maxn], To[maxn], e;
int f[maxn][maxn], ans = -INF, g[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
	f[u][0] = a[u];
	REP(i, 1, k) f[u][i] = -INF;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ;
		DFS(v, u);
		REP(j, 0, k) g[j] = f[u][j];
		REP(j, 0, k) REP(o, 0, k) if ( j + o >= k ) f[u][min(j + 1, o)] = max(f[u][min(j + 1, o)], g[o] + f[v][j]);
		REP(j, 1, k) f[u][j] = max(f[u][j], f[v][j - 1]);
		f[u][0] = max(f[u][0], f[v][k] + a[u]);
		f[u][k] = max(f[u][k], f[v][k]);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	DFS(1, 0);
	REP(i, 0, k) ans = max(ans, f[1][i]);
	printf("%d\n", ans);
	return 0;
}
