#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6e5 + 10;

int n, q, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], anc[maxn][20], a[maxn], size[maxn];
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
	size[u] = 1;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ;
		dis[v] = dis[u] + 1; anc[v][0] = u;
		DFS(v, u); size[u] += size[v];
	}
}

inline int LCA(int x, int y)
{
	if ( dis[x] < dis[y] ) swap(x, y);
	for ( int j = 18; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
	if ( x == y ) return x;
	for ( int j = 18; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
	return anc[x][0];
}

inline int Dis(int x, int y) { return dis[x] + dis[y] - 2 * dis[LCA(x, y)]; }

inline bool cmp(int a, int b) { return dis[a] < dis[b]; }

inline int Get(int u, int len)
{
	for ( int j = 18; j >= 0; -- j )
		if ( (1 << j) <= len )
		{
			u = anc[u][j];
			len -= (1 << j);
		}
	while ( len ) { u = anc[u][0]; -- len; }
	return u;
}

int main()
{
	freopen("skyhigh.in", "r", stdin);
	freopen("skyhigh.out", "w", stdout);
	scanf("%d%d", &n, &q);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	dis[1] = 1; DFS(1, 0);
	REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	REP(j, 1, q)
	{
		int k; scanf("%d", &k);
		REP(i, 1, k) scanf("%d", &a[i]);
		sort(a + 1, a + k + 1, cmp);
		if ( k == 1 ) printf("%d\n", n);
		else if ( k == 2 )
		{
			int u = a[1], v = a[2], t = LCA(u, v);
			if ( Dis(u, v) & 1 ) { puts("0"); continue ; }
			int ans = 1;
			if ( dis[u] == dis[v] && t != u && t != v )
				ans = n - size[Get(u, dis[u] - dis[t] - 1)] - size[Get(v, dis[v] - dis[t] - 1)];
			else
			{
				t = Get(v, Dis(u, v) / 2);
				ans = size[t] - size[Get(v, (dis[v] - dis[t] - 1))];
			}
			printf("%d\n", ans);
		}
		else
		{
			int len = 0;
			REP(i, 2, k) len = max(len, Dis(a[1], a[i]));
			if ( len & 1 ) { puts("0"); continue ; }
			int t = Get(a[k], len / 2), p = len / 2;
			REP(i, 1, k - 1) if ( Dis(a[i], t) != p ) { puts("0"); goto Next ; }
			int ans = 0; bool flag = false;
			REP(i, 1, k) if ( dis[a[i]] <= p || Get(a[i], p) != t ) flag = true;
			ans = flag == false ? n : size[t];
			REP(i, 1, k) if ( dis[a[i]] > p && Get(a[i], p) == t )
			{
				int x = Get(a[i], p - 1);
				if ( vis[x] ) continue ; vis[x] = true;
				ans -= size[x];
			}
			REP(i, 1, k) if ( dis[a[i]] > p && Get(a[i], p) == t )
			{
				int x = Get(a[i], p - 1);
				vis[x] = false;
			}
			printf("%d\n", ans);
		}
		Next : ;
	}
	return 0;
}
