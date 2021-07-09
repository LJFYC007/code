/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年05月17日 星期五 10时18分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2000010;
const long long INF = 4557430888798830399;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, s, vis[maxn];
long long dis[maxn], ans[maxn];
bool flag;

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline void spfa(int u, int x)
{
	if ( flag == true ) return ;
	vis[u] = x;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i];
		if ( dis[v] > dis[u] + W[i] ) 
		{
			dis[v] = dis[u] + W[i];
			if ( !vis[v] ) spfa(v, x);
			if ( vis[v] == x ) { flag = true; return ; }
		}
	}
	vis[u] = 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("test7.in", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &s);
	REP(i, 1, m)
	{
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);
	}
	flag = false;
	memset ( dis, 0x3f, sizeof ( dis ) );
//	dis[s] = 0;
//	spfa(s, s);
//	REP(i, 1, n) ans[i] = dis[i];
	REP(i, 1, n)
		if ( dis[i] == INF ) 
		{
			dis[i] = 0;
			spfa(i, i);
			if ( flag == true ) break ;
		}
	if ( flag == true ) { printf("-1\n"); return 0; }
	REP(i, 1, n) 
		if ( ans[i] == INF ) printf("NoPath\n"); 
		else printf("%lld\n", dis[i]); 
    return 0;
}
