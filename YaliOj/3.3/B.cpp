/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月17日 星期五 08时58分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10010;

int Begin[maxn], Next[maxn], To[maxn], e, W1[maxn], W2[maxn];
int n, m, s, t, dis[110][maxn], sum, ans;
bool vis[110][maxn], f[110][maxn];

struct node
{
	int x, dis;
} p1, p2;

inline void add(int u, int v, int w1, int w2)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W1[e] = w1;
	W2[e] = w2;
}

inline void Solve()
{
	queue<node> Q;
	p1.x = s; p1.dis = 0;
	Q.push(p1);
	memset ( dis, 0x3f, sizeof ( dis ) );
	dis[s][0] = 0; f[s][0] = 1;
	while ( !Q.empty() ) 
	{
		p1 = Q.front(); Q.pop();
//		printf("%d %d\n", p1.x, p1.dis);
		vis[p1.x][p1.dis] = false;
		for ( int i = Begin[p1.x]; i; i = Next[i] )
		{
			int v = To[i];
			if ( p1.dis + W1[i] > sum ) continue ;
			if ( dis[p1.x][p1.dis] + W2[i] < dis[v][p1.dis + W1[i]] )
			{
				dis[v][p1.dis + W1[i]] = dis[p1.x][p1.dis] + W2[i];
				p2.x = v; p2.dis = p1.dis + W1[i];
				f[p2.x][p2.dis] = 1;
				if ( !vis[p2.x][p2.dis] )
				{
					vis[p2.x][p2.dis] = true;
					Q.push(p2);
				}
			}
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d%d", &n, &m, &s, &t);
	REP(i, 1, m)
	{
		int u, v, w1, w2; 
		scanf("%d%d%d%d", &u, &v, &w1, &w2);
		add(u, v, w1, w2);
		add(v, u, w1, w2);
	}
	sum = 100 * (n - 1) + 1;
	Solve();
	int Min = 0x3f3f3f3f;
//	REP(i, 1, n) REP(j, 0, 10) printf("%d %d %d\n", i, j, dis[i][j]);
	REP(i, 0, 10000)
	{
		if ( !f[t][i] ) continue ;
		if ( dis[t][i] < Min ) 
		{
			++ ans;
			Min = dis[t][i];
		}
	}
	printf("%d\n", ans);
    return 0;
}
