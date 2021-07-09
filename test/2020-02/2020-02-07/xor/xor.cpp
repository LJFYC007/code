#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int unsigned int
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 300010;

int n, m, a[maxn], sum[maxn], ans[maxn];
map<int, int> Map;
struct node1 { int l, r, id; bool operator < (const node1 &a) const { return r < a.r;} } q[maxn];
struct node2 { int lazy; } Tree[maxn << 4];

inline void PushDown(int root)
{
	if ( !Tree[root].lazy ) return ;
	Tree[lson].lazy ^= Tree[root].lazy;
	Tree[rson].lazy ^= Tree[root].lazy;
	Tree[root].lazy = 0;
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) { Tree[root].lazy ^= val; return ; }
	PushDown(root);
	int Mid = l + r >> 1;
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
}

inline int Query(int root, int l, int r, int pos)
{
	if ( l == r ) return Tree[root].lazy;
	PushDown(root);
	int Mid = l + r >> 1;
	if ( pos <= Mid ) return Query(lson, l, Mid, pos);
	return Query(rson, Mid + 1, r, pos);
}

signed main()
{
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	scanf("%u", &n);
	REP(i, 1, n)
	{
		scanf("%u", &a[i]);
		sum[i] = sum[i - 1] ^ a[i];
	}
	scanf("%u", &m);
	REP(i, 1, m) { q[i].id = i; scanf("%u%u", &q[i].l, &q[i].r); }
	sort(q + 1, q + m + 1);
	int now = 1;
	REP(i, 1, n)
	{
		int last = Map[a[i]] + 1; Map[a[i]] = i;
		Modify(1, 1, n, last, i, a[i]);
		while ( q[now].r == i )
		{
			int ret = sum[q[now].r] ^ sum[q[now].l - 1];
			ans[q[now].id] = ret ^ Query(1, 1, n, q[now].l);
			++ now;
		}
	}
	REP(i, 1, m) printf("%u\n", ans[i]);
	return 0;
}
