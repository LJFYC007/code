/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年05月10日 星期五 15时08分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), -1, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10010;

int r, c, dt[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}}, vis[60][60];
char a[60][60], s[maxn], n;

struct node
{
	int x, y, s, now;
}p1, p2;

inline void BFS()
{
	queue<node> Q;
	p1.x = p1.y = 1; p1.s = 0; p1.now = 0;	
	mem(vis);
	Q.push(p1);
	int cnt = 0;
	while ( !Q.empty() ) 
	{
		++ cnt; if ( cnt == 10000 ) return ;
		p1 = Q.front(); Q.pop();
		if ( p1.now <= vis[p1.x][p1.y] ) continue ;
		printf("%d %d %d %d\n", p1.x, p1.y, p1.s, p1.now);
		vis[p1.x][p1.y] = p1.now;
		if ( p1.now == n ) { printf("%d\n", p1.s); return ; }
		REP(i, 0, 3)
		{
			p2.x = dt[i][0] + p1.x;
			p2.y = dt[i][1] + p1.y;
			if ( p2.x == 0 ) p2.x = r;
			if ( p2.x == r + 1 ) p2.x = 1;
			if ( p2.y == 0 ) p2.y = c;
			if ( p2.y == c + 1 ) p2.y = 1;
//			if ( p2.x < 1 || p2.y < 1 || p2.x > r || p2.y > c ) continue ;
			p2.s = p1.s + 1; p2.now = p1.now;
			if ( a[p2.x][p2.y] == s[p1.now] ) p2.now ++, p2.s ++;
			Q.push(p2);
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &r, &c);
	REP(i, 1, r) { getchar(); REP(j, 1, c) scanf("%c", &a[i][j]); }
	getchar(); scanf("%s", s);
	n = str(s);
	s[n ++] = '*';
	BFS();
    return 0;
}
