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

int n, m, q;
struct Matrix
{
	int n, m;
	vector<int> f[maxn][maxn];
} f[21], g;
struct node 
{ 
	int j, p, q, w; 
	bool operator <(const node &a) const { return w > a.w; } 
};

Matrix operator *(Matrix a, Matrix b)
{
	Matrix c; c.n = a.n; c.m = b.m;
	REP(i, 1, c.n) REP(k, 1, c.m) 
	{
		c.f[i][k].clear(); priority_queue<node> Q;
		REP(j, 1, n) for ( int p = 0; p < a.f[i][j].size(); ++ p )
			if ( !b.f[j][k].empty() ) Q.push({j, p, 0, a.f[i][j][p] + b.f[j][k][0]});
		int sum = 15;
		while ( !Q.empty() && sum ) 
		{
			node now = Q.top(); Q.pop(); -- sum; 
			c.f[i][k].push_back(now.w); 
			if ( now.q + 1 < b.f[now.j][k].size() )
				Q.push({now.j, now.p, now.q + 1, a.f[i][now.j][now.p] + b.f[now.j][k][now.q + 1]});
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
		f[0].f[u][v].push_back(w);
	}
	REP(i, 1, n) REP(j, 1, n)
	{
		sort(f[0].f[i][j].begin(), f[0].f[i][j].end());
		while ( f[0].f[i][j].size() > 15 ) f[0].f[i][j].pop_back();
	}
	REP(i, 1, 10) f[i] = f[i - 1] * f[i - 1];
	while ( q -- ) 
	{
		int s, t, a, k; scanf("%d%d%d%d", &s, &t, &a, &k);
		g.n = 1; g.m = n; REP(i, 1, n) g.f[1][i].clear();
		g.f[1][s].push_back(0);
		for ( int i = 10; i >= 0; -- i ) if ( (a >> i) & 1 ) g = g * f[i];
		if ( k - 1 >= g.f[1][t].size() ) puts("-1");
		else printf("%d\n", g.f[1][t][k - 1]);
	}
    return 0;
}
