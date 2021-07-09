#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int INF = 0x3f3f3f3f;
const int maxn = 3e5 + 10;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], a[maxn], ans;
int size[maxn], top[maxn], son[maxn], f[maxn], p[maxn], id[maxn], tot, b[maxn];
struct node { bitset<1000> x; } Tree[maxn << 2];
bitset<1000> Set[6];

inline void PushUp(int root) { Tree[root].x = Tree[lson].x | Tree[rson].x; }

inline void Build(int root, int l, int r)
{
	if ( l == r ) { Tree[root].x[a[id[l]]] = true; return ; }
	int Mid = l + r >> 1;
	Build(lson, l, Mid); Build(rson, Mid + 1, r);
	PushUp(root);
}

inline void Query(int root, int l, int r, int L, int R, int pos)
{
	if ( L <= l && r <= R ) { Set[pos] |= Tree[root].x; return ; }
	int Mid = l + r >> 1;
	if ( L <= Mid ) Query(lson, l, Mid, L, R, pos);
	if ( Mid < R ) Query(rson, Mid + 1, r, L, R, pos);
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
	size[u] = 1; int Max = 0;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ;
		dis[v] = dis[u] + 1; f[v] = u;
		DFS1(v, u);
		size[u] += size[v]; if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
	}
}

inline void DFS2(int u, int t)
{
	top[u] = t; p[u] = ++ tot; id[tot] = u;
	if ( son[u] ) DFS2(son[u], t);
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
		DFS2(v, v);
	}
}

inline int LCA(int x, int y)
{
	while ( top[x] != top[y] ) { if ( dis[top[x]] < dis[top[y]] ) swap(x, y); x = f[top[x]]; }
	return dis[x] < dis[y] ? x : y;
}

inline void Solve(int i, int y)
{
	int x = b[i];
	while ( top[x] != top[y] )
	{
		Query(1, 1, n, p[top[x]], p[x], i);
		x = f[top[x]];
	}
	Query(1, 1, n, p[y], p[x], i);
}

int main()
{
	freopen("party.in", "r", stdin);
	freopen("party.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &q);
	REP(i, 2, n) { int x; scanf("%d", &x); add(x, i); }
	REP(i, 1, n) scanf("%d", &a[i]);
	dis[1] = 1; DFS1(1, 0); DFS2(1, 1); Build(1, 1, n);
	while ( q -- )
	{
		int c; scanf("%d", &c);
		REP(i, 1, c) scanf("%d", &b[i]);
		int x = b[1]; REP(i, 2, c) x = LCA(x, b[i]);
		REP(i, 1, c) { Set[i].reset(); Solve(i, x); }
		ans = INF;
		REP(i, 1, (1 << c) - 1)
		{
			Set[0].reset(); int ret = 0;
			REP(j, 1, c) if ( i & (1 << j - 1) ) { ++ ret; Set[0] |= Set[j]; }
			ans = min(ans, (int)Set[0].count() / ret);
		}
		printf("%d\n", ans * c);
	}
	return 0;
}
