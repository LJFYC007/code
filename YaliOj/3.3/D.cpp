/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月17日 星期五 10时11分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, w, dis[maxn];
bool vis[maxn], flag;

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline void spfa(int u)
{
	if ( flag == true ) return ;
	vis[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i];
		if ( dis[v] > dis[u] + W[i] ) 
		{
			dis[v] = dis[u] + W[i];
			if ( !vis[v] ) spfa(v);
			if ( vis[v] == true ) { flag = true; return ; }
		}
	}
	vis[u] = false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while ( T -- ) 
	{
		mem(Begin); e = 0; memset(dis, 0x3f, sizeof(dis)); mem(vis); flag = false;
		scanf("%d%d%d", &n, &m, &w);
		REP(i, 1, m)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			add(u, v, w); add(v, u, w);
		}
		REP(i, 1, w)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			add(u, v, -w);
		}
		dis[1] = 0;
		spfa(1);
//		REP(i, 1, n) printf("%d ", dis[i]);
		if ( flag == true ) printf("YES\n");
		else printf("NO\n");
	}
    return 0;
}
