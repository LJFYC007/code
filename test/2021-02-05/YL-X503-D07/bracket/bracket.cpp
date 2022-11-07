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

int n, m, k, ans;
bool f[maxn][maxn];
vector<pii> Edge[maxn];
queue<pii> Q;

inline void add(int u, int v, int w) { Edge[v].push_back(pii(u, w)); }

int main()
{
	freopen("bracket.in", "r", stdin);
	freopen("bracket.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); }
	REP(i, 1, n) { f[i][i] = 1; Q.push(pii(i, i)); }
	while ( !Q.empty() )
	{
		int u = Q.front().first, v = Q.front().second; Q.pop();
		for ( int i = 0; i < Edge[u].size(); ++ i )
			for ( int j = 0; j < Edge[v].size(); ++ j )
			{
				pii x = Edge[u][i], y = Edge[v][j];
				if ( x.second == y.second && !f[x.first][y.first] )
				{
					f[x.first][y.first] = true;
					Q.push(pii(x.first, y.first));
				}
			}
		REP(x, 1, n) if ( u != x && v != x )
		{
			if ( !f[u][x] && f[v][x] ) { f[u][x] = true; Q.push(pii(u, x)); }
			if ( !f[x][v] && f[x][u] ) { f[x][v] = true; Q.push(pii(x, v)); }
		}
	}
	REP(i, 1, n) REP(j, i + 1, n) ans += f[i][j];
	printf("%d\n", ans);
    return 0;
}
