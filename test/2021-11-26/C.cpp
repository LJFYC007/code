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
typedef long long LL;

const int maxn = 10010;

int n, q, f[maxn], Begin[maxn], Next[maxn], To[maxn], e, deg[maxn], anc[maxn];
bool ans[maxn][maxn], vis[maxn], Vis[maxn], flag, use[maxn];
pii Edge[maxn];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[u]; }

inline void DFS(int u, int fa)
{
	if ( flag ) return ;
	Vis[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( i == (fa ^ 1) ) continue ; 
		if ( flag ) return ;
		if ( Vis[v] ) 
		{
			while ( u != v ) { use[u] = true; u = anc[u]; }
			use[v] = true;
			flag = true; return ;
		}
		anc[v] = u; DFS(v, i);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) scanf("%d%d", &Edge[i].first, &Edge[i].second);
	REP(o, 1, n)
	{
		mem(vis);
		REP(i, 1, n) f[i] = i;
		int num = 0, t = -1;
		flag = false;
		REP(i, o, n)
		{
			int u = Edge[i].first, v = Edge[i].second;
			int fu = find(u), fv = find(v);
			if ( !vis[u] ) ++ num; if ( !vis[v] ) ++ num;
			vis[u] = vis[v] = true;
			if ( fu != fv ) { f[fu] = fv; -- num; }
			else 
			{
				if ( flag ) goto Next;
				flag = true;
			}

			if ( flag && num == 1 ) { t = i; break ; }
		}
		if ( t == -1 ) goto Next ;

		mem(Begin); mem(deg); e = 1;
		REP(i, o, t) 
		{
			add(Edge[i].first, Edge[i].second);
			add(Edge[i].second, Edge[i].first);
		}

		mem(Vis); flag = false; mem(use);
		DFS(Edge[o].first, 0);

		REP(i, 1, n) if ( !use[i] && deg[i] > 2 ) goto Next ; 

		ans[o][t] = true;
		REP(i, t + 1, n)
		{
			int u = Edge[i].first, v = Edge[i].second;
			++ deg[u]; ++ deg[v];
			if ( !use[u] && deg[u] > 2 ) goto Next ; 
			if ( !use[v] && deg[v] > 2 ) goto Next ; 
			int fu = find(u), fv = find(v);
			if ( !vis[u] ) ++ num; if ( !vis[v] ) ++ num;
			vis[u] = vis[v] = true;
			if ( fu != fv ) { f[fu] = fv; -- num; }
			else goto Next ;

			if ( num == 1 ) ans[o][i] = true;	
		}

		Next : ; 
	}
	scanf("%d", &q);
	//REP(i, 1, n) REP(j, i, n) if ( ans[i][j] ) cerr << i << " " << j << endl;
	while ( q -- ) 
	{
		int l, r; scanf("%d%d", &l, &r);
		int ret = 0;
		REP(i, l, r) REP(j, i, r) if ( ans[i][j] ) ++ ret;
		printf("%d\n", ret);
	}
    return 0;
}
