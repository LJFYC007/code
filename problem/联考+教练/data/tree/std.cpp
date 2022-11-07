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

const int maxn = 1e6 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, ans, deg[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[v]; } 

inline int DFS(int u, int fa)
{
	if ( deg[u] == 1 ) return 1;
	int num1 = 0, num2 = 0;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		int x = DFS(v, u);
		if ( x == 1 ) ++ num1;
		if ( x == 2 ) ++ num2;
	}

	while ( num1 > 2 ) { num1 -= 2; ++ ans; } 
	while ( num2 > 1 ) { num2 -= 2; ++ ans; } 
	if ( num1 == 2 && num2 == 1 ) { num1 = 1; num2 = 0; ++ ans; } 

	return min(2, num1 + 2 * num2);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("tree10.in", "r", stdin);
	freopen("tree10.out", "w", stdout);
#endif
	scanf("%d", &n);
	if ( n <= 3 ) { puts("1"); return 0; } 
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
	int Root = 1;
	REP(i, 2, n) if ( deg[i] != 1 ) Root = i;
	int x = DFS(Root, 0);	
	if ( x >= 2 ) ++ ans;
	printf("%d\n", ans);
    return 0;
}
