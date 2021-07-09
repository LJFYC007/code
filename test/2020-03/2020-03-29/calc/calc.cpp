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

const int maxn = 2e5 + 10;
const int Mod = 1e9;

int n, m, f[maxn], a[maxn], g[maxn];
struct node { int X, Y, lazy; } Tree[maxn << 2];

inline void PushTag(int root, int l, int r, int d)
{
	Tree[root].X = (Tree[root].X + d * (1 + (r - l - 1 > 0 ? g[r - l - 2] : 0))) % Mod;
	Tree[root].Y = (Tree[root].Y + d * (r - l > 0 ? g[r - l - 1] : 0))  % Mod;
	Tree[root].lazy = (Tree[root].lazy + d) % Mod;
}

inline void PushDown(int root, int l, int r)
{
	if ( !Tree[root].lazy ) return ;
	int Mid = l + r >> 1;
	PushTag(lson, l, Mid, Tree[root].lazy);
	PushTag(rson, Mid + 1, r, Tree[root].lazy);
	Tree[root].lazy = 0;
}

inline void Modify1(int root, int l, int r, int L, int R, int d)
{
	if ( L <= l && r <= R ) { PushTag(root, l, r, d); return ; }
	PushDown(root, l, r);
	int Mid = l + r >> 1;
	if ( L <= Mid ) Modify1(lson, l, Mid, L, R, d);
	if ( Mid < R ) Modify1(rson, Mid + 1, r, L, R, d);
	if ( Mid - l > 0 ) Tree[root].X = (Tree[lson].X + Tree[rson].X * f[Mid - l - 1] + Tree[rson].Y * f[Mid - l]) % Mod;
	else Tree[root].X = Tree[lson].X;
	Tree[root].Y = (Tree[lson].Y + Tree[rson].X * f[Mid - l] + Tree[rson].Y * f[Mid - l + 1]) % Mod;
}

inline void Modify(int root, int l, int r, int pos, int val)
{
	if ( pos == l + 1 ) Tree[root].Y = (Tree[root].Y + val) % Mod;
	else if ( pos == l ) Tree[root].X = (Tree[root].X + val) % Mod;
	else
	{
		Tree[root].X = (Tree[root].X + f[pos - l - 2] * val) % Mod;
	 	Tree[root].Y = (Tree[root].Y + f[pos - l - 1] * val) % Mod;
	}
	if ( l == r ) return ;
	PushDown(root, l, r);
	int Mid = l + r >> 1;
	if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
	else Modify(rson, Mid + 1, r, pos, val);
}

inline int Query(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) return (Tree[root].X * f[l - L] + Tree[root].Y * f[l - L + 1]) % Mod;
	PushDown(root, l, r);
	int Mid = l + r >> 1, ret = 0;
	if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
	if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
	return ret % Mod;
}

signed main()
{
	freopen("calc.in", "r", stdin);
	freopen("calc.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	f[0] = f[1] = g[0] = 1;
	REP(i, 2, n) f[i] = (f[i - 1] + f[i - 2]) % Mod;
	REP(i, 1, n) g[i] = (g[i - 1] + f[i]) % Mod;
	REP(i, 1, n)
	{
		scanf("%lld", &a[i]);
		Modify(1, 1, n, i, a[i]);
	}
	REP(i, 1, m)
	{
		int op; scanf("%lld", &op);
		if ( op == 1 )
		{
			int x, y; scanf("%lld%lld", &x, &y);
			Modify(1, 1, n, x, y - Query(1, 1, n, x, x));
		}
		else if ( op == 2 )
		{
			int l, r; scanf("%lld%lld", &l, &r);
			printf("%lld\n", (Query(1, 1, n, l, r) + Mod) % Mod);
		}
		else if ( op == 3 )
		{
			int l, r, d; scanf("%lld%lld%lld", &l, &r, &d);
			Modify1(1, 1, n, l, r, d);
		}
	}
	return 0;
}
