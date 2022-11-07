// luogu-judger-enable-o2
/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年06月03日 星期一 14时56分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
#define int long long

const int maxn = 1e6 + 10;
const int INF = 1e18;

int Begin[maxn], Next[maxn], To[maxn], e, size[maxn], id[maxn];
int dis[maxn], dfn[maxn], n, m, x, r, a[maxn], tot, anc[maxn];
bool vis[maxn];
vector<int> ans;
map<int, int> Map[maxn];

struct node
{
    int Max, lazy, id;
} Tree[maxn * 2];

inline void Push_up(int root) 
{ 
	if ( Tree[lson].Max > Tree[rson].Max ) Tree[root].id = Tree[lson].id;
	else Tree[root].id = Tree[rson].id;
	Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
}

inline void Push_down(int root)
{
	if ( !Tree[root].lazy ) return ;
    Tree[lson].lazy = (Tree[lson].lazy + Tree[root].lazy);
    Tree[rson].lazy = (Tree[rson].lazy + Tree[root].lazy);
    Tree[lson].Max = (Tree[lson].Max + Tree[root].lazy);
    Tree[rson].Max = (Tree[rson].Max + Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) 
    {
        Tree[root].Max = (Tree[root].Max + val) ;
        Tree[root].lazy = (Tree[root].lazy + val);
        return ;
    }
    Push_down(root);
	int Mid = l + r >> 1;
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    Push_up(root);
}

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS(int u, int fa)
{
	dfn[u] = ++ tot; size[u] = 1; id[tot] = u;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		anc[v] = u;
		dis[v] = dis[u] + 1; DFS(v, u); size[u] += size[v];
	}
	if ( u != r ) Modify(1, 1, n, dfn[u], dfn[u] + size[u] - 1, a[u] - x);
}

inline void Build(int root, int l, int r)
{
	Tree[root].id = l; 
	if ( l == r ) return ;
	int Mid =l  + r>> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &x);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); Map[u][v] = Map[v][u] = i; }
	REP(i, 1, n) if ( a[i] > a[r] ) r = i;
	Build(1, 1, n);
	Modify(1, 1, n, 1, 1, -INF);
	DFS(r, 0); vis[r] = true;
	int sum = a[r];
	while ( Tree[1].Max > -INF / 2 ) 
	{
		if ( Tree[1].Max + sum < 0 ) { puts("NO"); return 0; } 
		sum += Tree[1].Max; int u = id[Tree[1].id];
		cerr << Tree[1].Max << " " << id[Tree[1].id] << endl;
		vector<int> p; p.push_back(u);
		while ( !vis[u] ) 
		{
			Modify(1, 1, n, dfn[u], dfn[u] + size[u] - 1, x - a[u]);
			Modify(1, 1, n, dfn[u], dfn[u], -INF);
			vis[u] = true; u = anc[u]; p.push_back(u);
		}
		while ( p.size() >= 2 ) 
		{
			int k = p.size();
			ans.push_back(Map[p[k - 1]][p[k - 2]]);
			p.pop_back();
		}
	}
	puts("YES");
	for ( auto it : ans ) printf("%d\n", it);
    return 0;
}