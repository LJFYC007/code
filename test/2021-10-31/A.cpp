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

const int maxn = 4e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e;
int dis[maxn], anc[maxn][20];
bool vis[maxn], f[maxn], g[maxn];
LL ans;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		dis[v] = dis[u] + 1; DFS(v, u); anc[v][0] = u; 
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

inline int Get(int x, int len)
{
	for ( int j = 19; j >= 0; -- j ) 
		if ( len >= (1 << j) ) 
		{
			x = anc[x][j];
			len -= 1 << j;
		}
	return x;
}

inline void DFS1(int u, int fa)
{
	if ( vis[u] ) f[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS1(v, u); f[u] |= f[v];
	}
}

inline void DFS2(int u, int fa)
{
	int sum = vis[u];
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		sum += f[v];
	}

	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		g[v] = g[u] | ((sum - f[v]) >= 1);
		DFS2(v, u); 
	}
}

inline int DFS3(int u, int fa)
{
	int size = !vis[u];
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		size += DFS3(v, u);
	}
	ans += size; return size;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
	dis[1] = 1; DFS(1, 0);
	REP(j, 1, 19) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];

	if ( m == 1 ) 
	{
		int u, v; scanf("%d%d", &u, &v);
		int t = LCA(u, v);
		if ( dis[u] + dis[v] - 2 * dis[t] <= 2 ) { puts("0"); exit(0); }
		
		mem(anc); dis[u] = 1; DFS(u, 0);
		int sum = 1; vis[u] = true;
		while ( v != u ) { ++ sum; vis[v] = true; v = anc[v][0]; }

		ans = sum * (sum - 1) / 2;
		DFS3(u, 0);
		cout << ans << endl;
	}

	REP(i, 1, m)
	{
		int u, v; scanf("%d%d", &u, &v);
		int t = LCA(u, v);
		if ( dis[u] + dis[v] - 2 * dis[t] <= 2 ) continue ; 
		while ( u != t ) { vis[u] = true; u = anc[u][0]; } 
		while ( v != t ) { vis[v] = true; v = anc[v][0]; } 
		vis[t] = true;
	}

	DFS1(1, 0); DFS2(1, 0);

	int ans = 0;
	REP(i, 1, n) REP(j, 1, n) if ( i != j ) 
	{
		int t = LCA(i, j);
		if ( dis[i] >= dis[j] )
		{
			int pos = Get(i, (dis[i] + dis[j] - 2 * dis[t] - 1) / 2);
			ans += f[pos];
			if ( f[pos] ) cout << i << " " << j << " " << pos << endl;
		}
		else
		{
			int pos = Get(j, (dis[i] + dis[j] - 2 * dis[t]) / 2);
			ans += g[pos];
			if ( g[pos] ) cout << i << " " << j << " " << pos << endl;
		}
	}
	printf("%lld\n", ans);
    return 0;
}
