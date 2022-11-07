#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 200010;
const int N = 200000;

int n, k, ans, p[maxn];
struct Node
{
	int l, r, id;
	bool operator < (const Node &a) const { return r < a.r; }
} a[maxn];
struct node
{
	int Max, lazy;
} Tree[maxn << 2];

inline void PushUp(int root) { Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max); }

inline void PushDown(int root)
{
	if ( !Tree[root].lazy ) return ;
	int x = Tree[root].lazy; Tree[root].lazy = 0;
	Tree[lson].lazy += x; Tree[rson].lazy += x;
	Tree[lson].Max += x; Tree[rson].Max += x;
}

inline void Modify(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) { ++ Tree[root].lazy; ++ Tree[root].Max; return ; }
	PushDown(root);
	int Mid = l + r >> 1;
	if ( L <= Mid ) Modify(lson, l, Mid, L, R);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R);
	PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) return Tree[root].Max;
	PushDown(root);
	int Mid = l + r >> 1, Max = 0;
	if ( L <= Mid ) Max = max(Max, Query(lson, l, Mid, L, R));
	if ( Mid < R ) Max = max(Max, Query(rson, Mid + 1, r, L, R));
	return Max;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	REP(i, 1, n)
	{
		scanf("%d%d", &a[i].l, &a[i].r);
		a[i].id = i;
	}
	sort(a + 1, a + n + 1);
	REP(i, 1, n)
	{
		int x = Query(1, 1, N, a[i].l, a[i].r);
		if ( x >= k ) { p[++ ans] = a[i].id; continue ; }
		Modify(1, 1, N, a[i].l, a[i].r);
	}
	printf("%d\n", ans);
	REP(i, 1, ans) printf("%d ", p[i]);
	puts("");
	return 0;
}
