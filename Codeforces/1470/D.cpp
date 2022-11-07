/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e;
bool use[maxn], vis[maxn], visit[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
	if ( visit[u] ) return ; visit[u] = true;
	if ( use[u] ) for ( int i = Begin[u]; i; i = Next[i] ) vis[To[i]] = true;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i];
		if ( !vis[v] ) { vis[v] = use[v] = true; DFS(v); }
		else DFS(v);
	}
}

inline bool Check()
{
	REP(i, 1, n) vis[i] = false;
	REP(i, 1, n) if ( use[i] )
	{
		vis[i] = true;
		for ( int j = Begin[i]; j; j = Next[j] ) vis[To[j]] = true;
	}
	REP(i, 1, n) if ( !vis[i] ) return false;
	return true;
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
		scanf("%d%d", &n, &m); REP(i, 1, n) Begin[i] = vis[i] = visit[i] = use[i] = 0; e =0 ;
		REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
		vis[1] = use[1] = true; DFS(1);
		if ( Check() )
		{
			puts("YES");
			int sum = 0; REP(i, 1, n) if ( use[i] ) ++ sum;
			printf("%d\n", sum); REP(i, 1, n) if ( use[i] ) printf("%d ", i); puts("");
		}
		else puts("NO");
	}
    return 0;
}
