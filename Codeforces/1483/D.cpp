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
#define int long long
typedef long long LL;

const int maxn = 610;
const int INF = 1e18;

int n, m, q, dis[maxn][maxn], a[maxn][maxn], limit[maxn], ans;
bool Map[maxn][maxn];
vector<pii> Edge[maxn];
struct node { int u, v, l; } p[maxn * maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n) REP(j, 1, n) if ( i != j ) dis[i][j] = INF;
	REP(i, 1, m)
	{
		int u, v, w; scanf("%lld%lld%lld", &u, &v, &w);
		a[u][v] = a[v][u] = dis[u][v] = dis[v][u] = w;
		Edge[u].push_back(pii(v, w));
		Edge[v].push_back(pii(u, w));
	}
	REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	scanf("%lld", &q);
	REP(i, 1, q) scanf("%lld%lld%lld", &p[i].u, &p[i].v, &p[i].l);
	REP(u, 1, n)
	{
		REP(i, 1, n) limit[i] = -INF;
		REP(i, 1, q)
		{
			limit[p[i].v] = max(limit[p[i].v], p[i].l - dis[p[i].u][u]);
			limit[p[i].u] = max(limit[p[i].u], p[i].l - dis[p[i].v][u]);
		}
		for ( auto it : Edge[u] ) 
		{
			int v = it.first;
			REP(i, 1, n) if ( limit[i] >= it.second + dis[v][i] && !Map[u][v] )
			{
				Map[u][v] = true;
				++ ans;
			}
		}
	}
	printf("%lld\n", ans / 2);
    return 0;
}
