/***************************************************************
	File name: ARC095F.cpp
	Author: ljfcnyali
	Create time: 2021年06月15日 星期二 15时19分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, s, t, Root, dis[maxn], pre[maxn], a[maxn], b[maxn], m;
vector<int> Edge[maxn];

inline void DFS(int u, int fa)
{
	if ( dis[u] > dis[Root] ) Root = u;
	for ( auto v : Edge[u] ) 
	{
		if ( v == fa ) continue ; 
		dis[v] = dis[u] + 1; pre[v] = u;
		DFS(v, u);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); Edge[u].push_back(v); Edge[v].push_back(u); }
	dis[1] = 1; DFS(1, 0); s = Root; 
	dis[s] = 1; pre[s] = 0; DFS(s, 0); t = Root;

	int x = t, sum = 0;
	while ( x ) 
	{
		sum += Edge[x].size() - 1;
		a[++ m] = Edge[x].size() - 2 + (x == t) + (x == s); x = pre[x];
	}
	if ( sum + 2 != n ) { puts("-1"); return 0; }
	REP(i, 1, m) b[i] = a[m - i + 1];
	REP(i, 1, m) 
		if ( a[i] < b[i] ) break ; 
		else if ( a[i] > b[i] ) 
		{
			REP(j, 1, m) a[j] = b[j];
			break ; 
		}

	x = 1;
	REP(i, 1, m)
	{
		REP(j, 1, a[i]) printf("%d ", x + j);
		printf("%d ", x); x += a[i] + 1;
	}
	puts("");
    return 0;
}
