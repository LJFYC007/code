#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int block = 256;

int n, m, a[maxn], Begin[maxn], Next[maxn], To[maxn], e;
int dis[maxn], tot, f[maxn][block], anc[maxn], F[maxn];
struct node { int son[2]; } Tree[maxn];

inline void Insert(int x)
{
	int p = 1;
	for ( int i = 18; i >= 0; -- i )
	{
		int c = (x >> i) & 1;
		if ( !Tree[p].son[c] ) Tree[p].son[c] = ++ tot;
		p = Tree[p].son[c];
	}
}

inline int Query(int x)
{
	int ret = 0, p = 1;
	for ( int i = 18; i >= 0; -- i )
	{
		int c = (x >> i) & 1;
		if ( Tree[p].son[c ^ 1] ) { ret |= 1 << i; c ^= 1; }
		p = Tree[p].son[c];
	}
	return ret;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ;
		dis[v] = dis[u] + 1; F[v] = u;
		DFS(v, u);
	}
	if ( dis[u] >= block )
	{
		REP(i, 1, tot) Tree[i].son[0] = Tree[i].son[1] = 0; tot = 1;
		int x = u; Insert(a[x]);
		REP(i, 1, block - 1) { x = F[x]; Insert(a[x] ^ i); }
		anc[u] = x;
		REP(i, 0, block - 1) f[u][i] = Query(i << 8);
	}
}

int main()
{
	freopen("food.in", "r", stdin);
	freopen("food.out", "w", stdout);
	scanf("%d%d", &n, &m);
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	dis[1] = 1; DFS(1, 0);
	REP(o, 1, m)
	{
		int u, v; scanf("%d%d", &u, &v);
		int ans = 0, x = 0;
		for ( x = 0; dis[anc[v]] >= dis[u]; ++ x )
		{
			ans = max(ans, f[v][x]);
			v = F[anc[v]];
		}
		x *= block;
		while ( dis[v] >= dis[u] ) { ans = max(ans, a[v] ^ x); ++ x; v = F[v]; }
		printf("%d\n", ans);
	}
	return 0;
}
