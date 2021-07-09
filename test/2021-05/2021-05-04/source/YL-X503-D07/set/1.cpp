#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 3e5 + 10;

int n, m, p[maxn * 4], B, belong[maxn], ans[maxn], N;
struct node 
{ 
	int l, r, id; 
	bool operator < (const node &a) const 
	{
		if ( belong[l] != belong[a.l] ) return belong[l] < belong[a.l];
		return (belong[l] & 1) ? (r < a.r) : (r > a.r);
	}
} q[maxn];
struct Node { int a, b, c, d; } a[maxn];
map<int, int> Map;
struct NODE { int Max, id, lazy; } Tree[maxn << 5];

#define lson root << 1
#define rson root << 1 | 1
inline void Build(int root, int l, int r)
{
	Tree[root].id = l; if ( l == r ) return ;
	int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) { Tree[root].Max += val; Tree[root].lazy += val; return ; } 
	int Mid = l + r >> 1; 
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
	Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max) + Tree[root].lazy;
	Tree[root].id = Tree[lson].Max >= Tree[rson].Max ? Tree[lson].id : Tree[rson].id;
}

inline void Insert(int x)
{
	Modify(1, 1, N, a[x].a, a[x].b, 1);
	if ( a[x].c ) Modify(1, 1, N, a[x].c, a[x].d, 1);
}

inline void Erase(int x) 
{ 
	Modify(1, 1, N, a[x].a, a[x].b, -1);
	if ( a[x].c ) Modify(1, 1, N, a[x].c, a[x].d, -1);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("set.in", "r", stdin);
	freopen("set.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n) 
	{
		scanf("%d%d%d%d", &a[i].a, &a[i].b, &a[i].c, &a[i].d);
		if ( a[i].a > a[i].c ) { swap(a[i].a, a[i].c); swap(a[i].b, a[i].d); }
		if ( a[i].c <= a[i].b ) { a[i].b = max(a[i].b, a[i].d); a[i].c = a[i].d = 0; }
		Map[a[i].a] = Map[a[i].b] = true;
		if ( a[i].c ) Map[a[i].c] = Map[a[i].d] = true;
	}
	for ( auto it : Map ) { Map[it.first] = ++ N; p[N] = it.first; } 
	REP(i, 1, n) { a[i].a = Map[a[i].a]; a[i].b = Map[a[i].b]; a[i].c = Map[a[i].c]; a[i].d = Map[a[i].d]; } 


	REP(i, 1, m) { scanf("%d%d", &q[i].l, &q[i].r); q[i].id = i; } 
	B = sqrt(m); REP(i, 1, m) belong[i] = (i - 1) / B + 1;
	sort(q + 1, q + m + 1);

	Build(1, 1, N);
	int L = 1, R = 1; Insert(1);
	REP(i, 1, m)
	{
		while ( L < q[i].l ) Erase(L ++);
		while ( L > q[i].l ) Insert(-- L);
		while ( R < q[i].r ) Insert(++ R);
		while ( R > q[i].r ) Erase(R --);
		ans[q[i].id] = Tree[1].Max == R - L + 1 ? p[Tree[1].id] : -1;
	}

	REP(i, 1, m) if ( ans[i] == -1 ) puts("NO"); else printf("%d\n", ans[i]);
	return 0;
}
