/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月18日 星期六 10时07分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;
const int INF = 0x3f3f3f3f;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m1, m2, dis[maxn], cnt[maxn];
bool vis[maxn];
int Vis[maxn];

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline void spfa(int u, int x)
{
	Vis[u] = x;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i];
		if ( dis[v] < dis[u] + W[i] ) 
		{
			dis[v] = dis[u] + W[i];
			if ( !Vis[v] ) spfa(v, x);
			if ( Vis[v] == x ) { printf("-1\n"); exit(0); }
		}
	}
	Vis[u] = 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m1, &m2);
	REP(i, 1, m1)
	{
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		add(u, v, -w);
	}
	REP(i, 1, m2)
	{
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		add(v, u, w);
	}
	queue<int> Q; Q.push(1);
	REP(i, 2, n) dis[i] = -INF;
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		vis[u] = false;
		if ( cnt[u] == n - 1 ) { printf("-1\n"); return 0; }
		++ cnt[u];
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i];
			if ( dis[v] < dis[u] + W[i] )
			{
				dis[v] = dis[u] + W[i];
				if ( !vis[v] ) 
				{
					vis[v] = true;
					Q.push(v);
				}
			}
		}
	}
	int ans = dis[n];
	REP(i, 1, n) dis[i] = -INF;
	REP(i, 1, n) if ( dis[i] == -INF) { dis[i] = 0; spfa(i, i); }
	if ( ans == -INF ) printf("-2\n");
	else printf("%d\n", abs(ans));
    return 0;
}
