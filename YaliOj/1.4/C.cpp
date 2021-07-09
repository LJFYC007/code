/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月10日 星期五 13时26分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int T, n, t1, t2;
int dt[8][2] = {{2, 1}, {1, 2}, {1, -2}, {2, -1}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}};
bool vis[500][500];

struct node
{
	int x, y, sum;
}p1, p2;

inline void BFS()
{
	mem(vis);
	queue<node> Q;
	p1.sum = 0;
	Q.push(p1);
	while ( !Q.empty() )
	{
		p1 = Q.front(); Q.pop();
		if ( vis[p1.x][p1.y] ) continue;
		vis[p1.x][p1.y] = true;
		//cerr << p1.x << " " << p1.y << " " << p1.sum << endl;
		if ( p1.x == t1 && p1.y == t2 ) 
		{ 
			printf("%d\n", p1.sum);
			break ;
		}
		REP(i, 0 ,7)
		{
			p2.x = p1.x + dt[i][0];
			p2.y = p1.y + dt[i][1];
			if ( p2.x < 0 || p2.y < 0 || p2.x > n || p2.y > n ) continue ;
			p2.sum = p1.sum + 1;
			Q.push(p2);
		}
	}
	while ( !Q.empty() ) Q.pop();
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d", &n);
		scanf("%d%d%d%d", &p1.x, &p1.y, &t1, &t2);
		BFS();
	}
    return 0;
}
