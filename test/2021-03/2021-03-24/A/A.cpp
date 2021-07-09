#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int n, dis[11][11];
map<vector<int>, int> Map;

inline bool Check(vector<int> f)
{
	REP(i, 1, n) if ( f[i] == 0 ) return false;
	return true;
}

inline int Solve(vector<int> f)
{
	int ret = 0;
	REP(i, 1, n) REP(j, 1, n) if ( f[i] == 1 && f[j] == 1 ) ret = max(ret, dis[i][j]);
	return ret;
}

inline int DFS2(vector<int> f) ;

inline int DFS1(vector<int> f)
{
	if ( Map.count(f) ) return Map[f];
	if ( Check(f) ) return Solve(f);
	int Min = INF;
	REP(i, 1, n) if ( !f[i] ) { f[i] = 1; Min = min(Min, DFS2(f)); f[i] = 0; }
	Map[f] = Min; return Min;
}

inline int DFS2(vector<int> f)
{
	if ( Map.count(f) ) return Map[f];
	if ( Check(f) ) return Solve(f);
	int Max = 0;
	REP(i, 1, n) if ( !f[i] ) { f[i] = 2; Max = max(Max, DFS1(f)); f[i] = 0; }
	Map[f] = Max; return Max;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
#endif
	scanf("%d", &n); 
	REP(i, 1, n) REP(j, 1, n) if ( i != j ) dis[i][j] = INF;
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); dis[u][v] = dis[v][u] = 1; } 
	REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	vector<int> f(n + 1); 
	printf("%d\n", DFS1(f));
	return 0;
}
