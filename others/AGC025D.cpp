/***************************************************************
	File name: AGC025D.cpp
	Author: ljfcnyali
	Create time: 2021年04月27日 星期二 19时45分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 610;

int n, D[2], col[2][maxn * maxn], num[2][2];
vector<int> Edge[maxn * maxn]; pii p[maxn * maxn]; bool vis[maxn * maxn];

inline int Get(int x, int y) { return x * (n + n) + y + 1; }
inline void add(int u, int v) { Edge[u].push_back(v); Edge[v].push_back(u); } 

inline void DFS(int o, int u, int op)
{
	col[o][u] = op; 
	for ( auto v : Edge[u] ) if ( !vis[v] ) { vis[v] = true; DFS(o, v, op ^ 1); } 
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &D[0], &D[1]);
	REP(i, 0, n + n - 1) REP(j, 0, n + n - 1) p[Get(i, j)] = pii(i, j);
	REP(o, 0, 1)
	{
		mem(Edge); mem(vis);
		REP(i, 0, n + n - 1) REP(k, 0, n + n - 1)
		{
			int val = D[o] - (k - i) * (k - i), x = sqrt(val);
			if ( val < 0 || x * x != val ) continue ; 
			REP(j, 0, n + n - 1)
			{
				if ( j - x >= 0 ) add(Get(i, j), Get(k, j - x));
				if ( j + x < n + n ) add(Get(i, j), Get(k, j + x));
			}
		}
		REP(i, 1, n * n * 4) if ( !vis[i] ) { vis[i] = true; DFS(o, i, 0); }
	}
	REP(i, 1, n * n * 4) ++ num[col[0][i]][col[1][i]];
	int x, y; REP(i, 0, 1) REP(j, 0, 1) if ( num[i][j] >= n * n ) { x = i; y = j; } 
	int cnt = n * n;
	REP(i, 1, n * n * 4) if ( col[0][i] == x && col[1][i] == y ) 
	{
		printf("%d %d\n", p[i].first, p[i].second);
		-- cnt; if ( !cnt ) break ; 
	}
    return 0;
}
