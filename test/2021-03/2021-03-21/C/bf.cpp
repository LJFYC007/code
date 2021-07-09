/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年03月21日 星期日 10时31分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int n, m, dis[maxn][maxn][4], dt[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
LL ans;
bool a[maxn][maxn], vis[maxn][maxn][4];
struct node { int x, y, op; } ;
queue<node> Q;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m) { int x, y; scanf("%d%d", &x, &y); a[x][y] = true; } 
	memset(dis, 0x3f, sizeof(dis)); dis[1][1][0] = 0; vis[1][1][0] = true; Q.push({1, 1, 0});
	while ( !Q.empty() ) 
	{
		node u = Q.front(); Q.pop();
		REP(i, 0, 3)
		{
			int x = u.x + dt[i][0], y = u.y + dt[i][1];
			if ( x < 1 || y < 1 || x > n || y > n || a[x][y] ) continue ; 
			if ( dis[x][y][i] > dis[u.x][u.y][u.op] + (u.op != i) )
			{
				dis[x][y][i] = dis[u.x][u.y][u.op] + (u.op != i);
				if ( !vis[x][y][i] ) { vis[x][y][i] = true; Q.push({x, y, i}); }
			}
		}
		vis[u.x][u.y][u.op] = false;
	}
	REP(i, 1, n) REP(j, 1, n) 
	{ 
		int Min = 0x3f3f3f3f; 
		REP(o, 0, 3) Min = min(Min, dis[i][j][o]); 
		if ( Min != 0x3f3f3f3f ) ans += Min; 
	} 	
	printf("%lld\n", ans);
    return 0;
}
