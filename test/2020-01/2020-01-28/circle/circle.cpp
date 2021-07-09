
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;

int a[maxn][maxn], f[maxn], n, k, deg[maxn], dp[maxn];
int p1[maxn], p2[maxn], ans;
bool vis[maxn], use[maxn];

inline void Toposort()
{
	queue<int> Q;
	REP(i, 1, n) if ( vis[i] ) REP(j, 1, n) if ( vis[j] && a[i][j] ) ++ deg[j];
	REP(i, 1, n) if ( vis[i] && !deg[i] ) { Q.push(i); use[i] = true; }
	int x = 0;
	while ( !Q.empty() )
	{
		int u = Q.front(); Q.pop(); p1[++ x] = u;
		REP(i, 1, n) if ( vis[i] && a[u][i] && !use[i] ) { -- deg[i]; if ( !deg[i] ) { use[i] = true; Q.push(i); } }
	}
	if ( x != k ) { puts("impossible"); exit(0); }

	REP(i, 1, n) if ( !vis[i] ) REP(j, 1, n) if ( !vis[j] && a[i][j] ) ++ deg[j];
	REP(i, 1, n) if ( !vis[i] && !deg[i] ) { Q.push(i); use[i] = true; }
	x = 0;
	while ( !Q.empty() )
	{
		int u = Q.front(); Q.pop(); p2[u] = ++ x;
		REP(i, 1, n) if ( !vis[i] && a[u][i] && !use[i] ) { -- deg[i]; if ( !deg[i] ) { use[i] = true; Q.push(i); } }
	}
}

int main()
{
	freopen("circle.in", "r", stdin);
	freopen("circle.out", "w", stdout);
	scanf("%d%d", &n, &k);
	REP(i, 1, n) REP(j, 1, n) scanf("%d", &a[i][j]);
	REP(i, 1, k) { int x; scanf("%d", &x); vis[x] = true; }
	Toposort();
	mem(use);
	REP(i, 1, n) if ( !vis[i] )
	{
		REP(j, 2, k) if ( a[i][p1[j - 1]] && a[p1[j]][i] ) { ++ ans; use[i] = true; break ; }
		if ( use[i] ) continue ;
		f[p2[i]] = k + 1;
		for ( int j = k; j >= 1; -- j ) if ( a[i][p1[j]] ) f[p2[i]] = j;
	}
	int Max = 0;
	REP(i, 1, n - k)
	{
		if ( !f[i] ) continue ;
		REP(j, 0, i - 1) if ( f[j] <= f[i] ) dp[i] = max(dp[i], dp[j] + 1);
		Max = max(Max, dp[i]);
	}
	ans += n - k - ans - Max;
	if ( ans >= k ) puts("impossible");
	else printf("%d\n", ans);
	return 0;
}
