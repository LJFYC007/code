/***************************************************************
	File name: CF526G.cpp
	Author: ljfcnyali
	Create time: 2021年05月28日 星期五 16时41分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int S, T, Root, dis[maxn], ans;
struct node { int len, id; } ;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

bool operator < (const node &a, const node &b) { return a.len > b.len; } 
node operator + (node a, int b) { return {a.len + b, a.id}; }
inline node max(node a, node b) { return a < b ? a : b; } 

inline void DFS1(int u, int fa)
{
	if ( dis[u] > dis[Root] ) Root = u;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		dis[v] = dis[u] + W[i]; DFS1(v, u);
	}
}

struct NODE
{
	int m, S, T, len, s[maxn], anc[maxn], vis[maxn], b[maxn], c[maxn], f[maxn][20], dis[maxn];
	bool use[maxn]; node a[maxn]; vector<node> p;

	inline void DFS3(int u, int fa)
	{
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i]; if ( v == fa || use[v] ) continue ; 
			c[v] = c[u]; DFS3(v, u);
		}
	}

	inline void DFS2(int u, int fa)
	{
		a[u] = {0, u}; if ( u == T ) use[u] = true;
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i]; if ( v == fa ) continue ; 
			anc[v] = u; b[v] = W[i]; f[v][0] = u; dis[v] = dis[u] + W[i];
			DFS2(v, u); 
			a[u] = max(a[u], a[v] + W[i]); use[u] |= use[v];
		}
		p.push_back(a[u] + b[u]);
		if ( use[u] ) { c[u] = u; DFS3(u, fa); }
	}

	inline int Get(int x, int y) { for ( int i = 18; i >= 0; -- i ) if ( vis[f[x][i]] > y ) x = f[x][i]; return f[x][0]; }

	inline void Build()
	{
		DFS2(S, 0); sort(p.begin(), p.end());
		for ( auto it : p ) 
		{
			int x = it.id; if ( vis[x] ) continue ; 
			++ m; s[m] = s[m - 1] + it.len;
			while ( !vis[x] ) { vis[x] = m; x = anc[x]; } 
		}
		REP(i, m + 1, maxn - 10) s[i] = s[i - 1];
		REP(j, 1, 18) REP(i, 1, n) f[i][j] = f[f[i][j - 1]][j - 1];
	}

	inline int Query(int x, int y)
	{
		int ans = 0;
		if ( y == 1 ) ans = a[x].len + dis[x];
		else if ( vis[x] <= y + y - 1 ) ans = s[y + y - 1];
		else
		{
			ans = s[y + y - 2] + a[x].len + dis[x] - dis[Get(x, y + y - 2)];
			ans = max(ans, s[y + y - 1] + a[x].len + dis[x] - dis[Get(x, y + y - 1)] - a[Get(x, y + y - 1)].len);
		}
		return ans;
	}
} A, B;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &q);
	REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); } 
	dis[1] = 0; DFS1(1, 0);	S = Root; dis[S] = 0; DFS1(S, 0); T = Root; 
	A.S = S; A.T = T; A.Build(); 
	B.S = T; B.T = S; B.Build();

	while ( q -- ) 
	{
		int x, y; scanf("%d%d", &x, &y);
		x = (x + ans - 1) % n + 1; y = (y + ans - 1) % n + 1;
		// cout << x << " " << y << " ";
		ans = max(A.Query(x, y), B.Query(x, y));
		printf("%d\n", ans);
	}
    return 0;
}
