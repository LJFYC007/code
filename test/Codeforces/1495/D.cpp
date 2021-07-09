/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2021年03月10日 星期三 20时55分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1210;
const int Mod = 998244353;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn][maxn], ans;
bool vis[maxn][maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void BFS(int x)
{
	queue<int> Q; Q.push(x); vis[x][x] = true;
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i]; if ( vis[x][v] ) continue ;
			dis[x][v] = dis[x][u] + 1; vis[x][v] = true; Q.push(v);
		}
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m);
	REP(i, 1, m) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); } 	
	REP(i, 1, n) BFS(i);
	REP(x, 1, n) REP(y, 1, n)
	{
		ans = 1; int sum = x == y ? 0 : 1;
		REP(i, 1, n) if ( i != x && i != y ) 
		{
			if ( dis[x][i] + dis[y][i] == dis[x][y] ) { ++ sum; continue ; } 
			int num = 0;
			for ( int j = Begin[i]; j; j = Next[j] ) 
			{
				int v = To[j]; 
				if ( dis[x][v] == dis[x][i] - 1 && dis[y][v] == dis[y][i] - 1 ) ++ num;
			}
			ans = ans * num % Mod;
		}
		if ( sum > dis[x][y] ) ans = 0;
		printf("%lld ", ans); if ( y == n ) puts("");
	}
    return 0;
}
