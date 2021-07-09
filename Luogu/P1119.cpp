#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss
const int maxn = 210;

int dis[maxn][maxn], n, m, q, Time[50010], K;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	memset(dis, 0x3f, sizeof (dis));
	Time[n] = 0x3f3f3f3f;
	REP(i, 0, n - 1) { scanf("%d", &Time[i]); dis[i][i] = 0; }
	REP(i, 1, m)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		dis[u][v] = dis[v][u] = w;
	}
	scanf("%d", &q);
	while ( q -- )
	{
		int u, v, t; scanf("%d%d%d", &u, &v, &t);
		if ( Time[u] > t || Time[v] > t ) 
		{
			printf("-1\n"); continue ;
		}
		while ( Time[K] <= t ) 
		{
			REP(i, 0, n - 1)	
				REP(j, 0, n - 1)
					dis[i][j] = min(dis[i][j], dis[i][K] + dis[K][j]);
			++ K;
		}
		printf("%d\n", dis[u][v] == 0x3f3f3f3f ? -1 : dis[u][v]);
	}
	return 0;
}

