/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年07月13日 星期二 08时57分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;
const int INF = 0x3f3f3f3f;

int n, a[maxn], f[maxn][maxn], g[maxn][maxn], anc[maxn], deg[maxn];
int Begin[maxn], Next[maxn << 1], To[maxn << 1], e;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[v]; } 

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ;
		anc[v] = u; DFS(v, u);
	}
	int N = deg[u] - 2;
	REP(j, 0, N) f[u][j] = INF;
	REP(j, 1, N)
	{
		vector<int> p;
		for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) p.push_back(f[To[i]][j]);
		sort(p.begin(), p.end()); reverse(p.begin(), p.end());
		for ( int i = 0; i < p.size(); ++ i ) 
			f[u][j + i - 1] = min(f[u][j + i - 1], p[i]);
	}
	REP(j, 0, N) f[u][j] = max(a[u], f[u][j] == INF ? 0 : f[u][j]);
	REP(j, deg[u] - 1, n) f[u][j] = a[u];
}

inline void DFS1(int u, int fa)
{
	if ( fa )  
	{
		int N = deg[fa] - 2;
		REP(j, 0, N) g[u][j] = INF;
		REP(j, 1, N)
		{
			vector<int> p; p.push_back(g[fa][j]);
			for ( int i = Begin[fa]; i; i = Next[i] ) if ( To[i] != u && To[i] != anc[fa] ) p.push_back(f[To[i]][j]);
			sort(p.begin(), p.end()); reverse(p.begin(), p.end());
			for ( int i = 0; i < p.size(); ++ i ) 
				g[u][j + i - 1] = min(g[u][j + i - 1], p[i]);
		}
		REP(j, 0, N) g[u][j] = max(a[fa], g[u][j] == INF ? 0 : g[u][j]);
		REP(j, deg[fa] - 1, n) g[u][j] = a[fa];
	}
	for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) DFS1(To[i], u);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
	DFS(1, 0); DFS1(1, 0);
	REP(i, 1, n) printf("%d ", max(f[i][0], g[i][1])); puts("");
    return 0;
}
