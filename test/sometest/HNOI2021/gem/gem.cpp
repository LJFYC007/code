#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen (a)
#define pii pair<int, int>

const int maxn = 4e5 + 10;

int n, m, q, c, p[maxn], w[maxn], belong[maxn], Begin[maxn], Next[maxn], To[maxn], e;
int S, ROOT, size[maxn], f[maxn], g[maxn], ans[maxn], lst[maxn], tot, Root[maxn];
bool vis[maxn], use[maxn];
vector<pii> Q[maxn], a[maxn];
struct node { int lson, rson, Max; } Tree[maxn << 5];

#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson

inline int Modify(int now, int l, int r, int pos, int val)
{
	int root = ++ tot; Tree[root] = Tree[now]; Tree[root].Max = max(Tree[root].Max, val); 
	if ( l == r ) return root;
	int Mid = l + r >> 1;
	if ( pos <= Mid ) ls(root) = Modify(ls(root), l, Mid, pos, val);
	else rs(root) = Modify(rs(root), Mid + 1, r, pos, val);
	return root;
}

inline int Query(int root, int l, int r, int pos)
{
	if ( !root || l == r ) return Tree[root].Max;
	int Mid = l + r >> 1;
	if ( pos <= Mid ) return Query(ls(root), l, Mid, pos);
	return max(Tree[ls(root)].Max, Query(rs(root), Mid + 1, r, pos));
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void Get(int u, int fa)
{
	size[u] = 1; int Max = 0;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa || vis[v] ) continue ;
		Get(v, u); size[u] += size[v]; Max = max(Max, size[v]);
	}
	if ( max(Max, S - size[u]) <= S / 2 ) ROOT = u;
}

inline void DFS(int u, int fa, bool col)
{
	use[u] = col; 
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa || vis[v] ) continue ;
		DFS(v, u, col);
	}
}

inline void Find(int u, int fa, int Max)
{
	if ( belong[w[u]] == 1 ) Max = f[u];
	for ( int i = 0; i < Q[u].size(); ++ i ) 
	{
		int x = Q[u][i].first;
		if ( use[x] ) a[x].push_back(pii(Max, Q[u][i].second));
	}
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa || vis[v] ) continue ;
		Find(v, u, Max);
	}
}

inline void calc(int u, int fa)
{
	int x = lst[w[u]]; lst[w[u]] = u;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa || vis[v] ) continue ;
		if ( belong[w[v]] ) 
		{
			f[v] = f[lst[p[belong[w[v]] + 1]]] + 1;
			g[v] = g[lst[p[belong[w[v]] - 1]]] + 1;
		}
		else f[v] = g[v] = 0; 
		calc(v, u);
	}
	lst[w[u]] = x;
}

inline void Fucku(int u, int fa)
{
	if ( belong[w[u]] ) Root[u] = Modify(Root[u], 0, m, belong[w[u]] - g[u], belong[w[u]]);
	for ( int i = 0; i < a[u].size(); ++ i )
		ans[a[u][i].second] = max(a[u][i].first, Query(Root[u], 0, m, a[u][i].first));
	size[u] = 1; a[u].clear();
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa || vis[v] ) continue ;
		Root[v] = Root[u]; Fucku(v, u); size[u] += size[v];
	}
}

inline void Solve(int u)
{
	f[u] = 0; g[u] = (belong[w[u]] != 0); calc(u, 0); DFS(u, 0, 1); 
	for ( int i = 0; i < Q[u].size(); ++ i ) if ( use[Q[u][i].first] ) 
		a[Q[u][i].first].push_back(pii(0, Q[u][i].second));
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( vis[v] ) continue ; 
		DFS(v, u, 0); Find(v, u, 0); DFS(v, u, 1);
	}
	DFS(u, 0, 0); tot = Root[u] = 0; Fucku(u, 0);

	vis[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( vis[v] ) continue ;
		S = size[v]; Get(v, 0); Solve(ROOT);
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &c);
	REP(i, 1, c) { scanf("%d", &p[i]); belong[p[i]] = i; }
	REP(i, 1, n) scanf("%d", &w[i]);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
	scanf("%d", &q); 
	REP(i, 1, q) { int u, v; scanf("%d%d", &u, &v); Q[u].push_back(pii(v, i)); }	
	S = n; Get(1, 0); Solve(ROOT);
	REP(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
