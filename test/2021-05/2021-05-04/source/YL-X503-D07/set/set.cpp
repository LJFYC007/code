#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e6 + 10;

int n, m, ans[maxn], c[maxn], d[maxn], N, p[maxn * 4];
vector<pii> Q[maxn]; 
struct Node { int a, b, c, d; } a[maxn];
struct NODE { int lazy, Max; } Tree[maxn * 40];

inline int lowbit(int x) { return x & -x; } 
inline void modify1(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) c[i] = max(c[i], val); }
inline void modify2(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) d[i] = min(d[i], val); }
inline int query1(int pos) { int ret = 1; for ( int i = pos; i > 0; i -= lowbit(i) ) ret = max(ret, c[i]); return ret; }
inline int query2(int pos) { int ret = N; for ( int i = pos; i > 0; i -= lowbit(i) ) ret = min(ret, d[i]); return ret; }

#define lson root << 1
#define rson root << 1 | 1

inline void PushTag(int root, int val) { Tree[root].lazy = Tree[root].Max = val; }

inline void PushDown(int root)
{
	if ( !Tree[root].lazy ) return ;
	PushTag(lson, Tree[root].lazy);
	PushTag(rson, Tree[root].lazy);
	Tree[root].lazy = 0;
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) { PushTag(root, val); return ; } 
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
	Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
}

inline int Query(int root, int l, int r, int L, int R, int val)
{
	if ( Tree[root].Max <= val ) return -1;
	if ( l == r ) return l;
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= l && r <= R ) 
	{
		if ( Tree[lson].Max > val ) return Query(lson, l, Mid, L, R, val);
		return Query(rson, Mid + 1, r, L, R, val);
	}
	if ( L <= Mid ) { int x = Query(lson, l, Mid, L, R, val); if ( x != -1 ) return x; } 
	if ( Mid < R ) return Query(rson, Mid + 1, r, L, R, val);
	return -1;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("set.in", "r", stdin);
	freopen("set.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m); vector<pii> ccc;
	REP(i, 1, n) 
	{
		scanf("%d%d%d%d", &a[i].a, &a[i].b, &a[i].c, &a[i].d);
		if ( a[i].a > a[i].c ) { swap(a[i].a, a[i].c); swap(a[i].b, a[i].d); }
		if ( a[i].c <= a[i].b ) { a[i].b = max(a[i].b, a[i].d); a[i].c = a[i].d = 0; }
		ccc.push_back(pii(a[i].a, i * 4)); ccc.push_back(pii(a[i].b, i * 4 + 1));
		if ( a[i].c ) { ccc.push_back(pii(a[i].c, i * 4 + 2)); ccc.push_back(pii(a[i].d, i * 4 + 3)); }
	}
	sort(ccc.begin(), ccc.end());
	for ( int i = 0; i < ccc.size(); ++ i ) 
	{
		if ( i == 0 || ccc[i].first != ccc[i - 1].first ) p[++ N] = ccc[i].first;
		if ( ccc[i].second % 4 == 0 ) a[ccc[i].second / 4].a = N;
		if ( ccc[i].second % 4 == 1 ) a[ccc[i].second / 4].b = N;
		if ( ccc[i].second % 4 == 2 ) a[ccc[i].second / 4].c = N;
		if ( ccc[i].second % 4 == 3 ) a[ccc[i].second / 4].d = N;
	}

	REP(i, 1, n) if ( a[i].c ) 
	{ 
		swap(a[i].b, a[i].d); swap(a[i].c, a[i].d); ++ a[i].c; -- a[i].d; 
		if ( a[i].c > a[i].d ) a[i].c = a[i].d = 0;
	}
	REP(i, 1, m) { int l, r; scanf("%d%d", &l, &r); Q[l].push_back(pii(r, i)); }
	Modify(1, 1, N, 1, N, n + 1);
	REP(i, 1, n) d[i] = N;
	for ( int i = n; i >= 1; -- i ) 
	{
		if ( a[i].c ) Modify(1, 1, N, a[i].c, a[i].d, i);
		modify1(i, a[i].a); modify2(i, a[i].b);
		for ( auto it : Q[i] ) 
		{
			int L = query1(it.first), R = query2(it.first);
			ans[it.second] = Query(1, 1, N, L, R, it.first);
		}
	}

	REP(i, 1, m) if ( ans[i] == -1 ) puts("NO"); else printf("%d\n", p[ans[i]]);
	return 0;
}
