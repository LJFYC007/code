#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, x[maxn], y[maxn], c[maxn], sa[maxn], tot, rk[maxn], h[maxn];
int w[maxn], a[maxn], ret;
struct node { int l, r; bool operator < (const node &a) const { return l < a.l || (l == a.l && r < a.r); } } ans[maxn];
struct Node1 { int val; } Tree[maxn << 4];
char s[maxn];

inline void PushDown(int root, int l, int r)
{
	if ( !Tree[root].val ) return ;
	int Mid = l + r >> 1;
	Tree[rson].val = Tree[root].val;
	Tree[lson].val = Tree[root].val + r - Mid;
	Tree[root].val = 0;
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R )
	{
		Tree[root].val = val + R - r;
		return ;
	}
	PushDown(root, l, r);
	int Mid = l + r >> 1;
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
}

inline int Query1(int root, int l, int r, int pos)
{
	if ( l == r ) return Tree[root].val;
	PushDown(root, l, r);
	int Mid = l + r >> 1;
	if ( pos <= Mid ) return Query1(lson, l, Mid, pos);
	else return Query1(rson, Mid + 1, r, pos);
}

inline bool cmp(int a, int b, int k) { return y[a] == y[b] && y[a + k] == y[b + k]; }

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) w[i] += val; }

inline int get_sum(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += w[i]; return sum; }

inline int Query(int l, int r) { return get_sum(r) - get_sum(l - 1); }

inline void Solve(int i, int L, int R, int y)
{
	int l = L, r = R, pos = L, s = sa[i];
	while ( L <= R )
	{
		int Mid = L + R >> 1, x = y == -1 ? Query1(1, 1, n, Mid - l + 1) : y - Mid + l;
		if ( Query(s, Mid) <= x ) { L = Mid + 1, pos = Mid; }
		else R = Mid - 1;
	}
	int x = pos, t = y == -1 ? Query1(1, 1, n, x - l + 1) : y - x + l;
	while ( Query(s, x) == t && x <= r )
	{
		ans[++ ret].l = s; ans[ret].r = x; ++ x;
		t = y == -1 ? Query1(1, 1, n, x - l + 1) : y - x + l;
	}
	x = pos - 1; t = y == -1 ? Query1(1, 1, n, x - l + 1) : y - x + l;
	while ( Query(s, x) == t && x >= l )
	{
		ans[++ ret].l = s; ans[ret].r = x; -- x;
		t = y == -1 ? Query1(1, 1, n, x - l + 1) : y - x + l;
	}
}

signed main()
{
	freopen("platform.in", "r", stdin);
	freopen("platform.out", "w", stdout);
	scanf("%s", s + 1); n = str(s + 1); m = 122;
	REP(i, 1, n) { x[i] = s[i]; ++ c[x[i]]; } REP(i, 1, m) c[i] += c[i - 1];
	for ( int i = n; i >= 1; -- i ) sa[c[x[i]] -- ] = i;
	for ( int k = 1; k < n; k <<= 1 )
	{
		mem(c); tot = 0;
		REP(i, n - k + 1, n) y[++ tot] = i;
		REP(i, 1, n) if ( sa[i] > k ) y[++ tot] = sa[i] - k;
		REP(i, 1, n) ++ c[x[i]]; REP(i, 1, m) c[i] += c[i - 1];
		for ( int i = n; i >= 1; -- i ) sa[c[x[y[i]]] --] = y[i];
		REP(i, 1, n) y[i] = x[i];
		x[sa[1]] = 1; tot = 1;
		REP(i, 2, n) x[sa[i]] = cmp(sa[i], sa[i - 1], k) ? tot : ++ tot;
		if ( tot == n ) break ; m = tot;
	}
	REP(i, 1, n) rk[sa[i]] = i;
	for ( int i = 1, k = 0; i <= n; ++ i )
	{
		if ( k ) -- k;
		while ( s[i + k] == s[sa[rk[i] - 1] + k] ) ++ k;
		h[rk[i]] = k;
	}
	int N = n * (n + 1) / 2, sum = 0;
	REP(i, 2, n) N -= h[i];
	REP(i, 1, n) { int x; scanf("%lld", &x); add(i, x); }
	REP(i, 1, n)
	{
		if ( h[i] < h[i + 1] )
		{
			sum += h[i + 1] - h[i];
			Modify(1, 1, n, h[i] + 1, h[i + 1], N - sum + 1);
		}
		int L = sa[i], R = sa[i] + max(h[i], h[i + 1]) - 1; Solve(i, L, R, -1);
		L = sa[i] + max(h[i], h[i + 1]); R = n; int len = R - L + 1;
		if ( L > R ) continue ; sum += len;
		Solve(i, L, R, N - sum + len);
	}
	sort(ans + 1, ans + ret + 1);
	printf("%lld\n", ret);
	REP(i, 1, ret) printf("%lld %lld\n", ans[i].l, ans[i].r);
	return 0;
}
