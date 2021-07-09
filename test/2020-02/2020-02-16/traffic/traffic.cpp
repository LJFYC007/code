#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

struct node
{
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
	struct node1 { int lson, rson, sum; } Tree[maxn << 5];
	int Root[maxn], tot;

	inline int Modify(int now, int l, int r, int pos)
	{
		int root = ++ tot; Tree[root] = Tree[now]; ++ Tree[root].sum;
		if ( l == r ) return root;
		int Mid = l + r >> 1;
		if ( pos <= Mid ) ls(root) = Modify(ls(root), l, Mid, pos);
		else rs(root) = Modify(rs(root), Mid + 1, r, pos);
	}

	inline int Find(int p, int q, int l, int r, int L, int R)
	{
		if ( Tree[p].sum == Tree[q].sum ) return 0;
		if ( L <= l && r <= R ) return Tree[q].sum - Tree[p].sum;
		int Mid = l + r >> 1, ret = 0;
		if ( L <= Mid ) ret += Find(ls(p), ls(q), l, Mid, L, R);
		if ( Mid < R ) ret += Find(rs(p), rs(q), Mid + 1, r, L, R);
		return ret;
	}

	inline int Query(int p, int q, int l, int r, int k)
	{
		if ( k > Tree[q].sum - Tree[p].sum ) return -1;
		if ( l == r ) return l;
		int Mid = l + r >> 1, ret = Tree[ls(q)].sum - Tree[ls(p)].sum;
		if ( k <= ret ) return Query(ls(p), ls(q), l, Mid, k);
		else return Query(rs(p), rs(q), Mid + 1, r, k - ret);
	}

	inline void Solve(int l, int r, int x, int &ans1, int &ans2)
	{
		int pos = Find(Root[l], Root[r], 1, n, 1, x);
		ans1 = Query(Root[l], Root[r], 1, n, pos);
		ans2 = Query(Root[l], Root[r], 1, n, pos + 1);
	}
} Tree[4];
struct node2 { int Max, Maxx, size} a[maxn];
int n, Begin[maxn], Next[maxn], To[maxn], e, id[maxn], p[maxn], tot, deg[maxn], Deg[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
	a[u].size = 1; p[u] = ++ tot; id[tot] = u;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; DFS(v);
		a[u].size += a[v].size;
		if ( a[v].size >
	}
}

int main()
{
	freopen("traffic.in", "r", stdin);
	freopen("traffic.outt", "w", stdout);
	scanf("%d", &n);
	REP(i, 2, n) { int x; scanf("%d", &x); add(x, i); ++ Deg[x]; }
	DFS(1);
	return 0;
}

/*
Max - x == x + Min
x = (Max - Min) / 2
<= >
*/
