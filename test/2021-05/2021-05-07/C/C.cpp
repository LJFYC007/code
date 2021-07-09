/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年05月07日 星期五 11时16分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], ans;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u, int fa, int dep)
{
	if ( dep < 0 ) return ; 
	++ a[u];
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS(v, u, dep - 1);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
	scanf("%d", &m);
	while ( m -- ) 
	{
		int k; scanf("%d", &k);
		REP(i, 1, n) a[i] = 0; ans = 0;
		REP(i, 1, k) { int x, y; scanf("%d%d", &x, &y); DFS(x, 0, y); }
		REP(i, 1, n) if ( a[i] >= k - 1) ++ ans;
		printf("%d\n", ans);
	}
    return 0;
}
