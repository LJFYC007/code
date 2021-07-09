#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int n, m, N, Begin[maxn << 1], Next[maxn << 1], To[maxn << 1], e, ans[maxn];
int size[maxn], dis[maxn], son[maxn], f[maxn], id[maxn], p[maxn], top[maxn], tot, g[maxn];
struct node1 { int u, v, p; } a[maxn];
struct node2
{
	int u, v, id;
	node2(int a = 0, int b = 0, int c = 0) { u = a; v = b; id = c; }
} Q[maxn];
struct node3
{
	int u, v, t, id;
	node3(int a = 0, int b = 0, int c = 0, int d = 0) { u = a; v = b; t = c; id = d; }
	bool operator < (const node3 &a) const { return u < a.u || (u == a.u && (v < a.v || (v == a.v && t < a.t))); }
} Line[maxn];
struct node { int len, sum1, sum2, sum3, sum4, lazy1, lazy2; } Tree[maxn << 2];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void Build(int root, int l, int r)
{
	Tree[root].sum1 = Tree[root].sum2 = Tree[root].lazy1 = 1; Tree[root].len = r - l + 1;
	if ( l == r ) return ;
	int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
}

inline void PushTag3(int root, int val) { Tree[root].lazy2 = (Tree[root].lazy2 + val) % Mod; Tree[root].sum3 = (Tree[root].sum3 + Tree[root].len * val) % Mod; }

inline void PushTag1(int root, int val) { Tree[root].lazy1 = Tree[root].lazy1 * val % Mod; Tree[root].sum1 = Tree[root].sum1 * val % Mod; }

inline void PushDown(int root)
{
	if ( Tree[root].lazy1 ) { PushTag1(lson, Tree[root].lazy1); PushTag1(rson, Tree[root].lazy1); Tree[root].lazy1 = 1; }
	if ( Tree[root].lazy2 ) { PushTag3(lson, Tree[root].lazy2); PushTag3(rson, Tree[root].lazy2); Tree[root].lazy2 = 0; }
}

inline void Modify1(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) { PushTag3(root, 1); return ; }
	PushDown(root); int Mid = l + r >> 1;
	if ( L <= Mid ) Modify1(lson, l, Mid, L, R);
	if ( Mid < R ) Modify1(rson, Mid + 1, r, L, R);
}

inline void Modify2(int root, int l, int r, int pos)
{
	++ Tree[root].sum4; if ( l == r ) return ;
	int Mid = l + r >> 1;
	if ( pos <= Mid ) Modify2(lson, l, Mid, pos);
	else Modify2(rson, Mid + 1, r, pos);
}

inline void Modify3(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) { PushTag1(root, val); return ; }
	PushDown(root); int Mid = l + r >> 1;
	if ( L <= Mid ) Modify3(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify3(rson, Mid + 1, r, L, R, val);
}

inline void Modify4(int root, int l, int r, int pos, int val)
{
	Tree[root].sum2 = Tree[root].sum2 * val % Mod; if ( l == r ) return ;
	int Mid = l + r >> 1;
	if ( pos <= Mid ) Modify4(lson, l, Mid, pos, val);
	else Modify4(rson, Mid + 1, r, pos, val);
}

inline int Query1(int root, int l, int r, int pos)
{
	if ( l == r ) return Tree[root].sum1;
	PushDown(root); int Mid = l + r >> 1;
	if ( pos <= Mid ) return Query1(lson, l, Mid, pos);
	return Query1(rson, Mid + 1, r, pos);
}

inline int Query2(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) return Tree[root].sum2;
	int Mid = l + r >> 1, ret = 1;
	if ( L <= Mid ) ret = ret * Query2(lson, l, Mid, L, R) % Mod;
	if ( Mid < R ) ret = ret * Query2(rson, Mid + 1, r, L, R) % Mod;
	return ret;
}

inline int Query3(int root, int l, int r, int pos)
{
	if ( l == r ) return Tree[root].sum3;
	PushDown(root); int Mid = l + r >> 1;
	if ( pos <= Mid ) return Query3(lson, l, Mid, pos);
	return Query3(rson, Mid + 1, r, pos);
}

inline int Query4(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) return Tree[root].sum4;
	int Mid = l + r >> 1, ret = 0;
	if ( L <= Mid ) ret = (ret + Query4(lson, l, Mid, L, R)) % Mod;
	if ( Mid < R ) ret = (ret + Query4(rson, Mid + 1, r, L, R)) % Mod;
	return ret;
}

inline void Solve1(int u, int t)
{
	while ( top[u] != top[t] ) { Modify1(1, 1, n, id[top[u]], id[u]); u = f[top[u]]; }
	if ( dis[u] > dis[t] ) Modify1(1, 1, n, id[t] + 1, id[u]);
}

inline void Solve2(int u, int t, int val)
{
	while ( top[u] != top[t] ) { Modify3(1, 1, n, id[top[u]], id[u], val); u = f[top[u]]; }
	if ( dis[u] > dis[t] ) Modify3(1, 1, n, id[t] + 1, id[u], val);
}

