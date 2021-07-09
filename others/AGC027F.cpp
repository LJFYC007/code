/***************************************************************
	File name: AGC027F.cpp
	Author: ljfcnyali
	Create time: 2021年04月23日 星期五 10时08分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110; 
const int INF = 0x3f3f3f3f;

int T, n, anc[2][maxn], ans, ret, e, Begin[maxn], Next[maxn], To[maxn], deg[maxn];
vector<int> Edge[2][maxn]; queue<int> Q;
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[v]; } 

inline void DFS(int u, int fa, int op)
{
	anc[op][u] = fa; 
	for ( auto v : Edge[op][u] ) if ( v != fa ) DFS(v, u, op); 
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d", &n); REP(o, 0, 1) REP(i, 1, n) Edge[o][i].clear(); ans = INF;
		REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); Edge[0][u].push_back(v); Edge[0][v].push_back(u); }
		REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); Edge[1][u].push_back(v); Edge[1][v].push_back(u); }
		REP(i, 1, n) REP(k, 1, n)
		{
			ret = e = 0; 
			if ( i != k ) { if ( Edge[0][i].size() > 1 ) goto Next ; ++ ret; }
			DFS(k, 0, 0); DFS(i, 0, 1); mem(vis); mem(Begin); mem(deg);
			anc[0][k] = i;

			REP(j, 1, n) if ( j != i && anc[0][j] != anc[1][j] ) { ++ ret; vis[j] = true; }
			REP(j, 1, n) if ( j != i && !vis[j] && vis[anc[0][j]] ) goto Next ; 
			REP(j, 1, n) if ( vis[j] ) 
			{
				if ( vis[anc[0][j]] ) add(j, anc[0][j]); 
				if ( vis[anc[1][j]] ) add(anc[1][j], j); 
			} 
			REP(j, 1, n) if ( !deg[j] ) Q.push(j); 
			while ( !Q.empty() ) 
			{
				int u = Q.front(); Q.pop();
				for ( int i = Begin[u]; i; i = Next[i] ) 
				{
					int v = To[i]; -- deg[v];
					if ( !deg[v] ) Q.push(v);
				}
			}
			REP(j, 1, n) if ( deg[j] ) goto Next ;
			ans = min(ans, ret);
Next : ; 
		}
		if ( ans == INF ) puts("-1"); else printf("%d\n", ans);
	}
    return 0;
}
