/***************************************************************
	File name: P3388.cpp
	Author: ljfcnyali
	Create time: 2020年12月02日 星期三 16时33分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, dfn[maxn], low[maxn], cnt, ans;
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Tarjan(int u, int fa)
{
    int son = 0; dfn[u] = low[u] = ++ cnt;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( !dfn[v] ) 
        { 
            Tarjan(v, u); low[u] = min(low[u], low[v]); ++ son; 
            if ( fa != 0 && low[v] >= dfn[u] && !vis[u] ) { vis[u] = true; ++ ans; }
        }
        else low[u] = min(low[u], dfn[v]);
    }
    if ( fa == 0 && !vis[u] && son >= 2 ) { vis[u] = true; ++ ans; } 
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, n) if ( !dfn[i] ) Tarjan(i, 0);
    printf("%d\n", ans); REP(i, 1, n) if ( vis[i] ) printf("%d ", i); puts("");
    return 0;
}
