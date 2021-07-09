/***************************************************************
	File name: P6192.cpp
	Author: ljfcnyali
	Create time: 2021年03月29日 星期一 19时50分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, k, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], f[1 << 10][110];
queue<pii> Q;
bool vis[1 << 10][110];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &k);
	REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); } 
	memset(f, 0x3f, sizeof(f)); 
	REP(i, 1, k) { int x; scanf("%d", &x); f[1 << i - 1][x] = 0; Q.push(pii(1 << i - 1, x)); vis[1 << i - 1][x] = true; }
	while ( !Q.empty() ) 
	{
		pii x = Q.front(); Q.pop();
		for ( int i = Begin[x.second]; i; i = Next[i] ) 
		{
			int v = To[i];
			if ( f[x.first][v] > f[x.first][x.second] + W[i] ) 
			{
				f[x.first][v] = f[x.first][x.second] + W[i];
				if ( !vis[x.first][v] ) { vis[x.first][v] = true; Q.push(pii(x.first, v)); } 
			}
		}
		REP(i, 0, (1 << k) - 1) 
			if ( f[x.first | i][x.second] > f[x.first][x.second] + f[i][x.second] )
			{
				f[x.first | i][x.second] = f[x.first][x.second] + f[i][x.second];
				if ( !vis[x.first | i][x.second] ) { vis[x.first | i][x.second] = true; Q.push(pii(x.first | i, x.second)); } 
			}
		vis[x.first][x.second] = false;
	}
	int ans = 0x3f3f3f3f; REP(i, 1, n) ans = min(ans, f[(1 << k) - 1][i]); printf("%d\n", ans);
    return 0;
}
