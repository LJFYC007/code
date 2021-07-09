/***************************************************************
	File name: LibreOJ_2330.cpp
	Author: ljfcnyali
	Create time: 2020年08月09日 星期日 08时28分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, size[maxn], Max[maxn], son1[maxn], son2[maxn], ans[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    size[u] = 1; son1[u] = son2[u] = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u); size[u] += size[v];
        if ( size[v] >= size[son1[u]] ) { son2[u] = son1[u]; son1[u] = v; }
        else if ( size[v] > size[son2[u]] ) son2[u] = v;
    }
    if ( size[u] + 2 * Max[son1[u]] - 1 - size[son1[u]] >= size[son1[u]] ) Max[u] = (size[u] - 1) / 2;
    else Max[u] = Max[son1[u]] + size[u] - 1 - size[son1[u]];
}

inline void DFS1(int u, int fa, int son, int dep)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( v == son1[u] ) DFS1(v, u, size[son] > size[son2[u]] ? son : son2[u], dep + 1);
        else DFS1(v, u, size[son] > size[son1[u]] ? son : son1[u], dep + 1);
    }
    son = size[son] > size[son1[u]] ? son : son1[u];
    int num = n - dep - 1; 
    if ( num + 2 * Max[son] - size[son] >= size[son] && !(num & 1) ) ans[u] = 1; 
    else ans[u] = 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int W, T; scanf("%d%d", &W, &T);
    while ( T -- ) 
    {
        scanf("%d", &n); e = 0; mem(Begin);
        REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
        DFS(1, 0);
        DFS1(1, 0, 0, 0);
        if ( W == 3 ) { printf("%d", ans[1]); puts(""); continue ; }
        REP(i, 1, n) printf("%d", ans[i]); puts("");
    }
    return 0;
}
