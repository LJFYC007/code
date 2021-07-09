/***************************************************************
	File name: ARC092F.cpp
	Author: ljfcnyali
	Create time: 2021年05月30日 星期日 14时58分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e3 + 10;
const int maxm = 2e5 + 10;

int n, m, a[2][maxn][maxn];
bool f[maxn][maxn], vis[maxn]; pii Edge[maxm];
vector<int> To[maxn];

inline void DFS(int u, int t)
{
	vis[u] = f[t][u] = true;
	for ( auto v : To[u] ) if ( !vis[v] ) DFS(v, t);
}

inline void DFS2(int u, int x, int y, int op)
{
	vis[u] = true; a[op][x][u] = y;
	for ( auto v : To[u] ) if ( !vis[v] ) DFS2(v, x, y, op);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m) 
	{
		int u, v; scanf("%d%d", &u, &v); 
		To[u].push_back(v); Edge[i] = pii(u, v);
	}
	REP(i, 1, n) 
	{ 
		mem(vis); DFS(i, i); 
		mem(vis); vis[i] = true; 
		for ( int j = 0; j < To[i].size(); ++ j ) if ( !vis[To[i][j]] ) DFS2(To[i][j], i, j, 0);
		mem(vis); vis[i] = true; reverse(To[i].begin(), To[i].end());
		for ( int j = 0; j < To[i].size(); ++ j ) if ( !vis[To[i][j]] ) DFS2(To[i][j], i, To[i].size() - j - 1, 1);
	}
	REP(i, 1, m) 
	{
		int u = Edge[i].first, v = Edge[i].second;
		if ( f[v][u] != (a[0][u][v] == a[1][u][v]) ) puts("same");
		else puts("diff");
	}
    return 0;
}
