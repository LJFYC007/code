/***************************************************************
	File name: UOJ207.cpp
	Author: ljfcnyali
	Create time: 2021年03月26日 星期五 20时33分18秒
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

const int maxn = 1e6 + 10;

int n, m, type, k, num; LL b[maxn], ans;
struct node { int son[2], fa, tag; LL lazy, val; } Tree[maxn];
map<int, int> Map[maxn];
pii a[maxn];

inline bool IsRoot(int x) { return ls(fa(x)) != x && rs(fa(x)) != x; }
inline void PushTag1(int root) { if ( !root ) return ; swap(ls(root), rs(root)); Tree[root].tag ^= 1; } 
inline void PushTag2(int root, LL val) { if ( !root ) return ; Tree[root].lazy ^= val; Tree[root].val ^= val; } 
inline void PushDown(int root)
{
	if ( Tree[root].tag ) { PushTag1(ls(root)); PushTag1(rs(root)); Tree[root].tag ^= 1; } 
	if ( Tree[root].lazy ) 
	{
		PushTag2(ls(root), Tree[root].lazy);
		PushTag2(rs(root), Tree[root].lazy);
		Tree[root].lazy = 0;
	}
}
inline void Maintain(int root) { if ( !IsRoot(root) ) Maintain(fa(root)); PushDown(root); } 

inline void Rotate(int x)
{
	int y = fa(x), z = fa(y), k = rs(y) == x, w = Tree[x].son[!k];
	if ( !IsRoot(y) ) Tree[z].son[rs(z) == y] = x; 
	fa(x) = z; fa(y) = x; if ( w ) fa(w) = y;
	Tree[y].son[k] = w; Tree[x].son[!k] = y;
}

inline void Splay(int x)
{
	Maintain(x); 
	while ( !IsRoot(x) ) 
	{
		int y = fa(x), z = fa(y);
		if ( !IsRoot(y) ) Rotate((ls(y) == x) ^ (ls(z) == y) ? x : y);
		Rotate(x);
	}
}

inline void Access(int root) { for ( int x = 0; root; x = root, root = fa(root) ) { Splay(root); rs(root) = x; } }
inline void MakeRoot(int root) { Access(root); Splay(root); PushTag1(root); } 
inline void Link(int u, int v) { MakeRoot(u); MakeRoot(v); fa(v) = u; }
inline void Split(int u, int v) { MakeRoot(u); Access(v); Splay(v); } 
inline void Cut(int u, int v) { Split(u, v); ls(v) = fa(u) = 0; }

inline LL Rand() { return 1ll * rand() * rand(); }
inline LL RAND()
{
	unsigned long long x = (Rand() << 5) ^ (Rand() >> 23) ^ (Rand() >> 36) ^ (Rand() << 47);
	return (long long)x;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	srand(time(0));
	scanf("%d", &type); scanf("%d%d", &n, &m); k = n;
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); ++ k; Link(u, k); Link(k, v); Map[u][v] = Map[v][u] = k; } 
	while ( m -- ) 
	{
		scanf("%d", &type);
		if ( type == 1 ) 
		{
			int u, v, x, y; scanf("%d%d%d%d", &u, &v, &x, &y);
			int id = Map[u][v]; Map[u][v] = Map[v][u] = 0;
			MakeRoot(id); LL val = Tree[id].val; Cut(u, id); Cut(id, v);
			++ k; Link(x, k); Link(k, y); Map[x][y] = Map[y][x] = k; Split(u, v); PushTag2(v, val);
		}
		if ( type == 2 ) 
		{
			int x, y; scanf("%d%d", &x, &y); a[++ num] = pii(x, y); b[num] = RAND();
			ans ^= b[num]; Split(x, y); PushTag2(y, b[num]);
		}
		if ( type == 3 ) { int x; scanf("%d", &x); ans ^= b[x]; Split(a[x].first, a[x].second); PushTag2(a[x].second, b[x]); }
		if ( type == 4 ) 
		{
			int x, y; scanf("%d%d", &x, &y); int id = Map[x][y];
			MakeRoot(id); if ( Tree[id].val == ans ) puts("YES"); else puts("NO");
		}
	}
    return 0;
}
