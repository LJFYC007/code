#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int Mod = 998244353;

int n, q, Begin[maxn], Next[maxn], To[maxn], e, ans[maxn], a[maxn];
int dis[maxn], son[maxn], f[maxn], size[maxn], id[maxn], p[maxn], top[maxn], tot;
struct node { int lazy, sum; } Tree[maxn << 2];

inline void PushTag(int root, int l, int r, int val)
{
	Tree[root].lazy = (Tree[root].lazy + val) % Mod;
	Tree[root].sum = (Tree[root].sum + (r - l + 1) * val) % Mod;
}

inline void PushDown(int root, int l, int r)
{
	if ( !Tree[root].lazy ) return ;
	int Mid = l + r >> 1;
	PushTag(lson, l, Mid, Tree[root].lazy);
	PushTag(rson, Mid + 1, r, Tree[root].lazy);
	Tree[root].lazy = 0;
}

inline void PushUp(int root) { Tree[root].sum = (Tree[lson].sum + Tree[rson].sum) % Mod; }

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) { PushTag(root, l, r, val); return ; }
	PushDown(root, l, r); int Mid = l + r >> 1;
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
	PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) return Tree[root].sum;
	PushDown(root, l, r); int Mid = l + r >> 1, ret = 0;
	if ( L <= Mid ) ret = (ret + Query(lson, l, Mid, L, R)) % Mod;
	if ( Mid < R ) ret = (ret + Query(rson, Mid + 1, r, L, R)) % Mod;
	return ret;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == fa ) continue ;
        f[v] = u; dis[v] = dis[u] + 1;
        DFS1(v, u);
        if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
        size[u] += size[v];
    }
}

inline void DFS2(int u, int t)
{
    id[u] = ++ tot; p[tot] = u; top[u] = t;
    if ( !son[u] ) return ;
    DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
        DFS2(v, v);
    }
}

inline void Solve1(int u, int val)
{
	int v = 1;
	while ( top[u] != top[v] )
	{
		if ( dis[top[u]] < dis[top[v]] ) swap(u, v);
		Modify(1, 1, n, id[top[u]], id[u], val);
		u = f[top[u]];
	}
	if ( dis[u] > dis[v] ) swap(u, v);
	Modify(1, 1, n, id[u], id[v], val);
}

inline int Solve2(int u)
{
	int v = 1, sum = 0;
	while ( top[u] != top[v] )
	{
		if ( dis[top[u]] < dis[top[v]] ) swap(u, v);
		sum = (sum + Query(1, 1, n, id[top[u]], id[u])) % Mod;
		u = f[top[u]];
	}
	if ( dis[u] > dis[v] ) swap(u, v);
	sum = (sum + Query(1, 1, n, id[u], id[v])) % Mod;
	return sum;
}

inline int Get(int x) { return (x * (x + 1) / 2) % Mod; }

signed main()
{
	freopen("sumsumsumsum.in", "r", stdin);
	freopen("sumsumsumsum.out", "w", stdout);
	scanf("%lld%lld", &n, &q);
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
	REP(i, 1, n) scanf("%lld", &a[i]);
	dis[1] = 1; DFS1(1, 0); DFS2(1, 1);
	int sum = 0, sum1 = 0;
	REP(i, 1, n)
	{
		sum1 = (sum1 + dis[a[i]] * i) % Mod;
		sum = (sum + sum1) % Mod;
		sum = (sum + dis[a[i]] * Get(i)) % Mod;
		Solve1(a[i], i);
		sum = (sum - 2 * Solve2(a[i])) % Mod;
		ans[i] = (ans[i - 1] + sum) % Mod;
		ans[i] = (ans[i] + Mod) % Mod;
	}
	REP(i, 1, q) { int k; scanf("%lld", &k); printf("%lld\n", ans[k]); }
	return 0;
}
