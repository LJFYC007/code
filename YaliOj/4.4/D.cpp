/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年06月02日 星期日 14时38分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 600010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int dis[maxn], n, m, anc[maxn][30], F[maxn];
long long sum, cnt, ans;
int f[maxn][30][2], Max, Maxx;
bool use[maxn];

struct node
{
	int u, v, w;
} a[maxn];

inline int cmp(node a, node b) { return a.w < b.w; }

inline int cha(int x) { return x == F[x] ? x : F[x] = cha(F[x]); }

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline void DFS(int u, int x)
{
	dis[u] = ++ x;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( dis[v] ) continue ;
		anc[v][0] = u; f[v][0][0] = W[i];
		DFS(v, x);
	}
}

inline int maxx(int a, int b, int c, int d)
{
	if ( a == c ) return max(b, d);
	if ( a > c ) return max(b, c);
	if ( a < c ) return max(a, d);
}

inline void Get_Max(int x, int y)
{
	if ( dis[x] < dis[y] ) swap(x, y);
	for ( int j = 18; j >= 0; -- j )
		if ( dis[anc[x][j]] >= dis[y] )
		{
			x = anc[x][j];
			Max = max(Max, f[x][j][0]);
			if ( Max == f[x][j][0] ) Maxx = max(Maxx, f[x][j][1]);
			else Maxx = max(Maxx, f[x][j][0]);
		}
	if ( x == y ) return ;
	for ( int j = 18; j >= 0; -- j )
		if ( anc[x][j] != anc[y][j] ) 
		{
			int M = max(f[x][j][0], f[y][j][0]), k;
			Max = max(Max, M);
			if ( Max == M ) k =	maxx(f[x][j][0], f[x][j][1], f[y][j][0], f[y][j][1]);
			else k = M;
			Maxx = max(Maxx, k);
			x = anc[x][j]; y = anc[y][j];
		}
	int M = max(f[x][0][0], f[y][0][0]), k; Max = max(Max, M);
	if ( Max == M ) k =	maxx(f[x][0][0], f[x][0][1], f[y][0][0], f[y][0][1]);
	else k = M;
	Maxx = max(Maxx, k);
}

inline void Solve(int x)
{
	Max = Maxx = 0;	
	Get_Max(a[x].u, a[x].v);
	if ( Max == 0 ) return ;
	if ( a[x].w == Max ) ans = min(ans, sum + a[x].w - Maxx);
	else if ( a[x].w > Max ) ans = min(ans, sum + a[x].w - Max);
  printf("%d %d %d %d %d\n", ans, a[x].u, a[x].v, Max, Maxx);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m)
	{
		scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
//		add(a[i].u, a[i].v, a[i].w);
//		add(a[i].v, a[i].u, a[i].w);
	}
	sort ( a + 1, a + m + 1, cmp );
	REP(i, 1, n) F[i] = i;
	REP(i, 1, m)
	{
		int fx = cha(a[i].u), fy = cha(a[i].v);
		if ( fx != fy ) 
		{
			F[fx] = fy; ++ cnt; sum += a[i].w;
			add(a[i].u, a[i].v, a[i].w); add(a[i].v, a[i].u, a[i].w); ++ m;
			use[i] = true;
		}
		if ( cnt == n - 1 ) break ;
	}
	DFS(1, 0);
	REP(j, 1, 18) REP(i, 1, n)
	{
		anc[i][j] = anc[anc[i][j - 1]][j - 1];
		f[i][j][0] = max(f[i][j - 1][0], f[anc[i][j - 1]][j - 1][0]);
		f[i][j][1] = 
			maxx(f[i][j - 1][0], f[i][j - 1][1], f[anc[i][j - 1]][j - 1][0], f[anc[i][j - 1]][j - 1][1]);
	}
	ans = 0x3f3f3f3f3f3f;
	REP(i, 1, m)
	{
		if ( use[i] ) { printf("%d %d\n", a[i].u, a[i].v); continue ; }
		Solve(i);	
	}
	printf("%lld\n", ans);
    return 0;
}
