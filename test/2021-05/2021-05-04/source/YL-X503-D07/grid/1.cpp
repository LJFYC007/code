#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 210;

int n, m, ans[maxn][maxn], match[maxn], col[maxn], Edge[maxn][maxn];
vector<int> a[maxn][maxn]; bool b[maxn][maxn][maxn];
bool vis[maxn];

inline bool DFS(int u)
{
	if ( vis[u] ) return false; vis[u] = true;
	REP(i, 1, n) if ( Edge[u][i] > 0 && (!match[i] || DFS(match[i])) ) 
	{
		match[i] = u; 
		REP(j, 1, m) if ( b[u][i][j] ) { col[i] = j; break ; } 
		return true;
	}
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n) REP(j, 1, n) 
	{
		Edge[i][j] = n;
		REP(k, 1, m - n) { int x; scanf("%d", &x); vis[x] = true; }
		REP(k, 1, m) 
		{
			if ( !vis[k] ) { b[i][j][k] = true; a[i][k].push_back(j); }
			vis[k] = false;
		}
	}
	REP(o, 1, n)
	{
		REP(i, 1, n) match[i] = 0;
		REP(i, 1, n) { mem(vis); DFS(i); }
		REP(i, 1, n) 
		{ 
			cout << "(" << match[i] << " " << col[i] << ") "; 
			ans[match[i]][i] = col[i]; 
			Edge[match[i]][i] = 0;
			for ( auto it : a[match[i]][col[i]] ) { -- Edge[match[i]][it]; b[match[i]][it][col[i]] = false; } 
			a[match[i]][col[i]].clear(); 
		}
		cout << endl;
	}
	REP(i, 1, n) { REP(j, 1, n) printf("%d ", ans[i][j]); puts(""); } 
	return 0;
}
