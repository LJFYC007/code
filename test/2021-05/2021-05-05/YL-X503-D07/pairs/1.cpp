/***************************************************************
	File name: pairs.cpp
	Author: ljfcnyali
	Create time: 2021年05月05日 星期三 09时46分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, Begin[maxn], Next[maxn], To[maxn], e, match[maxn];
bool vis[1010];

inline void add(int u, int v) 
{ 
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e;
	swap(u, v);
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e;
}

inline bool DFS(int u)
{
	if ( vis[u] ) return false; vis[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i];
		if ( !match[v] || DFS(match[v]) ) 
		{
			match[u] = v; match[v] = u;
			return true;
		}
	}
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("pairs.in", "r", stdin);
    freopen("pairs.out", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d", &n); e = 0; REP(i, 1, n) Begin[i] = match[i] = 0;
		for ( int i = 2; i <= n + n; i <<= 1 ) 
			REP(j, 1, n) if ( j < i - j && i - j >= 1 && i - j <= n ) add(j, i - j);
		int ans = 0;
		REP(i, 1, n) { mem(vis); if ( !match[i] && DFS(i) ) ++ ans; } 
		printf("%d\n", ans);
	}
    return 0;
}
