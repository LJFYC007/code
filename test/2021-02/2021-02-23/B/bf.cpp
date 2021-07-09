/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年02月23日 星期二 14时44分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e6 + 10;
const int Mod = 10007;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, ans, num;
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u)
{
	++ num; vis[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] ) if ( !vis[To[i]] ) DFS(To[i]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &q);
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
	while ( q -- ) 
	{
		int op, x, y; scanf("%d", &op);
		if ( op == 1 ) 
		{ 
			scanf("%d", &x); REP(i, 1, n) vis[i] = false; vis[x] = true; ans = 0;
			REP(i, 1, n) if ( !vis[i] ) { num = 0; DFS(i); num %= Mod; ans = (ans + num * num) % Mod; }
			printf("%d\n", ans);
		}
		else { scanf("%d%d", &x, &y); add(x, y); add(y, x); } 
	}
    return 0;
}
