/***************************************************************
	File name: LibreOJ_2206.cpp
	Author: ljfcnyali
	Create time: 2020年06月19日 星期五 14时41分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6e5 + 10;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], pos[maxn], len[maxn];
int p[maxn], tot, dis[maxn], size[maxn], anc[maxn][20], Stack[maxn], top, ans[maxn];
bool vis[maxn];
vector<int> Edge[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Add(int u, int v) { Edge[u].push_back(v); Edge[v].push_back(u); }

inline void DFS(int u, int fa)
{
    size[u] = 1; p[u] = ++ tot;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; DFS(v, u);
        anc[v][0] = u; size[u] += size[v];
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 18; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 18; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

inline void DFS1(int u, int fa)
{
    if ( vis[u] ) { pos[u] = u; len[u] = 0; }
    else len[u] = n + 1;
    for ( auto v : Edge[u] ) 
        if ( abs(dis[v] - dis[u]) < len[u] ) { len[u] = abs(dis[v] - dis[u]); pos[u] = v; }
    ans[pos[u]] += size[u];
    for ( auto v : Edge[u] ) if ( v != fa ) ans[pos[u]] -= size[v];
    for ( auto v : Edge[u] )
    {
        if ( v == fa ) continue ;
        DFS1(v, u);
        int t = v;
        for ( int j = 18; j >= 0; -- j ) 
            if ( len[v] + dis[v] - dis[anc[t][j]] < len[u] + dis[anc[t][j]] - dis[v] 
             || (len[v] + dis[v] - dis[anc[t][j]] == len[u] + dis[anc[t][j]] - dis[v] && pos[v] < pos[u]) )
                t = anc[t][j];
    }
}

inline void Build()
{
    sort(a + 1, a + m + 1, [](int x, int y) { return p[x] < p[y]; });
    top = Stack[1] = 1;
    REP(i, 1, m)
    {
        if ( a[i] == 1 ) continue ;
        int t = LCA(a[i], Stack[top]);
        if ( t != Stack[top] ) 
        {
            while ( p[t] < p[Stack[top - 1]] ) 
            { 
                Add(Stack[top - 1], Stack[top]);
                -- top;
            }
            if ( t == Stack[top - 1] ) { Add(t, Stack[top]); -- top; }
            else { Edge[t].clear(); Add(t, Stack[top]); Stack[top] = t; }
        }
        Edge[a[i]].clear(); Stack[++ top] = a[i];
    }
    while ( top > 1 ) { Add(Stack[top - 1], Stack[top]); -- top; }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS(1, 0);
    REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    scanf("%d", &q);
    while ( q -- ) 
    {
        scanf("%d", &m);
        REP(i, 1, m) { scanf("%d", &a[i]); vis[a[i]] = true; ans[i] = 0; }
        Build(); DFS1(1, 0);
        REP(i, 1, m) { vis[a[i]] = false; printf("%d ", ans[i]); } puts("");
    }
    return 0;
}
