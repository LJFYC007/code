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

const int maxn = 4e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e = 1, f[maxn], size[maxn], pos, id, x, y, Max;
bool cut[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS1(int u, int fa)
{
	size[u] = 1; int x = 0;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa || cut[i] ) continue ; 
		DFS1(v, u); size[u] += size[v]; x = max(x, size[v]);
	}
	x = max(x, n - size[u]);
	if ( x < Max ) { Max = x; pos = u; }
}

inline void DFS(int u, int fa, int m)
{
	size[u] = 1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa || cut[i] ) continue ; 
		DFS(v, u, m); size[u] += size[v];
		if ( size[v] == f[m - 2] ) { x = v; y = u; id = i; }
	}
}

inline bool Solve(int m, int Root)
{
	if ( m <= 3 ) return true;
	n = f[m]; Max = n; DFS1(Root, 0);
	x = -1; DFS(pos, 0, m);
	if ( x == -1 ) return false;
	cut[id] = cut[id ^ 1] = true;
	int t1 = x, t2 =y;
	return Solve(m - 2, t1) && Solve(m - 1, t2);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
	f[0] = f[1] = 1; m = 1; while ( n > f[m] ) { ++ m; f[m] = f[m - 1] + f[m - 2]; } 
	if ( n == f[m] && Solve(m, 1) ) puts("YES");
	else puts("NO");
    return 0;
}
