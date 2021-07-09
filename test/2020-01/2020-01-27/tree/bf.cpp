#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 6e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], Root = 1, w[maxn];
int son[maxn], size[maxn], f[maxn], p[maxn], id[maxn], cnt, anc[maxn][20], top[maxn];
struct node
{
	#define lson root << 1
	#define rson root << 1 | 1
	struct Node { int sum, lazy; } Tree[maxn << 2];

	inline void PushTag(int root, int l, int r, int val)
	{
		Tree[root].sum += (r - l + 1) * val;
		Tree[root].lazy += val;
	}

	inline void PushUp(int root) { Tree[root].sum = Tree[lson].sum + Tree[rson].sum; }

	inline void PushDown(int root, int l, int r)
	{
		if ( !Tree[root].lazy ) return ;
		int Mid = l + r >> 1;
		PushTag(lson, l, Mid, Tree[root].lazy);
		PushTag(rson, Mid + 1, r, Tree[root].lazy);
		Tree[root].lazy = 0;
	}

	inline void Build(int root, int l, int r)
	{
		if ( l == r ) { Tree[root].sum = w[id[l]]; return ; }
		int Mid = l + r >> 1;
		Build(lson, l, Mid); Build(rson, Mid + 1, r);
		PushUp(root);
	}

	inline void Modify(int root, int l, int r, int L, int R, int val)
	{
		if ( L <= l && r <= R ) { PushTag(root, l, r, val); return ; }
		PushDown(root, l, r);
		int Mid = l + r >> 1;
		if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
		if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
		PushUp(root);
	}

	inline int Query(int root, int l, int r, int L, int R)
	{
		if ( L <= l && r <= R ) return Tree[root].sum;
		PushDown(root, l, r);
		int Mid = l + r >> 1, ret = 0;
		if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
		if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
		return ret;
	}
} Tree[2];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
	size[u] = 1; int Max = 0;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ;
		anc[v][0] = u; dis[v] = dis[u] + 1; f[v] = u;
		DFS1(v, u);
		size[u] += size[v];
		if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
	}
}

inline void DFS2(int u, int t)
{
	p[u] = ++ cnt; id[cnt] = u; top[u] = t;
	if ( son[u] ) DFS2(son[u], t);
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == son[u] || v == f[u] ) continue ;
		DFS2(v, v);
	}
}

inline int LCA(int x, int y)
{
	while ( top[x] != top[y] ) { if ( dis[top[x]] < dis[top[y]] ) swap(x, y); x = f[top[x]]; }
	return dis[x] < dis[y] ? x : y;
}

inline void Solve(int x, int y, int val)
{
	while ( top[x] != top[y] )
	{
		if ( dis[top[x]] < dis[top[y]] ) swap(x, y);
		Tree[1].Modify(1, 1, n, p[top[x]], p[x], val);
		x = f[top[x]];
	}
	if ( dis[x] > dis[y] ) swap(x, y);
	Tree[1].Modify(1, 1, n, p[x], p[y], val);
}

inline bool Check(int x)
{
	if ( !x ) return false;
	return Tree[1].Query(1, 1, n, p[x], p[x] + size[x] - 1) > 0 ? false : true;
}

signed main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n) scanf("%lld", &w[i]);
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
	dis[1] = 1; DFS1(1, 0); DFS2(1, 1);
	Tree[0].Build(1, 1, n);
	REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	while ( m -- )
	{
		int op; scanf("%lld", &op);
		if ( op == 1 ) scanf("%lld", &Root);
		if ( op == 2 )
		{
			int u, v, val; scanf("%lld%lld%lld", &u, &v, &val);
			int x = LCA(u, v);
			if ( x == Root ) { Tree[0].Modify(1, 1, n, 1, n, val); continue ; }
			if ( LCA(x, Root) != x ) { Tree[0].Modify(1, 1, n, p[x], p[x] + size[x] - 1, val); continue ; }
			int pos = Root; Solve(u, v, 1);
			for ( int j = 18; j >= 0; -- j ) if ( Check(anc[pos][j]) ) pos = anc[pos][j];
			if ( !Tree[1].Query(1, 1, n, p[pos], p[pos]) ) pos = anc[pos][0];
			Solve(u, v, -1);
			Tree[0].Modify(1, 1, n, 1, n, val);
			if ( pos == Root ) continue ;
			Tree[0].Modify(1, 1, n, p[Root] + 1, p[Root] + size[Root] - 1, -val);
			x = Root;
			while ( top[x] != top[pos] )
			{
				Tree[0].Modify(1, 1, n, p[top[x]], p[x], -val);
				x = f[top[x]];
			}
			if ( pos != x ) Tree[0].Modify(1, 1, n, p[pos] + 1, p[x], -val);
		}
		if ( op == 3 )
		{
			int u; scanf("%lld", &u);
			if ( u == Root ) printf("%lld\n", Tree[0].Query(1, 1, n, 1, n));
			else if ( LCA(u, Root) != u ) printf("%lld\n", Tree[0].Query(1, 1, n, p[u], p[u] + size[u] - 1));
			else
			{
				int ret = Tree[0].Query(1, 1, n, 1, n) - Tree[0].Query(1, 1, n, p[Root] + 1, p[Root] + size[Root] - 1);
				int x = Root;
				while ( top[x] != top[u] )
				{
					ret -= Tree[0].Query(1, 1, n, p[top[x]], p[x]);
					x = f[top[x]];
				}
				if ( u != x ) ret -= Tree[0].Query(1, 1, n, p[u] + 1, p[x]);
				printf("%lld\n", ret);
			}
		}
	}
	REP(i, 1, n) printf("%lld ", Tree[0].Query(1, 1, n, p[i], p[i])); puts("");
	return 0;
}
