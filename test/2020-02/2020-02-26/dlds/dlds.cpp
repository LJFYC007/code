#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int long long
typedef long long LL;

const int maxn = 250010;
const int N = 1e6;

int n, m, tot, Root[maxn], len, t1, t2;
vector<pii> v[maxn];
int tmp[maxn];
struct node2
{
	int lson, rson, A, val, id, lazy1, lazy2, size, Max, rank;
	node2(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0, int f = 0, int g = 0)
	{
		lson = a; rson = b; Max = val = c; id = d; lazy1 = lazy2 = e; size = f; rank = rand(); A = g;
	}
} ;
struct node1
{
	vector<node2> Tree; int lson, rson, Root, lazy;

	inline void PushTag1(int root, int lazy) { Tree[root].id += lazy; Tree[root].lazy1 += lazy; }

	inline void PushTag2(int root, int lazy) { Tree[root].lazy2 += lazy; if ( ls(root) ) ls(root) += lazy; if ( rs(root) ) rs(root) += lazy; }

	inline void PushDown(int root)
	{
		if ( Tree[root].lazy1 )
		{
			if ( ls(root) ) PushTag1(ls(root), Tree[root].lazy1);
			if ( rs(root) ) PushTag1(rs(root), Tree[root].lazy1);
			Tree[root].lazy1 = 0;
		}
		if ( Tree[root].lazy2 )
		{
			if ( ls(root) ) PushTag2(ls(root), Tree[root].lazy2);
			if ( rs(root) ) PushTag2(rs(root), Tree[root].lazy2);
			Tree[root].lazy2 = 0;
		}
	}

	inline void PushUp(int root)
	{
		Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1;
		Tree[root].Max = max(Tree[root].val, max(Tree[ls(root)].Max, Tree[rs(root)].Max));
	}

	inline void Split(int root, int &a, int &b, int k)
	{
		if ( !root ) { a = b = 0; return ; }
		PushDown(root);
		if ( Tree[root].id <= k ) { a = root; Split(rs(a), rs(a), b, k); }
		else { b = root; Split(ls(b), a, ls(b), k); }
		PushUp(root);
	}

	inline void Merge(int &root, int a, int b)
	{
		if ( !a || !b ) { root = a + b; return ; }
		if ( Tree[a].rank < Tree[b].rank ) { PushDown(a); root = a; Merge(rs(a), rs(a), b); }
		else { PushDown(b); root = b; Merge(ls(b), a, ls(b)); }
		PushUp(root);
	}

	inline int Query(pii x)
	{
		int a, b, c, ret; Split(Root, a, b, x.first - 1); Split(b, b, c, x.second);
		ret = Tree[b].size; Merge(b, b, c); Merge(Root, a, b);
		return ret;
	}

	inline int Query1(pii x)
	{
		int a, b, c, ret; Split(Root, a, b, x.first - 1); Split(b, b, c, x.second);
		ret = Tree[b].Max; Merge(b, b, c); Merge(Root, a, b);
		return ret;
	}

	inline void print(int root)
	{
		if ( !root ) return ;
		print(ls(root));
		cerr << root << " " << ls(root) << " " << rs(root) << " " << Tree[root].size<< " " << Tree[root].val << " " << Tree[root].id << endl;
		print(rs(root));
	}

	inline void Modify(pii x)
	{
		int a, b, c; Split(Root, a, b, x.first - 1); Split(b, b, c, x.first);
		Tree[b].val = Tree[b].Max = x.second; Merge(b, b, c); Merge(Root, a, b);
	}

	inline void Query2(int pos)
	{
		int a, b, c; Split(Root, a, b, pos - 1); Split(b, b, c, pos);
		t1 = Tree[b].A; t2 = Tree[b].val; Merge(b, b, c); Merge(Root, a, b);
	}

	inline void Delete(int pos) { int a, b, c; Split(Root, a, b, pos - 1); Split(b, b, c, pos); Merge(Root, a, c); }
} Tree[maxn << 5];

inline void PushDown(int root)
{
	if ( !Tree[root].lazy ) return ;
	if ( ls(root) && Tree[ls(root)].Tree.size() > 1 ) { Tree[ls(root)].lazy += Tree[root].lazy; Tree[ls(root)].PushTag1(Tree[ls(root)].Root, Tree[root].lazy); }
	if ( rs(root) && Tree[rs(root)].Tree.size() > 1 ) { Tree[rs(root)].lazy += Tree[root].lazy; Tree[rs(root)].PushTag1(Tree[rs(root)].Root, Tree[root].lazy); }
	Tree[root].lazy = 0;
}

inline void Modify2(int root, int A, pii x)
{
	if ( !Tree[root].Tree.size() ) Tree[root].Tree.push_back(node2(0, 0, 0, 0, 0, 0, 0));
	Tree[root].Tree.push_back(node2(0, 0, x.second, x.first, 0, 1, A));
	int pos = Tree[root].Tree.size() - 1;
	int a, b; Tree[root].Split(Tree[root].Root, a, b, x.first - 1);
	Tree[root].Merge(a, a, pos); Tree[root].Merge(Tree[root].Root, a, b);
}

inline int Query1(int root, int l, int r, int L, int R, pii x)
{
	if ( !root ) return 0;
	if ( L <= l && r <= R ) return Tree[root].Query(x);
	PushDown(root); int Mid = l + r >> 1, ret = 0;
	if ( L <= Mid ) ret += Query1(ls(root), l, Mid, L, R, x);
	if ( Mid < R ) ret += Query1(rs(root), Mid + 1, r, L, R, x);
	return ret;
}

