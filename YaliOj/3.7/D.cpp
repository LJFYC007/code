/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月23日 星期四 14时10分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 4010;

int n, m, Begin[maxn], To[maxn], Next[maxn], W[maxn], e;
int degree[maxn];
bool vis[maxn];
vector<int> ans;

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline void DFS(int u)
{
	for ( int &i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i], p = W[i];
		if ( vis[p] ) continue ;
		vis[p] = true; DFS(v);
		ans.push_back(p);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("trip.in", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	while ( 1 ) 
	{
		ans.clear(); mem(Begin); mem(degree); mem(vis); e = n = m = 0; mem(To); mem(Next);
		int u, v, w, s;
		scanf("%d%d", &u, &v); s = min(u, v);
		if ( u == 0 && v == 0 ) break ; 
		scanf("%d", &w); add(u, v, w); add(v, u, w); ++ m; n = max(n, max(u, v));
		++ degree[u]; ++ degree[v];
		while ( 1 )
		{
			scanf("%d%d", &u, &v); if ( u == 0 && v == 0 ) break ; scanf("%d", &w);
			add(u, v, w); add(v, u, w); ++ m; n = max(n, max(u, v));
			++ degree[u]; ++ degree[v];
		}
		REP(i, 1, n) if ( degree[i] % 2 == 1 ) { printf("Round trip does not exist.\n"); goto finish; }
		DFS(s);
		if ( ans.size() != m ) { printf("Round trip does not exist.\n"); goto finish; }
		for ( int i = ans.size() - 1; i > 0; -- i ) printf("%d ", ans[i]); printf("%d\n", ans[0]);
finish: ;
	}
    return 0;
}
