/***************************************************************
	File name: G.cpp
	Author: ljfcnyali
	Create time: 2019年05月23日 星期四 15时59分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1010;

int n, degree[maxn], sum[maxn], f[maxn], ans1, ans2, m;
bool vis[maxn];

inline int cha(int x)
{
	return x == f[x] ? x : f[x] = cha(f[x]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, 1000) f[i] = i;
	REP(i, 1, n)
	{
		int u, v; scanf("%d%d", &u, &v);
		++ degree[u]; -- degree[v];
		int fx = cha(u), fy = cha(v); vis[u] = vis[v] = true;
		if ( fx != fy ) f[fx] = fy;
		m = max(m, max(u, v));
	}
	REP(i, 1, m)
	{
		if ( !vis[i] ) continue ;
		sum[cha(i)] += abs(degree[i]);
	}
	REP(i, 1, m) if ( vis[i] && cha(i) == i ) 
	{
		if ( sum[i] == 0 ) ++ ans1;
		else ans2 += sum[i];
	}
	printf("%d\n", n + ans1 + ans2 / 2);
    return 0;
}
