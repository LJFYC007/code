/***************************************************************
	File name: CF555E.cpp
	Author: ljfcnyali
	Create time: 2021年01月17日 星期日 20时07分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, cnt, dfn[maxn], low[maxn];
int p[maxn], Stack[maxn], tot, f1[maxn], f2[maxn], dis[maxn], vis[maxn], anc[maxn][20];
vector<int> Edge[maxn];
map<int, int> Map1[maxn], Map2[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    dfn[u] = low[u] = ++ cnt; Stack[++ tot] = u;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        if ( !dfn[v] ) { DFS(v, u); low[u] = min(low[u], low[v]); }
        else if ( !p[v] ) low[u] = min(low[u], dfn[v]);
    }
    if ( dfn[u] == low[u] ) 
    {
        ++ m; p[u] = m;
        while ( Stack[tot] != u ) { p[Stack[tot]] = m; -- tot; }
        -- tot;
    }
}

inline void DFS1(int u, int fa) 
{ 
    vis[u] = cnt;
    for ( auto v : Edge[u] ) if ( v != fa ) { dis[v] = dis[u] + 1; anc[v][0] = u; DFS1(v, u); } 
}

inline void DFS2(int u, int fa)
{
    vis[u] = cnt;
    for ( auto v : Edge[u] ) if ( v != fa ) 
    {
        DFS2(v, u); f1[u] += f1[v]; f2[u] += f2[v];
    }
    if ( f1[u] && f2[u] && Map2[u][fa] == 1 ) { puts("No"); exit(0); }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int i = 18; i >= 0; -- i ) if ( dis[anc[x][i]] >= dis[y] ) x = anc[x][i];
    if ( x == y ) return x; 
    for ( int i = 18; i >= 0; -- i ) if ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; }
    return anc[x][0];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, m) 
    { 
        int u, v; scanf("%d%d", &u, &v); 
        if ( !Map1[u][v] ) { add(u, v); add(v, u); }
        ++ Map1[u][v]; ++ Map1[v][u];
    } 
    m = 0; REP(i, 1, n) if ( !dfn[i] ) DFS(i, 0);
    REP(u, 1, n) for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( p[u] == p[v] ) continue ;
        Edge[p[u]].push_back(p[v]); 
        Map2[p[u]][p[v]] += Map1[u][v];
    }
    cnt = 0; REP(i, 1, m) if ( !vis[i] ) { ++ cnt; dis[i] = 1; DFS1(i, 0); }
    REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, q) 
    {
        int u, v; scanf("%d%d", &u, &v); u = p[u]; v = p[v];
        if ( vis[u] != vis[v] ) { puts("No"); return 0; } 
        int t = LCA(u, v); ++ f1[u]; -- f1[t]; -- f2[t]; ++ f2[v];
    }
    mem(vis); REP(i, 1, m) if ( !vis[i] ) DFS2(i, 0);
    puts("Yes");
    return 0;
}
