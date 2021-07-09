#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define x first
#define y second
typedef long long LL;

const int maxn = 2e6 + 10;

struct Segment_Tree
{
	struct node { int lson, rson, sum; } Tree[maxn << 5];
	int Root[maxn], tot;

	inline int Modify(int now, int l, int r, int pos)
	{
		int root = ++ tot; Tree[root] = Tree[now]; ++ Tree[root].sum;
		if ( l == r ) return root;
		int Mid = l + r >> 1;
		if ( pos <= Mid ) ls(root) = Modify(ls(root), l, Mid, pos);
		else rs(root) = Modify(rs(root), Mid + 1, r, pos);
		return root;
	}

	inline int Query(int root, int l, int r, int L, int R)
	{
		if ( !root ) return 0;
		if ( L <= l && r <= R ) return Tree[root].sum;
		int Mid = l + r >> 1, ret = 0;
		if ( L <= Mid ) ret += Query(ls(root), l, Mid, L, R);
		if ( Mid < R ) ret += Query(rs(root), Mid + 1, r, L, R);
		return ret;
	}
} A, B;

struct FHQ_Treap
{
	struct node { int lson, rson, fa, x, y, lazy1, lazy2, rank; } Tree[maxn];
	int tot;

	inline void NewNode(pii x)
	{
		++ tot; Tree[tot].x = x.x; Tree[tot].y = x.y;
		Tree[tot].rank = rand();
	}

	inline void Split(int root, int &a, int &b, int
} Tree;

int n, m, q, h[maxn];
pii a[maxn];
struct node { int op, pos; pii x; } Q[maxn];
vector<int> t[maxn];

inline bool Check(int L, int R, pii x)
{
	if ( A.Query(A.Root[R], 0, n, x.y, n - x.x) - A.Query(A.Root[L - 1], 0, n, x.y, n - x.x) > 0 ) return true;
	if ( B.Query(B.Root[R], 0, n, x.x, n - x.y) - B.Query(B.Root[L - 1], 0, n, x.x, n - x.y) > 0 ) return true;
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &q);
	REP(i, 1, m) { scanf("%d%d", &a[i].x, &a[i].y); Tree.NewNode(a[i]); h[i] = 1; }
	REP(i, 1, q)
	{
		scanf("%d", &Q[i].op);
		A.Root[i] = A.Root[i - 1];
		B.Root[i] = B.Root[i - 1];
		if ( Q[i].op == 1 ) scanf("%d", &Q[i].pos);
		else if ( Q[i].op == 2 ) { scanf("%d", &Q[i].x.x); Q[i].x.y = 1; A.Root[i] = A.Modify(A.Root[i], 0, n, Q[i].x.x); }
		else if ( Q[i].op == 3 ) { scanf("%d", &Q[i].x.x); Q[i].x.y = 2; B.Root[i] = B.Modify(B.Root[i], 0, n, Q[i].x.x); }
		else { scanf("%d%d", &Q[i].x.x, &Q[i].x.y); a[++ m] = Q[i].x; Q[i].pos = m; Tree.NewNode(Q[i].x); h[m] = i; }
	}
	REP(i, 1, m)
	{
		int L = 1, R = q, pos = q + 1;
		while ( L <= R )
		{
			int Mid = L + R >> 1;
			if ( Check(h[i], Mid, a[i]) ) { R = Mid - 1; pos = Mid; }
			else L = Mid + 1;
		}
		t[pos].push_back(i);
	}
	REP(i, 1, q)
	{
		for ( int j = 0; j < t[i]; ++ j ) Tree.Insert(t[i][j]);
		if ( Q[i].op == 1 ) Tree.Query(Q[i].pos);
		if ( Q[i].op == 2 ) Tree.Solve1(Q[i].x.x);
		if ( Q[i].op == 3 ) Tree.Solve2(Q[i].x.x);
	}
	return 0;
}
