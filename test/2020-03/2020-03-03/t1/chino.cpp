#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define lson root << 1
#define rson root << 1 | 1
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e18;

int n, a[maxn], b[maxn], ans;
vector<int> d[maxn], p[maxn];
struct node { int Min, Se, sum, num, lazy; } Tree[maxn << 2];

inline void PushUp(int root)
{
	Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
	if ( Tree[lson].Min == Tree[rson].Min )
	{
		Tree[root].Min = Tree[lson].Min;
		Tree[root].num = Tree[lson].num + Tree[rson].num;
		Tree[root].Se = min(Tree[lson].Se, Tree[rson].Se);
	}
	if ( Tree[lson].Min < Tree[rson].Min )
	{
		Tree[root].Min = Tree[lson].Min; Tree[root].num = Tree[lson].num;
		Tree[root].Se = min(Tree[lson].Se, Tree[rson].Min);
	}
	if ( Tree[lson].Min > Tree[rson].Min )
	{
		Tree[root].Min = Tree[rson].Min; Tree[root].num = Tree[rson].num;
		Tree[root].Se = min(Tree[lson].Min, Tree[rson].Se);
	}
}

inline void PushTag(int root, int val)
{
	if ( val <= Tree[root].Min ) return ;
	Tree[root].sum += Tree[root].num * (val - Tree[root].Min);
	Tree[root].Min = Tree[root].lazy = val;
}

inline void PushDown(int root)
{
	if ( !Tree[root].lazy ) return ;
	PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
	Tree[root].lazy = 0;
}

inline void Build(int root, int l, int r)
{
	if ( l == r ) { Tree[root].Min = Tree[root].sum = l; Tree[root].Se = INF; Tree[root].num = 1; return ; }
	int Mid = l + r >> 1;
	Build(lson, l, Mid); Build(rson, Mid + 1, r);
	PushUp(root);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L > R ) return ;
	if ( val <= Tree[root].Min ) return ;
	if ( L <= l && r <= R && val <= Tree[root].Se ) { PushTag(root, val); return ; }
	PushDown(root); int Mid = l + r >> 1;
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
	PushUp(root);
}

inline int Query(int root, int l, int r, int pos)
{
	if ( l == r ) return Tree[root].Min;
	PushDown(root); int Mid = l + r >> 1;
	if ( pos <= Mid ) return Query(lson, l, Mid, pos);
	return Query(rson, Mid + 1, r, pos);
}

signed main()
{
	freopen("chino.in", "r", stdin);
	freopen("chino.out", "w", stdout);
	scanf("%lld", &n);
	REP(i, 1, n)
	{
		scanf("%lld", &a[i]);
		p[a[i]].push_back(i);
	}
	int N = 200000;
	REP(i, 1, N)
	{
		for ( int j = i; j <= N; j += i ) if ( p[j].size() ) d[i].insert(d[i].end(), p[j].begin(), p[j].end());
		sort(d[i].begin(), d[i].end());
	}
	Build(1, 1, n);
	for ( int i = N; i >= 0; -- i )
	{
		b[i] = n * (n + 1) - Tree[1].sum;
		if ( d[i].size() <= 1 ) continue ;
		int l1 = d[i][0], l2 = d[i][1], r2 = d[i][d[i].size() - 2], r1 = d[i][d[i].size() - 1];
		Modify(1, 1, n, l2 + 1, n, n + 1);
		Modify(1, 1, n, l1 + 1, l2, r1);
		Modify(1, 1, n, 1, l1, r2);
	}
	REP(i, 1, N) ans += (b[i] - b[i - 1]) * i;
	printf("%lld\n", ans);
	return 0;
}
