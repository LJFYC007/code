/***************************************************************
	File name: AGC029E.cpp
	Author: ljfcnyali
	Create time: 2021年04月04日 星期日 14时46分46秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 4e5 + 10;
 
int n, ans[maxn], g[maxn], Begin[maxn], Next[maxn], To[maxn], e, Max[maxn], anc[maxn];
map<int, int> f[maxn];
 
inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 
 
inline void DFS1(int u, int fa)
{
	f[u][Max[u]] = f[u][Max[anc[u]]] = f[u][Max[anc[anc[u]]]] = 0;
	for ( auto it : f[u] ) f[u][it.first] = 1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		Max[v] = max(Max[u], v); anc[v] = u; 
		for ( auto it : f[u] ) if ( v <= it.first ) f[v][it.first] = 0;
		DFS1(v, u);
		for ( auto it : f[u] ) if ( v <= it.first ) f[u][it.first] += f[v][it.first];
	}
}
 
inline void DFS2(int u, int fa)
{
	int sum = 0;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		if ( v <= Max[fa] ) sum += f[v][Max[fa]];
	}
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		g[v] = g[u] + sum - (v <= Max[fa] ? f[v][Max[fa]] : 0) + 1;
		ans[v] = g[v] + f[v][Max[u]] - 1;
		DFS2(v, u); 
	}
}
 
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	Max[1] = 1; DFS1(1, 0); DFS2(1, 0);
	REP(i, 2, n) printf("%d ", ans[i]); puts("");
    return 0;
}