inline int Solve3(int u, int t)
{
	int sum = 1;
	while ( top[u] != top[t] ) { sum = sum * Query2(1, 1, n, id[top[u]], id[u]) % Mod; u = f[top[u]]; }
	if ( dis[u] > dis[t] ) sum = sum * Query2(1, 1, n, id[t] + 1, id[u]) % Mod;
	return sum;
}

inline int Solve4(int u, int t)
{
	int sum = 0;
	while ( top[u] != top[t] ) { sum += Query4(1, 1, n, id[top[u]], id[u]); u = f[top[u]]; }
	if ( dis[u] > dis[t] ) sum += Query4(1, 1, n, id[t] + 1, id[u]);
	return sum;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == fa ) continue ;
        f[v] = u; dis[v] = dis[u] + 1; DFS1(v, u);
        if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
        size[u] += size[v];
    }
}

inline void DFS2(int u, int t)
{
    id[u] = ++ tot; p[tot] = u; top[u] = t;
    if ( !son[u] ) return ; DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) { int v = To[i]; if ( v == f[u] || v == son[u] ) continue ; DFS2(v, v); }
}

inline int LCA(int x, int y) { while ( top[x] != top[y] ) { if ( dis[top[x]] < dis[top[y]] ) swap(x, y); x = f[top[x]]; } return dis[x] < dis[y] ? x : y; }

inline int Get(int x, int t) { while ( f[top[x]] != t && top[x] != top[t] ) x = f[top[x]]; return f[top[x]] == t ? top[x] : p[id[t] + 1]; }

signed main()
{
	freopen("cactus.in", "r", stdin);
	freopen("cactus.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
	REP(i, 1, m) scanf("%lld%lld%lld", &a[i].u, &a[i].v, &a[i].p);
	dis[1] = 1; DFS1(1, 0); DFS2(1, 1); Build(1, 1, n);
	REP(i, 1, m)
	{
		if ( a[i].p == 0 )
		{
			ans[i] = 1; g[i] = -1;
			int t = LCA(a[i].u, a[i].v);
			int x = a[i].u; if ( x != t ) { Solve1(x, t); x = Get(x, t); Q[++ N] = node2(t, x, i); }
			int y = a[i].v; if ( y != t ) { Solve1(y, t); y = Get(y, t); Q[++ N] = node2(t, y, i); }
			Line[i] = node3(min(x, y), max(x, y), t, i);
			if ( x != t ) Modify2(1, 1, n, id[x]);
			if ( y != t && x != y ) Modify2(1, 1, n, id[y]);
			if ( x != t && y != t ) -- g[i];
			continue ;
		}
		ans[i] = (1 - a[i].p) * power(a[i].p, Mod - 2) % Mod;
		int t = LCA(a[i].u, a[i].v);
		int x = a[i].u; if ( x != t ) { Solve2(x, t, a[i].p); x = Get(x, t); Q[++ N] = node2(t, x, i); }
		int y = a[i].v; if ( y != t ) { Solve2(y, t, a[i].p); y = Get(y, t); Q[++ N] = node2(t, y, i); }
		Line[i] = node3(min(x, y), max(x, y), t, i);
		if ( x != t ) Modify4(1, 1, n, id[x], a[i].p);
		if ( y != t && x != y ) Modify4(1, 1, n, id[y], a[i].p);
	}
	REP(i, 1, m)
	{
		int t = LCA(a[i].u, a[i].v), x = a[i].u, y = a[i].v;
		if ( dis[x] > dis[t] + 1 ) { int X = Get(x, t); g[i] += Solve4(x, X); ans[i] = ans[i] * Solve3(x, X) % Mod; }
		if ( dis[y] > dis[t] + 1 ) { int Y = Get(y, t); g[i] += Solve4(y, Y); ans[i] = ans[i] * Solve3(y, Y) % Mod; }
	}
	REP(i, 1, N)
	{
		ans[Q[i].id] = ans[Q[i].id] * Query1(1, 1, n, id[Q[i].v]) % Mod;
		g[Q[i].id] += Query3(1, 1, n, id[Q[i].v]);
	}
	REP(i, 1, m) if ( g[i] > 0 ) ans[i] = 0;
	sort(Line + 1, Line + m + 1);
	for ( int i = 1, j; i <= m; i = j )
	{
		int sum = a[Line[i].id].p == 0 ? 1 : a[Line[i].id].p;
		j = i + 1;
		if ( Line[i].u == Line[i].t ) continue ;
		while ( j <= m && Line[i].u == Line[j].u && Line[i].v == Line[j].v && Line[i].t == Line[j].t )
		{
			if ( a[Line[j].id].p == 0 ) { ++ j; continue ; }
			sum = (sum * a[Line[j].id].p) % Mod;
			++ j;
		}
		REP(k, i, j - 1) ans[Line[k].id] = ans[Line[k].id] * power(sum, Mod - 2) % Mod;
	}
	int ret = 0;
	REP(i, 1, m) ret = (ret + ans[i]) % Mod;
	printf("%lld\n", (ret + Mod) % Mod);
	return 0;
}
