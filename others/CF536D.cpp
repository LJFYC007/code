/***************************************************************
	File name: CF536D.cpp
	Author: ljfcnyali
	Create time: 2021年04月28日 星期三 10时02分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long

const int maxn = 2010;
const int maxm = 2e5 + 10;
const int INF = 1e18;

int n, m, n1, n2, Begin[maxn], Next[maxm], To[maxm], e, W[maxm], dis[maxn][maxn];
int f[maxn][maxn], g[maxn][maxn], a[maxn], s, t, h[maxn][maxn], num[maxn][maxn]; 
int val1[maxn][maxn], val2[maxn][maxn], nxt1[maxn][maxn], nxt2[maxn][maxn];
bool vis[maxn]; queue<int> Q;
map<int, int> Map1, Map2; vector<int> p1[maxn], p2[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

inline void SPFA(int s)
{
	mem(vis); REP(i, 1, n) dis[s][i] = INF; dis[s][s] = 0; Q.push(s);
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		for ( int i = Begin[u]; i; i = Next[i] )
		{
			int v = To[i];
			if ( dis[s][v] > dis[s][u] + W[i] ) 
			{
				dis[s][v] = dis[s][u] + W[i];
				if ( !vis[v] ) { vis[v] = true; Q.push(v); }
			}
		}
		vis[u] = false;
	}
}

inline int Get(int a, int b, int c, int d) { return h[b][d] - h[a - 1][d] - h[b][c - 1] + h[a - 1][c - 1]; }
inline bool Check(int a, int b, int c, int d) { return num[b][d] - num[a - 1][d] - num[b][c - 1] + num[a - 1][c - 1] > 0; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
	REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 1, m) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); } 
	SPFA(s); SPFA(t); REP(i, 1, n) Map1[dis[s][i]] = Map2[dis[t][i]] = true;	
	for ( auto it : Map1 ) Map1[it.first] = ++ n1; for ( auto it : Map2 ) Map2[it.first] = ++ n2;
	REP(i, 1, n) 
	{ 
		int x = Map1[dis[s][i]], y = Map2[dis[t][i]];
		p1[x].push_back(i); p2[y].push_back(i); h[x][y] += a[i]; ++ num[x][y];
	}
	REP(i, 1, n1) REP(j, 1, n2) 
	{
		h[i][j] += h[i - 1][j] + h[i][j - 1] - h[i - 1][j - 1];
		num[i][j] += num[i - 1][j] + num[i][j - 1] - num[i - 1][j - 1];
	}
	REP(i, 1, n1 + 1) REP(j, 1, n2 + 1) { val1[i][j] = -INF; val2[i][j] = INF; }

	for ( int i = n1; i >= 1; -- i ) for ( int j = n2; j >= 1; -- j ) 
	{
		if ( Check(i + 1, i + 1, j, n2) ) nxt1[i][j] = i + 1; 
		else nxt1[i][j] = nxt1[i + 1][j];
		val1[i][j] = max(Check(i, i, j, n2) ? g[nxt1[i][j]][j] : -INF, val1[i + 1][j]) + Get(i, i, j, n2);

		if ( Check(i, n1, j + 1, j + 1) ) nxt2[i][j] = j + 1; 
		else nxt2[i][j] = nxt2[i][j + 1];
		val2[i][j] = min(Check(i, n1, j, j) ? f[i][nxt2[i][j]] : INF, val2[i][j + 1]) - Get(i, n1, j, j);

		int Max = val1[i][j], Min = val2[i][j];
		if ( Max < -INF / 2 ) Max = 0; if ( Min > INF / 2 ) Min = 0;
		f[i][j] = Max; g[i][j] = Min;
	}
	if ( f[1][1] > 0 ) puts("Break a heart");
	else if ( f[1][1] < 0 ) puts("Cry");
	else puts("Flowers");
    return 0;
}
