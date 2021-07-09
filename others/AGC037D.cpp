/***************************************************************
	File name: AGC037D.cpp
	Author: ljfcnyali
	Create time: 2021年01月28日 星期四 18时58分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 210;
const int maxm = 210 * 210 * 2;

int n, m, k, a[maxn][maxn], id[maxn][maxn], Begin[maxm], Next[maxm], To[maxm], e, match[maxm], b[maxn][maxn];
pii belong[maxm];
bool vis[maxm];
map<int, int> Map[maxn];

inline void add(int u, int v) 
{
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ Map[u][v];
	swap(u, v);
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ Map[u][v];
}

inline int DFS(int u)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( vis[v] || !Map[u][v] ) continue ; 
		vis[v] = true;
		if ( !match[v] || DFS(match[v]) ) { match[u] = v; match[v] = u; return 1; }
	}
	return 0;
}

inline int Get(int x, int y)
{
	REP(i, 1, m) if ( belong[a[x][i]].x == y ) { int t = a[x][i]; a[x][i] = 0; return t; }
	return 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n) REP(j, 1, m) scanf("%d", &a[i][j]);
	REP(i, 1, n) REP(j, 1, m) { belong[++ k] = pii(i, j); id[i][j] = k; } 
	REP(i, 1, n) REP(j, 1, m) add(i, n + belong[a[i][j]].x);
	REP(o, 1, m)
	{
		REP(i, 1, n) { REP(j, 1, n) vis[n + j] = false; DFS(i); } 
		REP(i, 1, n) 
		{ 
			-- Map[i][match[i]]; -- Map[match[i]][i];
			b[i][o] = Get(i, match[i] - n);
		}
		REP(i, 1, n + n) match[i] = 0;
	}
	REP(i, 1, n) { REP(j, 1, m) printf("%d ", b[i][j]); puts(""); }
	REP(i, 1, m) 
	{
		vector<int> p; REP(j, 1, n) p.push_back(b[j][i]);
		sort(p.begin(), p.end());
		REP(j, 1, n) b[j][i] = p[j - 1];
	}
	REP(i, 1, n) { REP(j, 1, m) printf("%d ", b[i][j]); puts(""); }
    return 0;
}
