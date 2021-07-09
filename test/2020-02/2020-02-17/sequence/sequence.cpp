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

const int maxn = 1e5 + 10;

int n, k, m, a[maxn], f[maxn][31], tot, ans[maxn * 5];
struct node { int sum, lazy; } Tree[maxn << 3];
vector<pii> p[maxn], p1[maxn];
struct node1 { int l, r, id; bool operator < (const node1 &a) const { return l < a.l; } } q[maxn * 5];

inline void PushTag(int root, int l, int r, int val)
{
	Tree[root].lazy += val;
	Tree[root].sum += val * (r - l + 1);
}

inline void PushUp(int root) { Tree[root].sum = Tree[lson].sum + Tree[rson].sum; }

inline void PushDown(int root, int l, int r)
{
	if ( !Tree[root].lazy ) return ;
	int x = Tree[root].lazy; Tree[root].lazy = 0;
	int Mid = l + r >> 1;
	PushTag(lson, l, Mid, x); PushTag(rson, Mid + 1, r, x);
}

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
	if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
	if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
	return ret;
}

inline int GetNext(int sum, int pos)
{
	int Min = n + 1;
	REP(i, 0, 29) if ( (sum >> i) & 1 ) Min = min(Min, f[pos][i]);
	return Min;
}

signed main()
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &k);
	REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 0, 29) f[n + 1][i] = n + 1;
	for ( int i = n; i >= 1; -- i ) REP(j, 0, 29)
		if ( (a[i + 1] >> j) & 1 ) f[i][j] = f[i + 1][j];
		else f[i][j] = i + 1;
	REP(i, 1, n)
	{
		int last = i, sum = a[i], x = GetNext(sum, i);
		while ( x <= n )
		{
			if ( sum % k == 0 ) p[i].push_back(pii(last, x - 1));
			sum &= a[x]; last = x; x = GetNext(sum, last);
		}
		if ( x > n ) x = n + 1;
		if ( sum % k == 0 ) p[i].push_back(pii(last, x - 1));
	}
	REP(o, 1, n)
	{
		if ( !p[o].size() ) continue ;
		for ( int i = 0, j; i < p[o].size(); i = j )
		{
			j = i + 1; int R = p[o][i].second;
			while ( j < p[o].size() && p[o][j].first == R + 1 )
			{
				R = p[o][j].second; ++ j;
			}
			p1[o].push_back(pii(p[o][i].first, R));
			Modify(1, 1, n, p[o][i].first, R, 1);
		}
	}
	REP(i, 1, m) { scanf("%lld%lld", &q[i].l, &q[i].r); q[i].id = i; }
	sort(q + 1, q + m + 1);
	int now = 1;
	REP(i, 1, n)
	{
		while ( q[now].l <= i && now <= m )
		{
			ans[q[now].id] = Query(1, 1, n, q[now].l, q[now].r);
			++ now;
		}
		if ( p[i].size() )
		{
			REP(j, 0, p1[i].size() - 1) Modify(1, 1, n, p1[i][j].first, p1[i][j].second, -1);
		}
	}
	REP(i, 1, m) printf("%lld\n", ans[i]); puts("");
	return 0;
}
