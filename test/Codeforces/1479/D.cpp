/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2021年02月08日 星期一 15时41分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;

int n, q, a[maxn], c[maxn], Begin[maxn], Next[maxn], To[maxn], e, Root[maxn], anc[maxn][20], dis[maxn], tot;
struct node { int lson ,rson, sum; } Tree[maxn << 5];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline int Modify(int now, int l, int r, int pos)
{
	int root = ++ tot; Tree[root] = Tree[now];
	if ( l == r ) { Tree[root].sum ^= c[l]; return root; } 
	int Mid = l + r >> 1;
	if ( pos <= Mid ) ls(root) = Modify(ls(root), l, Mid, pos);
	else rs(root) = Modify(rs(root), Mid + 1, r, pos);
	Tree[root].sum = Tree[ls(root)].sum ^ Tree[rs(root)].sum;
	return root;
}

inline int Get(int p, int q, int L, int R, int val)
{
	int ret = Tree[p].sum ^ Tree[q].sum;
	if ( L <= val && val <= R ) ret ^= c[val];
	return ret;
}

inline int Query(int p, int q, int l, int r, int L, int R, int val)
{
	if ( !p && !q ) return -1;
	if ( L <= l && r <= R ) 
	{
		if ( l == r ) return Get(p, q, l, r, val) ? l : -1;
		int Mid = l + r >> 1;
		if ( Get(ls(p), ls(q), l, Mid, val) ) return Query(ls(p), ls(q), l, Mid, L, R, val);
		return Query(rs(p), rs(q), Mid + 1, r, L, R, val);;
	}
	int Mid = l + r >> 1;
	if ( L <= Mid ) { int x = Query(ls(p), ls(q), l, Mid, L, R, val); if ( x != -1 ) return x; }
	if ( Mid < R ) { int x = Query(rs(p), rs(q), Mid + 1, r, L, R, val); if ( x != -1 ) return x; }
	return -1;
}

inline void DFS(int u, int fa)
{
	Root[u] = Modify(Root[u], 1, n, a[u]);
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ;
		anc[v][0] = u; dis[v] = dis[u] + 1; Root[v] = Root[u]; DFS(v, u);
	}
}

inline int LCA(int x, int y)
{
	if ( dis[x] < dis[y] ) swap(x, y);
	for ( int j = 18; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
	if ( x == y ) return x;
	for ( int j = 18; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; } 
	return anc[x][0];
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &q); srand(time(0));
	REP(i, 1, n) { c[i] = (rand() << 32) ^ (rand() << 16) ^ (rand() << 8); scanf("%lld", &a[i]); }
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); } 
	dis[1] =1 ; DFS(1, 0); REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	REP(i, 1, q)
	{
		int u, v, l, r; scanf("%lld%lld%lld%lld", &u, &v, &l, &r);		
		int t = a[LCA(u, v)];			
		printf("%lld\n", Query(Root[u], Root[v], 1, n, l, r, t));
	}
    return 0;
}