inline int Query2(int root, int l, int r, int k, pii x)
{
	if ( !root ) return 0;
	if ( l == r ) return l;
	PushDown(root); int Mid = l + r >> 1, ret = (rs(root) && Tree[rs(root)].Tree.size() > 1) ? Tree[rs(root)].Query(x) : 0;
	if ( k <= ret ) return Query2(rs(root), Mid + 1, r, k, x);
	return Query2(ls(root), l, Mid, k - ret, x);
}

inline int Query3(int root, int l, int r, int L, int R, pii x)
{
	if ( !root ) return 0;
	if ( L <= l && r <= R ) return Tree[root].Query1(x);
	PushDown(root); int Mid = l + r >> 1, ret = 0;
	if ( L <= Mid ) ret = max(ret, Query3(ls(root), l, Mid, L, R, x));
	if ( Mid < R ) ret = max(ret, Query3(rs(root), Mid + 1, r, L, R, x));
	return ret;
}

inline void Modify1(int &root, int l, int r, int pos, pii x)
{
	if ( !root ) root = ++ tot; Modify2(root, pos, x);
	if ( l == r ) return ;
	PushDown(root); int Mid = l + r >> 1;
	if ( pos <= Mid ) Modify1(ls(root), l, Mid, pos, x);
	else Modify1(rs(root), Mid + 1, r, pos, x);
}

inline void Modify3(int root, int l, int r, int pos, pii x)
{
	Tree[root].Modify(x);
	if ( l == r ) return ;
	PushDown(root); int Mid = l + r >> 1;
	if ( pos <= Mid ) Modify3(ls(root), l, Mid, pos, x);
	else Modify3(rs(root), Mid + 1, r, pos, x);
}

inline void Delete(int root, int l, int r, int pos, int id)
{
	Tree[root].Delete(id);
	if ( l == r ) return ;
	PushDown(root); int Mid = l + r >> 1;
	if ( pos <= Mid ) Delete(ls(root), l, Mid, pos, id);
	else Delete(rs(root), Mid + 1, r, pos, id);
}

inline int Merge(int p, int q, int l, int r)
{
	if ( !p || !q )
	{
		if ( q ) { Tree[q].lazy += len; Tree[q].PushTag1(Tree[q].Root, len); }
		return p + q;
	}
	if ( !Tree[p].Tree.size() ) Tree[p].Tree.push_back(node2(0, 0, 0, 0, 0, 0, 0));
	if ( Tree[q].Tree.size() > 1 )
	{
		int size = Tree[p].Tree.size() - 1;
		REP(i, 1, Tree[q].Tree.size() - 1) Tree[p].Tree.push_back(Tree[q].Tree[i]);
		int Root = Tree[q].Root + size;
		Tree[p].PushTag1(Root, len); Tree[p].PushTag2(Root, size); Tree[p].Merge(Tree[p].Root, Tree[p].Root, Root);
	}
	if ( l == r ) return p;
	PushDown(p); PushDown(q); int Mid = l + r >> 1;
	ls(p) = Merge(ls(p), ls(q), l, Mid); rs(p) = Merge(rs(p), rs(q), Mid + 1, r);
	return p;
}

signed main()
{
	freopen("dlds.in", "r", stdin);
	freopen("dlds.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n)
	{
		int x, y; scanf("%lld%lld", &x, &y);
		Modify1(Root[i], 1, N, x, pii(1, y));
		v[i].push_back(pii(x, y));
	}
	int ans = 0;
	while ( m -- )
	{
		int opt, x; scanf("%lld%lld", &opt, &x); x ^= ans;
		if ( opt == 1 )
		{
			int y, val; scanf("%lld%lld", &y, &val); y ^= ans; val ^= ans;
			t1 = t2 = 0; Tree[Root[x]].Query2(y);
			Delete(Root[x], 1, N, t1, y);
			Modify1(Root[x], 1, N, val, pii(y, t2));
		}
		if ( opt == 2 )
		{
			int y, val; scanf("%lld%lld", &y, &val); y ^= ans; val ^= ans;
			t1 = t2 = 0; Tree[Root[x]].Query2(y);
			Modify3(Root[x], 1, N, t1, pii(y, val));
		}
		if ( opt == 3 )
		{
			int y; scanf("%lld", &y); y ^= ans;
			len = Tree[Root[x]].Tree.size() - 1;
			Root[x] = Merge(Root[x], Root[y], 1, N);
		}
		if ( opt == 4 )
		{
			int l, r, val; scanf("%lld%lld%lld", &l, &r, &val); l ^= ans; r ^= ans; val ^= ans;
			ans = Query1(Root[x], 1, N, val + 1, N, pii(l, r));
			printf("%lld\n", ans);
		}
		if ( opt == 5 )
		{
			int l, r, k; scanf("%lld%lld%lld", &l, &r, &k); l ^= ans; r ^= ans; k ^= ans;
			ans = Query2(Root[x], 1, N, k, pii(l, r));
			printf("%lld\n", ans);
		}
		if ( opt == 6 )
		{
			int l, r, L, R; scanf("%lld%lld%lld%lld", &l, &r, &L, &R); l ^= ans; r ^= ans; L ^= ans; R ^= ans;
			ans = Query3(Root[x], 1, N, L, R, pii(l, r));
			printf("%lld\n", ans);
		}
		fflush(stdout);
	}
	return 0;
}
