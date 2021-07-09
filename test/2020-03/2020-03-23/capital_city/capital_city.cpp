#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, C[maxn], id[maxn], c[maxn], a[maxn];
int dis[maxn], anc[maxn][20], ans, ret, t, vis[maxn], cnt, num, size[maxn];
vector<int> Col[maxn], p, col[maxn];
bool use[maxn], flag;
queue<int> Q;

namespace Subtask
{
	int Begin[maxn], Next[maxn], To[maxn], e, deg[maxn];
	bool vis[maxn];
	queue<int> Q;

	inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[u]; }

	inline void INIT() { REP(i, 1, num) Begin[i] = deg[i] = vis[i] = 0; e = 0; }

	inline void Solve(int x)
	{
		-- ret;
		for ( int i = 0; i < col[x].size(); ++ i ) if ( !vis[col[x][i]] ) { Q.push(col[x][i]); vis[col[x][i]] = true; }
	}

	inline void Solve()
	{
		while ( !Q.empty() ) Q.pop();
		REP(i, 1, num) if ( deg[i] == 1 ) { -- size[c[i]]; if ( size[c[i]] == 0 ) Solve(c[i]); }
		while ( !Q.empty() )
		{
			int u = Q.front(); Q.pop();
			for ( int j = Begin[u]; j; j = Next[j] )
			{
				int v = To[j]; -- deg[v];
				if ( deg[v] == 1 ) { -- size[c[v]]; if ( size[c[v]] == 0 ) Solve(c[v]); }
			}
		}
	}
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ;
		dis[v] = dis[u] + 1; anc[v][0] = u; DFS(v, u);
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

inline void Solve(int x)
{
	if ( use[x] ) return ; use[x] = true; ++ ret;
	int last = anc[t][0];
	for ( int j = 0; j < Col[x].size(); ++ j )
	{
		int u = Col[x][j];
		Q.push(u); t = LCA(t, u);
	}
	while ( !vis[last] && dis[last] >= dis[t] ) { vis[last] = cnt; Solve(C[last]); last = anc[last][0]; }
	if ( dis[last] >= dis[t] && vis[last] && vis[last] != cnt ) flag = true;
}

inline void DFS1(int u, int fa)
{
	p.push_back(u);
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa || vis[v] != cnt ) continue ;
		DFS1(v, u);
	}
}

inline void DFS2(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa || vis[v] != cnt || C[v] != C[u] ) continue ;
		id[v] = num; DFS2(v, u);
	}
}

inline void Check()
{
	mem(vis); mem(use); mem(id); cnt = 0;
	REP(i, 1, n) a[i] = i; random_shuffle(a + 1, a + n + 1);
	REP(i, 1, n)
	{
		if ( vis[a[i]] ) continue ;
		ret = -1; t = a[i]; ++ cnt; flag = false;
		while ( !Q.empty() ) Q.pop();
		Solve(C[a[i]]);
		while ( !Q.empty() )
		{
			int u = Q.front(); Q.pop();
			while ( !vis[u] && dis[u] >= dis[t] ) { vis[u] = cnt; Solve(C[u]); u = anc[u][0]; }
			if ( dis[u] >= dis[t] && vis[u] && vis[u] != cnt ) flag = true;
		}
		if ( flag == true ) continue ;

		p.clear(); DFS1(t, 0); num = 0;
		for ( int j = 0; j < p.size(); ++ j )
		{
			int u = p[j]; if ( id[u] ) continue ;
			id[u] = ++ num; c[num] = C[u];
			col[C[u]].clear(); size[C[u]] = 0;
			DFS2(u, 0);
		}
		REP(j, 1, num) { ++ size[c[j]]; col[c[j]].push_back(j); }
		Subtask :: INIT();
		for ( int j = 0; j < p.size(); ++ j )
		{
			int u = p[j];
			for ( int J = Begin[u]; J; J = Next[J] )
			{
				int v = To[J]; if ( vis[v] != cnt || id[u] == id[v] ) continue ;
				Subtask :: add(id[u], id[v]);
			}
		}
		Subtask :: Solve();

		ans = min(ans, max(0, ret));
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	srand(time(0));
	scanf("%d%d", &n, &m);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	REP(i, 1, n) { scanf("%d", &C[i]); Col[C[i]].push_back(i); }
	REP(i, 1, m) if ( Col[i].size() == 1 ) { puts("0"); return 0; }
	dis[1] = 1; DFS(1, 0);
	REP(j, 1, 19) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	ans = n + 1;
	REP(i, 1, n)
	{
		if ( vis[i] ) continue ;
		ret = -1; t = i; ++ cnt; flag = false;
		while ( !Q.empty() ) Q.pop();
		Solve(C[i]);
		while ( !Q.empty() )
		{
			int u = Q.front(); Q.pop();
			while ( !vis[u] && dis[u] >= dis[t] ) { vis[u] = cnt; Solve(C[u]); u = anc[u][0]; }
			if ( dis[u] >= dis[t] && vis[u] && vis[u] != cnt ) flag = true;
		}
		if ( flag == true ) continue ;

		p.clear(); DFS1(t, 0); num = 0;
		for ( int j = 0; j < p.size(); ++ j )
		{
			int u = p[j]; if ( id[u] ) continue ;
			id[u] = ++ num; c[num] = C[u];
			col[C[u]].clear(); size[C[u]] = 0;
			DFS2(u, 0);
		}
		REP(j, 1, num) { ++ size[c[j]]; col[c[j]].push_back(j); }
		Subtask :: INIT();
		for ( int j = 0; j < p.size(); ++ j )
		{
			int u = p[j];
			for ( int J = Begin[u]; J; J = Next[J] )
			{
				int v = To[J]; if ( vis[v] != cnt || id[u] == id[v] ) continue ;
				Subtask :: add(id[u], id[v]);
			}
		}
		Subtask :: Solve();

		ans = min(ans, max(0, ret));
	}

	REP(i, 1, 5) Check();

	printf("%d\n", ans);
	return 0;
}
