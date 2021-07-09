/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年03月16日 星期二 20时10分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;
const int Mod = 998244353;

int n, Begin[maxn], Next[maxn], To[maxn], e, num, ans;
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int x)
{
	vis[x] = true;
	for ( int i = Begin[x]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( !vis[v] ) DFS(v);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) { int x; scanf("%d", &x); add(i, x); add(x, i); }
	ans = 1;
	REP(i, 1, n) if ( !vis[i] ) { vis[i] = true; ans = ans * 2 % Mod; DFS(i); } 	
	printf("%d\n", ans - 1);
    return 0;
}
