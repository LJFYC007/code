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

const int maxn = 3010;

int n, m, k, deg[maxn], ans, f[maxn][maxn], Begin[maxn], Next[maxn], To[maxn], e;
vector<pii> Edge[maxn];
queue<int> Q;

inline void add(int u, int v, int w)
{
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e;
	Edge[v].push_back(pii(u, w)); ++ deg[v];
}

int main()
{
	freopen("bracket.in", "r", stdin);
	freopen("bracket.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); }
	REP(i, 1, n) if ( !deg[i] ) Q.push(i);
	REP(i, 1, n) REP(j, 1, n) if ( i != j ) f[i][j] = 1;
	while ( !Q.empty() )
	{
		int u = Q.front(); Q.pop();
		for ( int i = Begin[u]; i; i = Next[i] )
		{
			int v = To[i]; -- deg[v];
			if ( !deg[v] ) Q.push(v);
		}
		for ( int i = 0; i < Edge[u].size(); ++ i )
			for ( int j = i + 1; j < Edge[u].size(); ++ j )
				if ( Edge[u][i].second == Edge[u][j].second )
				{
					if ( f[Edge[u][i].first][Edge[u][j].first] ) printf("%d %d\n", Edge[u][i].first, Edge[u][j].first);
					ans += f[Edge[u][i].first][Edge[u][j].first];
				}

		REP(v, 1, n) if ( v != u )
			for ( int i = 0; i < Edge[u].size(); ++ i )
				for ( int j = 0; j < Edge[v].size(); ++ j )
					if ( Edge[u][i].second == Edge[v][j].second )
						f[u][v] += f[Edge[u][i].first][Edge[v][j].first];
	}
	printf("%d\n", ans);
    return 0;
}
