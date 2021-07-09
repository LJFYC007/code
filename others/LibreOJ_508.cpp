/***************************************************************
	File name: LibreOJ_508.cpp
	Author: ljfcnyali
	Create time: 2021年02月19日 星期五 11时30分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;

int n, m, q, fa[maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int anc[maxn][20], dep[maxn], dis[maxn], Val[maxn];
struct node { int op, u, v, w, x, b, c; } Q[maxn];
bool vis[maxn];

inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ;
		dis[v] = dis[u] + 1; anc[v][0] = u; 
		dep[v] = dep[u] + W[i]; DFS(v, u);
 	}
}

inline int LCA(int x, int y)
{
	if ( dis[x] < dis[y] ) swap(x, y);
	for ( int i = 19; i >= 0; -- i ) if ( dis[anc[x][i]] >= dis[y] ) x = anc[x][i];
	if ( x == y ) return x;
	for ( int i = 19; i >= 0; -- i ) if ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; }
	return anc[x][0];
}

inline int Dis(int x, int y) { return dep[x] + dep[y] - 2 * dep[LCA(x, y)]; }

inline void exgcd(int a, int b, int &x, int &y)
{
	if ( !b ) { x = 1; y = 0; return ; } 
	exgcd(b, a % b, x, y); int t = x; x = y; y = t - a / b * y;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &m, &q);
	REP(i, 1, n) fa[i] = i; 
	REP(i, 1, q) 
	{
		scanf("%lld%lld%lld", &Q[i].op, &Q[i].u, &Q[i].v);
		if ( Q[i].op == 1 ) 
		{
			scanf("%lld", &Q[i].w); int fx = find(Q[i].u), fy = find(Q[i].v);
			if ( fx != fy ) { vis[i] = true; fa[fx] = fy; add(Q[i].u, Q[i].v, Q[i].w); add(Q[i].v, Q[i].u, Q[i].w); }
		}
		else scanf("%lld%lld%lld", &Q[i].x, &Q[i].b, &Q[i].c);
	}
	REP(i, 1, n) if ( !dis[i] ) { dis[i] = 1; DFS(i, 0); }
	REP(j, 1, 19) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	REP(i, 1, n) { Val[i] = m; fa[i] = i; }
	REP(i, 1, q)
	{
		int fx = find(Q[i].u), fy = find(Q[i].v);
		if ( Q[i].op == 1 ) 
		{
			if ( fx != fy ) { fa[fx] = fy; Val[fy] = __gcd(Val[fy], Val[fx]); }
			Val[fy] = __gcd(Val[fy], Q[i].w + Q[i].w);
		}
		if ( vis[i] ) continue ;

		if ( Q[i].op == 1 ) Val[fy] = __gcd(Val[fy], Dis(Q[i].u, Q[i].v) + Q[i].w);
		else
		{
			if ( fx != fy ) { puts("0"); continue ; } 
			int C = Dis(Q[i].u, Q[i].v) - Q[i].x, A = Q[i].b, B = Val[fy], x, y;
			int d = __gcd(A, B); if ( C % d != 0 ) { puts("0"); continue ; } 
			A /= d; B /= d; C /= d;
			exgcd(A, B, x, y);
			x *= C; x = (x % B + B) % B;
			int ans = 0;
			if ( x < Q[i].c ) { ++ ans; ans += (Q[i].c - x - 1) / B; }
			printf("%lld\n", ans);
		}
	}
    return 0;
}
