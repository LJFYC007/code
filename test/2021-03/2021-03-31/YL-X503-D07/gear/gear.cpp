#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define pdd pair<double, double>
#define x first
#define y second

const int maxn = 2e5 + 10;
const double pi = acos(-1);

int n, m, Begin[maxn], Next[maxn], To[maxn], e, fa[maxn], dis[maxn];
int size[maxn], son[maxn], top[maxn], p[maxn], id[maxn], tot;
pdd a[maxn], s;
struct node { pdd sum; double theta; } Tree[maxn << 2];

pdd operator + (pdd a, pdd b) { return pdd(a.x + b.x, a.y + b.y); } 
pdd operator - (pdd a, pdd b) { return pdd(a.x - b.x, a.y - b.y); } 
inline double len(pdd a) { return sqrt(a.x * a.x + a.y * a.y); }
inline pdd change(pdd a, double theta) { return pdd(a.x * cos(theta) - a.y * sin(theta), a.x * sin(theta) + a.y * cos(theta)); }
inline pdd Merge(pdd a, pdd b, double theta) { return a + change(b, theta); }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS1(int u)
{
	size[u] = 1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; dis[v] = dis[u] + 1;
		DFS1(v); size[u] += size[v]; if ( size[v] > size[son[u]] ) son[u] = v;
	}
}

inline void DFS2(int u, int t)
{
	id[++ tot] = u; p[u] = tot; top[u] = t;
	if ( son[u] ) DFS2(son[u], t);
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa[u] || v == son[u] ) continue ; 
		DFS2(v, v);
	}
}

#define lson root << 1
#define rson root << 1 | 1

inline void PushUp(int root) 
{
	Tree[root].theta = Tree[lson].theta + Tree[rson].theta;
	if ( Tree[root].theta > pi + pi ) Tree[root].theta -= pi + pi;
	Tree[root].sum = Merge(Tree[lson].sum, Tree[rson].sum, Tree[lson].theta);
}

inline void Build(int root, int l, int r)
{
	if ( l == r ) { Tree[root].sum = a[id[l]]; Tree[root].theta = atan2(a[id[l]].y, a[id[l]].x) + pi; return ; } 
	int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
	PushUp(root);
}

inline void Modify(int root, int l, int r, int pos)
{
	if ( l == r ) { Tree[root].sum = a[id[l]]; Tree[root].theta = atan2(a[id[l]].y, a[id[l]].x) + pi; return ; } 
	int Mid = l + r >> 1;
	if ( pos <= Mid ) Modify(lson, l, Mid, pos);
	else Modify(rson, Mid + 1, r, pos);
	PushUp(root);
}

inline void Query(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) { s = Merge(Tree[root].sum, s, Tree[root].theta); return ; } 
	int Mid = l + r >> 1;
	if ( Mid < R ) Query(rson, Mid + 1, r, L, R);
	if ( L <= Mid ) Query(lson, l, Mid, L, R);
}

inline pdd Get(int x)
{
	s = pdd(0, 0);
	while ( x ) { Query(1, 1, n, p[top[x]], p[x]); x = fa[top[x]]; }
	return s;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("gear.in", "r", stdin);
	freopen("gear.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 2, n) { scanf("%d", &fa[i]); add(fa[i], i); }
	REP(i, 1, n) a[i] = pdd(-1, 0);
	dis[1] = 1; DFS1(1); DFS2(1, 1); Build(1, 1, n);
	while ( m -- ) 
	{
		int op, x, y; scanf("%d%d%d", &op, &x, &y);
		if ( op == 1 ) 
		{
			double theta = y / 180.0 * pi;
			a[x] = change(a[x], theta);
			Modify(1, 1, n, p[x]);
		}
		else printf("%.6lf\n", len(Get(x) - Get(y)));
	}
	return 0;
}
