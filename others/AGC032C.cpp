/***************************************************************
	File name: AGC032C.cpp
	Author: ljfcnyali
	Create time: 2021年01月16日 星期六 17时12分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, deg[maxn], Begin[maxn], Next[maxn], To[maxn], e, s, t;
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( !vis[v] && deg[v] < 4 ) DFS(v);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m); if ( m <= n + 1 ) { puts("No"); return 0; } 
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); ++ deg[u]; ++ deg[v]; } 
    REP(i, 1, n) if ( deg[i] % 2 != 0 ) { puts("No"); return 0; } 
    int num = 0; REP(i, 1, n) if ( deg[i] > 4 ) num = -100000000; else if ( deg[i] == 4 ) ++ num;
    if ( num < 0 || num > 2 ) { puts("Yes"); return 0; } 
    REP(i, 1, n) if ( deg[i] == 4 ) { if ( !s ) s = i; else t = i; }
    num = 0;
    for ( int i = Begin[s]; i; i = Next[i] ) 
        if ( !vis[To[i]] ) { ++ num; DFS(To[i]); }

    if ( num != 3 ) puts("No");
    else puts("Yes");
    return 0;
}
