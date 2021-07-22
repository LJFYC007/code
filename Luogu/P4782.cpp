/***************************************************************
	File name: P4782.cpp
	Author: ljfcnyali
	Create time: 2021年07月22日 星期四 14时41分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, A[maxn][2];
int dfn[maxn], low[maxn], tot, p[maxn], Stack[maxn], cnt;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u)
{
	dfn[u] = low[u] = ++ tot; Stack[++ cnt] = u;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i];
		if ( !dfn[v] ) { DFS(v); low[u] = min(low[u], low[v]); }
		else if ( !p[v] ) low[u] = min(low[u], dfn[v]);  
	}
	if ( dfn[u] == low[u] ) 
	{
		++ m; p[u] = m;
		while ( Stack[cnt] != u ) p[Stack[cnt --]] = m;
		-- cnt;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n) { A[i][0] = i; A[i][1] = n + i; }
	REP(o, 1, m)	
	{
		int i, a, j, b; scanf("%d%d%d%d", &i, &a, &j, &b);
		add(A[i][a ^ 1], A[j][b]); add(A[j][b ^ 1], A[i][a]);		
	}
	m = 0; REP(i, 1, n + n) if ( !dfn[i] ) DFS(i);
	REP(i, 1, n) if ( p[i] == p[i + n] ) { puts("IMPOSSIBLE"); return 0; } 
	puts("POSSIBLE");
	REP(i, 1, n) if ( p[i] < p[i + n] ) printf("0 "); else printf("1 "); puts("");
    return 0;
}
