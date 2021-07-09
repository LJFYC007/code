#include "chameleon.h"
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>

const int maxn = 1010;

bool vis[maxn], p[maxn][maxn], Edge[maxn][maxn];
int a[maxn], m;
vector<int> t;

inline int Find(int x, int y, int z)
{
	t.clear(); t.push_back(x); t.push_back(y); t.push_back(z);
	return Query(t);
}

inline void Check(int x, int n)
{
	m = 0; REP(i, 1, n * 2) if ( Edge[x][i] && x != i ) a[++ m] = i;
	if ( m <= 2 )
	{
		REP(i, 1, m) p[x][a[i]] = true;
		return ;
	}
	if ( Find(x, a[1], a[2]) == 1 ) { p[x][a[1]] = p[x][a[2]] = true; }
	if ( Find(x, a[1], a[3]) == 1 ) { p[x][a[1]] = p[x][a[3]] = true; }
	if ( Find(x, a[2], a[3]) == 1 ) { p[x][a[2]] = p[x][a[3]] = true; }
}

inline void Get(int x, int l, int r)
{
	if ( l > r ) return ;
	t.clear(); t.push_back(x);
	REP(i, l, r) t.push_back(i);
	if ( Query(t) == r - l + 2 ) return ;
	if ( l == r ) { Edge[x][l] = Edge[l][x] = true; return ; }
	int Mid = l + r >> 1;
	Get(x, l, Mid); Get(x, Mid + 1, r);
}

void Solve(int n)
{
	REP(i, 1, n) Get(i, n + 1, n * 2);
	/*
	if ( n > 50 ) REP(i, 1, n) Get(i, n + 1, n * 2);
	else
	{
		REP(i, 1, n * 2) REP(j, i + 1, n * 2)
		{
			t.clear(); t.push_back(i); t.push_back(j);
			if ( Query(t) == 1 ) Edge[i][j] = Edge[j][i] = true;
		}
	}
	*/
	REP(i, 1, n * 2) Check(i, n);
	REP(i, 1, n * 2)
	{
		if ( vis[i] ) continue ;
		for ( int j = n * 2; j >= 1; -- j ) if ( p[i][j] && p[j][i] && i != j ) { Answer(i, j); vis[i] = vis[j] = true; break ; }
	}
}
