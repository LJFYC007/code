/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define son(x) Tree[x].son[c]
typedef long long LL;

const int maxn = 2e6 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, q, dis[maxn], anc[maxn][20];
int Root[maxn], tot = 1; vector<LL> p;
LL a[maxn], ans;
struct node { int sum, son[2]; } Tree[maxn << 6];

inline int Modify(int now, int dep, LL val)
{
	int root = ++ tot; Tree[root] = Tree[now]; ++ Tree[root].sum;
	if ( dep == -1 ) return root;
	int c = (val >> dep) & 1;
	Tree[root].son[c] = Modify(Tree[root].son[c], dep - 1, val);
	return root;
}

inline void Find(int A, int B, int C, int D, int dep, LL val)
{
	int num = Tree[A].sum + Tree[B].sum - Tree[C].sum - Tree[D].sum;
	if ( num == 0 ) return ; 
	if ( dep == -1 ) { REP(i, 1, num) p.push_back(val); return; } // cerr << val << endl; return ; }
	int c = 0; Find(son(A), son(B), son(C), son(D), dep - 1, val << 1);
	c = 1; Find(son(A), son(B), son(C), son(D), dep - 1, (val << 1) | 1);
}

inline void Query(int A, int B, int C, int D, int dep, int m)
{
	if ( dep == -1 ) return ;
	int sum = p.size() + Tree[A].sum + Tree[B].sum - Tree[C].sum - Tree[D].sum;
	//cerr << A << " " << B << " " << C << " " << D << " " << dep << " " << sum << endl;
	int c = 1, num = Tree[son(A)].sum + Tree[son(B)].sum - Tree[son(C)].sum - Tree[son(D)].sum;
	vector<LL> q; for ( auto it : p ) if ( (it >> dep) & 1 ) { q.push_back(it); ++ num; }
	if ( num >= m ) { ans = (ans << 1) | 1; p = q; Query(son(A), son(B), son(C), son(D), dep - 1, m); return ; }
	ans = (ans << 1);

	Find(son(A), son(B), son(C), son(D), dep - 1, ans | 1);
	c = 0; Query(son(A), son(B), son(C), son(D), dep - 1, m); 
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
	if ( n <= 100000 ) Root[u] = Modify(Root[fa], 61, a[u]);
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		dis[v] = dis[u] + 1; 
		DFS(v, u); anc[v][0] = u;
	}
}

inline int LCA(int x, int y)
{
	if ( dis[x] < dis[y] ) swap(x, y);
	for ( int j = 19; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
	if ( x == y ) return x;
	for ( int j = 19; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
	return anc[x][0];
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
	REP(i, 1, n) scanf("%lld", &a[i]);
	dis[1] = Root[0] = 1; DFS(1, 0); REP(j, 1, 19) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	scanf("%d", &q);
	if ( n > 100000 ) 
	{
		while ( q -- ) 
		{
			int u, v, m; scanf("%d%d%d", &u, &v, &m);
			u = (u ^ ans) % n + 1; v = (v ^ ans) % n + 1;
			int t = LCA(u, v); ans = 0;
			p.clear(); p.push_back(a[t]);
			while ( u != t ) { p.push_back(a[u]); u = anc[u][0]; } 
			while ( v != t ) { p.push_back(a[v]); v = anc[v][0]; } 

			for ( int i = 61; i >= 0; -- i ) 
			{
				vector<LL> q; ans <<= 1;
				for ( auto it : p ) if ( (it >> i) & 1 ) q.push_back(it); 
				if ( q.size() >= m ) { ++ ans; p = q; }
			}
		
			printf("%lld\n", ans);
		}
		return 0;
	}
	while ( q -- ) 
	{
		int u, v, m; scanf("%d%d%d", &u, &v, &m);
		u = (u ^ ans) % n + 1; v = (v ^ ans) % n + 1;
		int t = LCA(u, v); p.clear(); ans = 0;
		Query(Root[u], Root[v], Root[t], Root[anc[t][0]], 61, m);
		printf("%lld\n", ans);
	}
    return 0;
}
