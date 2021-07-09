/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年07月23日 星期四 09时44分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

int n, m, q, N, Begin[maxn], Next[maxn], To[maxn], e, id[260][260][2];
int dfn[maxn], low[maxn], tot, cnt, p[maxn], Stack[maxn], top, f[maxn];
bool ans[260][260];
vector<int> Edge[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void Add(int u, int v) { Edge[u].push_back(v); }

inline void DFS1(int u, int fa)
{
    vector<int> p; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        REP(j, 1, m) { Add(id[j][u][0], id[j][v][0]); Add(id[j][v][1], id[j][u][1]); }
        p.push_back(v);
        f[v] = u; DFS1(v, u);
    }
    REP(j, 1, m) for ( int x = 1; x < p.size(); ++ x ) REP(y, 0, x - 1)
    {
        Add(id[j][p[x]][1], id[j][p[y]][0]);
        Add(id[j][p[y]][1], id[j][p[x]][0]);
    }
}

inline void Tarjan(int u)
{
    low[u] = dfn[u] = ++ tot; Stack[++ top] = u;
    for ( auto v : Edge[u] ) 
        if ( !dfn[v] ) { Tarjan(v); low[u] = min(low[u], low[v]); }
        else if ( !p[v] ) low[u] = min(low[u], dfn[v]); 
    if ( low[u] == dfn[u] ) 
    {
        p[u] = ++ cnt;
        while ( Stack[top] != u ) { p[Stack[top]] = cnt; -- top; }
        -- top;
    }
}

inline void DFS(int x, int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( ans[x][v] ) { DFS(x, v, u); return ; }
    }
    printf("%d ", u);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, m) REP(j, 1, n) REP(o, 0, 1) id[i][j][o] = ++ N;
    id[0][1][0] = ++ N; id[0][1][1] = ++ N;
    id[0][2][0] = ++ N; id[0][2][1] = ++ N;
    Add(id[0][1][0], id[0][2][1]);
    Add(id[0][2][1], id[0][1][1]);
    REP(i, 1, m) { Add(id[0][1][1], id[i][1][1]); Add(id[i][1][0], id[0][1][0]); }
    DFS1(1, 0);
    REP(i, 1, q) 
    {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        if ( a == b ) 
        { 
            Add(id[0][1][1], id[a][c][1]); 
            for ( int j = Begin[c]; j; j = Next[j] ) 
            {
                int v = To[j]; 
                if ( v != f[c] ) Add(id[0][1][1], id[a][v][0]);
            }
            continue ; 
        }
        for ( int j = Begin[c]; j; j = Next[j] ) 
        {
            int v = To[j]; if ( v == f[c] ) continue ;
            Add(id[a][v][1], id[b][v][0]); Add(id[b][v][1], id[a][v][0]);
        }
        Add(id[a][c][0], id[b][c][1]); Add(id[b][c][0], id[a][c][1]);
    }
    REP(i, 1, N) if ( !dfn[i] ) Tarjan(i);
    REP(i, 1, m) REP(j, 1, n) if ( p[id[i][j][1]] < p[id[i][j][0]] ) ans[i][j] = true;
    REP(i, 1, m) DFS(i, 1, 0);
    puts("");
    return 0;
}
