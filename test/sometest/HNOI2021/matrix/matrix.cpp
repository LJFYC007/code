/***************************************************************
	File name: matrix.cpp
	Author: ljfcnyali
	Create time: 2021年04月16日 星期五 14时45分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 610;
const int INF = 4e6 + 10;
const int M = 1e9;
const int N = 1e6;

int T, n, m, a[maxn][maxn], b[maxn][maxn], dis[maxn], Edge[maxn][maxn];
bool vis[maxn];

inline void add(int u, int v, int w) { Edge[u][v] = min(Edge[u][v], w); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d%d", &n, &m); mem(a); REP(i, 1, n + m) REP(j, 1, n + m) Edge[i][j] = INF;
		REP(i, 1, n - 1) REP(j, 1, m - 1) scanf("%d", &b[i][j]);
		REP(i, 2, n) REP(j, 2, m) a[i][j] = b[i - 1][j - 1] - a[i - 1][j] - a[i][j - 1] - a[i - 1][j - 1];
		REP(i, 1, n) REP(j, 1, m) if ( !(i + j & 1) )
		{
			add(i, n + j, a[i][j]);
			add(n + j, i, N - a[i][j]);
		}
		else
		{
			add(n + j, i, a[i][j]);
			add(i, n + j, N - a[i][j]);
		}
		REP(i, 1, n + m) dis[i] = INF; dis[1] = 0; 
		REP(o, 1, n + m) 
		{
			bool flag = false;
			REP(u, 1, n + m) 
			{
				int l, r;
				if ( u <= n ) { l = n + 1; r = n + m; } 
				else { l = 1; r = n; }
				REP(v, l, r) if ( dis[v] > dis[u] + Edge[u][v] ) { dis[v] = dis[u] + Edge[u][v]; if ( dis[v] < -M ) { puts("NO"); goto Next ; } flag = true; }
			}
			if ( !flag ) break ; 
		}
		REP(u, 1, n + m) REP(v, 1, n + m) if ( dis[v] > dis[u] + Edge[u][v] ) { dis[v] = dis[u] + Edge[u][v]; puts("NO"); goto Next; } 
		REP(i, 1, n) REP(j, 1, m) a[i][j] += (i + j & 1 ? 1 : -1) * (dis[n + j] - dis[i]);
		puts("YES");
		REP(i, 1, n) { REP(j, 1, m) printf("%d ", a[i][j]); puts(""); }
Next : ; 
	}
    return 0;
}
