#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;
const int Mod = 1e9 + 7;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, size[maxn];
int p[maxn], id[maxn], tot, sum1, sum2, sum3, f[maxn];
struct node { int sum1, sum2, sum3; } Tree[maxn << 2];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
	size[u] = 1; p[u] = ++ tot; id[tot] = u;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ;
		DFS(v, u);
		size[u] += size[v];
	}
	int sum = size[u] - 1;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ;
		f[u] = (f[u] + size[v] * (sum - size[v])) % Mod;
	}
	f[u] = (f[u] * (Mod + 1) / 2) % Mod;
}

inline void PushUp(int root)
{
	Tree[root].sum1 = (Tree[lson].sum1 + Tree[rson].sum1) % Mod;
	Tree[root].sum2 = (Tree[lson].sum2 + Tree[rson].sum2) % Mod;
	Tree[root].sum3 = (Tree[lson].sum3 + Tree[rson].sum3) % Mod;
}

inline void Build(int root, int l, int r)
{
	if ( l == r )
	{
		Tree[root].sum1 = size[id[l]];
		Tree[root].sum2 = size[id[l]] * size[id[l]] % Mod;
		Tree[root].sum3 = f[id[l]];
		return ;
	}
	int Mid = l + r >> 1;
	Build(lson, l, Mid); Build(rson, Mid + 1, r);
	PushUp(root);
}

inline void Modify(int root, int l, int r, int pos, int x)
{
	if ( l == r )
	{
 		Tree[root].sum1 = (Tree[root].sum1 + x * size[id[l]]) % Mod;
		Tree[root].sum2 = (Tree[root].sum2 + (size[id[l]] * size[id[l]] % Mod) * x) % Mod;
		Tree[root].sum3 = (Tree[root].sum3 + x * f[id[l]]) % Mod;
		return ;
	}
	int Mid = l + r >> 1;
	if ( pos <= Mid ) Modify(lson, l, Mid, pos, x);
	else Modify(rson, Mid + 1, r, pos, x);
	PushUp(root);
}

inline void Query(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R )
	{
		sum1 = (sum1 + Tree[root].sum1) % Mod;
		sum2 = (sum2 + Tree[root].sum2) % Mod;
		sum3 = (sum3 + Tree[root].sum3) % Mod;
		return ;
	}
	int Mid = l + r >> 1;
	if ( L <= Mid ) Query(lson, l, Mid, L, R);
	if ( Mid < R ) Query(rson, Mid + 1, r, L, R);
}

signed main()
{
	freopen("transport.in", "r", stdin);
	freopen("transport.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
	DFS(1, 0); Build(1, 1, n);
	REP(i, 1, m)
	{
		int op; scanf("%lld", &op);
		if ( op == 1 )
		{
			int pos, x; scanf("%lld%lld", &pos, &x);
			Modify(1, 1, n, p[pos], x);
		}
		else
		{
			int x; scanf("%lld", &x);
			int L = p[x], R = p[x] + size[x] - 1;
			sum1 = sum2 = sum3 = 0; Query(1, 1, n, L, R);
			int ans = (sum1 * (size[x] + 1) - sum2 + sum3) % Mod;
			printf("%lld\n", (ans + Mod) % Mod);
		}
	}
	return 0;
}
