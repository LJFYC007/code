/***************************************************************
	File name: sssp.cpp
	Author: ljfcnyali
	Create time: 2021年06月22日 星期二 15时27分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 167;

int n, m, q, len;
struct Matrix
{
	int n, m, f[maxn][maxn][16], sz[maxn][maxn];
} f[21], g;
struct node 
{ 
	int j, p, q, w; 
	bool operator <(const node &a) const { return w < a.w; } 
	bool operator >(const node &a) const { return w > a.w; } 
} Q[maxn * maxn];

inline bool cmp(node a, node b) { return a > b; }
inline void INIT() { make_heap(Q + 1, Q + len + 1, cmp); }
inline void Insert(node t)
{
	Q[++ len] = t; int k = len;
	while ( k > 1 && Q[k] < Q[k / 2] ) 
	{
		swap(Q[k], Q[k / 2]);
		k /= 2;
	}
}

inline void Erase()
{
	Q[1] = Q[len --]; int k = 1;
	while((k * 2 <= len && Q[k] > Q[k * 2]) || (k * 2 + 1 <= len && Q[k] > Q[k * 2 + 1])) {
		m = k * 2;
		if(m + 1 <= len && Q[m] > Q[m + 1])
			++ m;
		swap(Q[k], Q[m]);
		k = m;
	}
}

Matrix operator *(Matrix a, Matrix b)
{
	Matrix c; c.n = a.n; c.m = b.m;
	REP(i, 1, c.n) REP(k, 1, c.m) 
	{
		c.sz[i][k] = 0; len = 0;
		REP(j, 1, a.m) if ( a.sz[i][j] && b.sz[j][k] ) Q[++ len] = {j, 0, 0, a.f[i][j][0] + b.f[j][k][0]};
		INIT();

		while ( len && c.sz[i][k] < 15 ) 
		{
			node now = Q[1]; Erase();
			c.f[i][k][c.sz[i][k] ++] = now.w; 
			if ( !now.p && now.q + 1 < b.sz[now.j][k] )
				Insert({now.j, now.p, now.q + 1, a.f[i][now.j][now.p] + b.f[now.j][k][now.q + 1]});
			if ( now.p + 1 < a.sz[i][now.j] )
				Insert({now.j, now.p + 1, now.q, a.f[i][now.j][now.p + 1] + b.f[now.j][k][now.q]});
		}
	}
	return c;
}

int main()
{
    freopen("sssp.in", "r", stdin);
    freopen("sssp.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &q); f[0].n = f[0].m = n;
	REP(i, 1, m)
	{
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		f[0].f[u][v][f[0].sz[u][v] ++] = w;
		if ( f[0].sz[u][v] == 16 ) 
		{
			REP(j, 0, 14) if ( f[0].f[u][v][j] > f[0].f[u][v][15] )
				swap(f[0].f[u][v][j], f[0].f[u][v][15]);
			-- f[0].sz[u][v];
		}
	}
	REP(i, 1, n) REP(j, 1, n) sort(f[0].f[i][j], f[0].f[i][j] + f[0].sz[i][j]);
	REP(i, 1, 20) f[i] = f[i - 1] * f[i - 1];
	while ( q -- ) 
	{
		int s, t, a, k; scanf("%d%d%d%d", &s, &t, &a, &k);
		g.n = 1; g.m = n; REP(i, 1, n) g.sz[1][i] = 0;
		g.f[1][s][g.sz[1][s] ++] = 0;
		for ( int i = 20; i >= 0; -- i ) if ( (a >> i) & 1 ) g = g * f[i];
		if ( k > g.sz[1][t] ) puts("-1");
		else printf("%d\n", g.f[1][t][k - 1]);
	}
    return 0;
}
