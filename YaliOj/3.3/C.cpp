/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月17日 星期五 09时38分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxm = 2000010;
const int maxn = 10010;
const double eps = 0.000000001;

int Begin[maxm], Next[maxm], To[maxm], e;
int n, m, vis[maxn];
double aver, ans = 0x3f3f3f3f3f3f, dis[maxn], W[maxn], Max = -0x3f3f3f3f3f3f, Min = 0x3f3f3f3f3f3f;
bool flag;

inline void add(int u, int v, double w)
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
		if ( (double) dis[v] > (double) dis[u] + W[i] - aver ) 
		{
			dis[v] = (double) dis[u] + W[i] - aver;
			if ( !vis[v] ) spfa(v, x);
//			if ( dis[v] > Max * n ) { flag = true; return ; } 
			if ( vis[v] == x ) { flag = true; return ; }
		}
	}
	vis[u] = 0;
}

inline bool solve() 
{
	mem(vis); mem(dis);
	flag = false;
	REP(i, 1, n) 
	{
		spfa(i, i);
		if ( flag == true ) return true;
	}
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m)
	{
		int u, v; double w;
		scanf("%d%d%lf", &u, &v, &w);
		add(u, v, w);
		Max = max(Max, w);
		Min = min(Min, w);
	}
	double L = Min, R = Max;
	while ( L <= R ) 
	{
		aver = (L + R) / 2;
		if ( solve() ) { ans = min(ans, aver); R = aver - eps; }
		else L = aver + eps;
	}
	printf("%.8lf\n", ans);
    return 0;
}
