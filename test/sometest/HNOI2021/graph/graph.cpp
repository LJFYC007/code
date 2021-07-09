#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define x first
#define y second

const int maxm = 2e5 + 10;
const int maxn = 1010;

int n, m, ans[maxm], Begin[maxm], Next[maxm], To[maxm], e, f[2][maxn][maxn];
pii Edge[maxm];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int x, int y, int z)
{
	if ( u < y || f[x][u][y] ) return ;
	f[x][u][y] = z;
	for ( int i = Begin[u]; i; i = Next[i] ) DFS(To[i], x, y, z);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m); 
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); Edge[i] = pii(u, v); }
	REP(i, 1, n) f[0][i][i] = f[1][i][i] = m + 1;
	for ( int i = m; i >= 1; -- i ) 
	{
		int s = Edge[i].x, t = Edge[i].y; 
		REP(j, 1, n) if ( f[0][t][j] ) DFS(s, 0, j, i);
		add(t, s);
	}
	e = 0; mem(Begin);
	for ( int i = m; i >= 1; -- i ) 
	{
		int s = Edge[i].x, t = Edge[i].y;
		REP(j, 1, n) if ( f[1][s][j] ) DFS(t, 1, j, i);
		add(s, t);
	}
	REP(i, 1, n) REP(j, 1, n) ++ ans[min(f[0][i][j], f[1][i][j])];
	for ( int i = m + 1; i >= 1; -- i ) ans[i] += ans[i + 1];
	REP(i, 1, m + 1) printf("%d ", ans[i]); puts("");
	return 0;
}
