/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年03月21日 星期日 10时30分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 6010 * 4;
const int INF = 1e18;
const int Mod = 1e9 + 7;

int n, a[4][maxn], dis[maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn], dt[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, ans;
bool vis[maxn];
priority_queue<pii> Q;

inline int Id(int x, int y) { return (x - 1) * n + y; } 

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); REP(i, 1, 3) REP(j, 1, n) scanf("%lld", &a[i][j]);
	REP(i, 1, 3) REP(j, 1, n) REP(o, 0, 3)
	{
		int x = i + dt[o][0], y = j + dt[o][1];
		if ( x < 1 || y < 1 || x > 3 || y > n ) continue ; 
		add(Id(i, j), Id(x, y), a[x][y]);
	}
	REP(s, 1, 3) REP(t, 1, n)
	{
		int pos = Id(s, t);
		REP(i, 1, n * 3) { dis[i] = INF; vis[i] = false; } 
		dis[pos] = a[s][t]; Q.push(pii(-dis[pos], pos));
		while ( !Q.empty() )  
		{
			int u = Q.top().second; Q.pop();
			if ( vis[u] ) continue ; vis[u] = true;
			for ( int i = Begin[u]; i; i = Next[i] ) 
			{
				int v = To[i];
				if ( dis[v] > dis[u] + W[i] ) 
				{
					dis[v] = dis[u] + W[i];
					if ( !vis[v] ) Q.push(pii(-dis[v], v)); 
				}
			}
		}
		REP(i, 1, n * 3) if ( i != pos ) ans = (ans + dis[i]) % Mod;
	}
	printf("%lld\n", ans);
    return 0;
}
