#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 210;

int n, m, ans[maxn][maxn];
vector<pii> a; vector<int> b;
bool vis[maxn][maxn][maxn];

inline bool Check()
{
	REP(i, 1, n) REP(j, 1, n) if ( !vis[i][j][ans[i][j]] ) return false;
	return true;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m); 
	REP(i, 1, n) REP(j, 1, n) ans[i][j] = (i + j - 2) % n + 1;
	memset(vis, true, sizeof(vis));
	REP(i, 1, n) REP(j, 1, n) REP(k, 1, m - n) { int x; scanf("%d", &x); vis[i][j][x] = false; }

	while ( !Check() ) 
	{
		int x, y;
		if ( rand() % 10 != 0 ) 
		{
			REP(i, 1, n) REP(j, 1, n) if ( !vis[i][j][ans[i][j]] ) a.push_back(pii(i, j));
			int id = rand() % a.size(); x = a[id].first, y = a[id].second; a.clear();
		}
		else x = rand() % n + 1, y = rand() % n + 1;
		REP(i, 1, m) if ( vis[x][y][i] )
		{
			REP(j, 1, n) if ( ans[x][j] == i || ans[j][y] == i ) goto Next;
			b.push_back(i);
Next : ; 
		}
		if ( b.size() ) ans[x][y] = b[rand() % b.size()];
		b.clear();
	}

	REP(i, 1, n) { REP(j, 1, n) printf("%d ", ans[i][j]); puts(""); } 
	return 0;
}
