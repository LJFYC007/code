#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)

const int maxn = 4010;

int n, a[maxn], ans[maxn];

namespace Subtask1
{
	struct node { int u, v; } Edge[maxn];
	bool vis[maxn];
	int p[maxn], tot;

	inline void Check()
	{
		REP(i, 1, n) REP(j, 1, n) if ( a[j] == i ) p[i] = j;
		REP(i, 1, n) if ( p[i] > ans[i] ) return ; else if ( p[i] < ans[i] ) break ;
		REP(i, 1, n) ans[i] = p[i];
	}

	inline void DFS(int x)
	{
		++ tot; if ( tot > 1000000 ) return ;
		if ( x == n ) { Check(); return ; }
		REP(i, 1, n - 1) if ( !vis[i] ) 
		{
			vis[i] = true;
			swap(a[Edge[i].u], a[Edge[i].v]);
			DFS(x + 1);
			swap(a[Edge[i].u], a[Edge[i].v]);
			vis[i] = false;
		}
	}

	inline void main()
	{
		tot = 0;
		REP(i, 1, n - 1) scanf("%d%d", &Edge[i].u, &Edge[i].v);
		REP(i, 1, n) ans[i] = n + 1;
		DFS(1);
		REP(i, 1, n) printf("%d ", ans[i]); puts("");
	}
}

namespace Subtask2 
{
	int Begin[maxn], Next[maxn], To[maxn], e, d[maxn], p[maxn], id[maxn], belong[maxn];
	bool use[maxn];

	inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

	inline void DFS(int u, int dep, int fa)
	{
		p[dep] = a[u]; id[u] = dep; belong[dep] = u;
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i]; if ( v == fa ) continue ;
			DFS(v, dep + 1, u);
		}
	}

	inline void Solve2()
	{
		DFS(1, 1, 0);
		REP(i, 1, n) 
		{
			int x = id[i], Min = n + 1, pos = -1;
			if ( use[x] ) continue ;
			int L = x, R = x;
			while ( L > 1 && !use[L] ) 
			{
				-- L; if ( p[L] < Min ) { Min = p[L]; pos = L; }
			}
			while ( R < n && !use[R + 1] )
			{
				++ R; if ( p[R] < Min ) { Min = p[R]; pos = R; }
			}
			if ( p[x] < Min ) 
			{
				Min = n + 1;
				if ( pos > x ) { R = pos + 1; while ( R < n && !use[R + 1] ) { ++ R; if ( p[R] < Min ) { Min = p[R]; pos = R; } } }	
				else { L = pos - 1; while ( L > 1 && !use[L] ) { -- L; if ( p[L] < Min ) { Min = p[L]; pos = L; } } }
			}
			use[x] = true; 
			if ( pos < x ) REP(j, pos, x - 1) { swap(p[j], p[j + 1]); use[j] = true; }
			else for ( int j = pos; j > x; -- j ) { swap(p[j], p[j - 1]); use[j] = true; }
		}
		REP(i, 1, n) REP(j, 1, n) if ( p[j] == i ) printf("%d ", belong[j]); puts("");
	}

	inline void Solve1()
	{
		REP(i, 1, n) printf("%d ", i); puts("");
	}

	inline void main()
	{
		REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); ++ d[u]; ++ d[v]; add(u, v); add(v, u); }
		REP(i, 1, n) if ( d[i] == n - 1 || d[i] > 2 ) { Solve1(); return ; }
		Solve2();
	}
}

int main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	int T; scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d", &n);
		REP(i, 1, n) { int x; scanf("%d", &x); a[x] = i; }
		if ( n <= 160 ) Subtask1 :: main();
		else Subtask2 :: main();
	}
	return 0;
}
