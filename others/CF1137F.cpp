/***************************************************************
	File name: CF1137F.cpp
	Author: ljfcnyali
	Create time: 2021年04月26日 星期一 19时43分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].son[0]
#define rs(x) Tree[x].son[1]
#define fa(x) Tree[x].fa
typedef long long LL;

const int maxn = 4e5 + 10;

int n, q, Begin[maxn], Next[maxn], To[maxn], e, c[maxn], anc[maxn], Root;
bool vis[maxn]; char s[maxn];
struct node { int son[2], fa, size, id, lazy; bool tag; } Tree[maxn];

inline int lowbit(int x) { return x & -x; } 
inline void modify(int pos, int val) { for ( int i = pos; i < maxn; i += lowbit(i) ) c[i] += val; } 
inline int query(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i]; return sum; } 
inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline bool IsRoot(int root) { return ls(fa(root)) != root && rs(fa(root)) != root; }
inline void PushTag(int root) { if ( !root ) return ; swap(ls(root), rs(root)); Tree[root].tag ^= 1; } 
inline void Maintain(int root, int val) { if ( !root ) return ; Tree[root].id = Tree[root].lazy = val; } 
inline void PushDown(int root)
{
	if ( Tree[root].tag ) { PushTag(ls(root)); PushTag(rs(root)); Tree[root].tag ^= 1; } 
	if ( Tree[root].lazy ) { Maintain(ls(root), Tree[root].lazy); Maintain(rs(root), Tree[root].lazy); Tree[root].lazy = 0; } 
}
inline void PushUp(int root) { Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1; }
inline void Get(int root) { if ( !IsRoot(root) ) Get(fa(root)); PushDown(root); } 
inline void Rotate(int x)
{
	int y = fa(x), z = fa(y), k = rs(y) == x, w = Tree[x].son[!k];
	if ( !IsRoot(y) ) Tree[z].son[rs(z) == y] = x; if ( w ) fa(w) = y;
	fa(x) = z; fa(y) = x; Tree[x].son[!k] = y; Tree[y].son[k] = w;
	PushUp(y); PushUp(x);
}
inline void Splay(int x)
{
	Get(x);
	while ( !IsRoot(x) ) 
	{
		int y = fa(x), z = fa(y);
		if ( !IsRoot(y) ) Rotate((ls(y) == x) ^ (ls(z) == y) ? x : y);
		Rotate(x);
	}
}
inline void Access(int root)
{
	for ( int x = 0; root; x = root, root = fa(root) ) 
	{
		Splay(root); PushDown(root);
		modify(Tree[root].id, -Tree[ls(root)].size - 1);
		rs(root) = x; PushUp(root);
	}
}
inline int ask(int v) { Splay(v); PushDown(v); return Tree[rs(v)].size + 1 + query(Tree[v].id - 1); }

inline void DFS(int u, int fa)
{
	anc[u] = fa;
	for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) DFS(To[i], u);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &q); REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
	DFS(n, 0); vis[0] = true;
	for ( int i = n; i >= 1; -- i ) if ( !vis[i] ) 
	{
		int x = i, num = 0;	
		while ( !vis[x] ) 
		{ 
			vis[x] = true; ++ num; fa(x) = anc[x];
			if ( !vis[anc[x]] ) rs(anc[x]) = x; 
			PushUp(x); Tree[x].id = i; x = anc[x]; 
		} 
		modify(i, num); 
	}

	while ( q -- ) 
	{
		scanf("%s", s + 1); int u, v;
		if ( s[1] == 'u' ) 
		{
			scanf("%d", &v); Access(v); Splay(v); PushTag(v);
			++ n; modify(n, Tree[v].size); Maintain(v, n); Root = v;
		}
		if ( s[1] == 'w' ) { scanf("%d", &v); printf("%d\n", ask(v)); }
		if ( s[1] == 'c' ) { scanf("%d%d", &u, &v); printf("%d\n", ask(u) < ask(v) ? u : v); }
	}
    return 0;
}
