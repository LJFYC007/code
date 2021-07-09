/***************************************************************
	File name: BZOJ3522.cpp
	Author: ljfcnyali
	Create time: 2019年10月10日 星期四 15时41分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 10010;

int n, Begin[maxn], Next[maxn], To[maxn], e;
int f[5010][5010], g[5010][5010], ans;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
	f[u][0] = 1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ;
		DFS(v, u);
	}
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ;
		REP(j, 0, n) 
		{
			ans += f[u][j] * g[v][j + 1] + g[u][j] * f[v][j - 1];
			g[u][j + 1] += f[u][j + 1] * f[v][j];
			g[u][j - 1] += g[v][j];
			f[u][j + 1] += f[v][j];
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	DFS(1, 0);
	printf("%d\n", ans);
    return 0;
}
