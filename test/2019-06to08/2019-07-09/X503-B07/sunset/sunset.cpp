/***************************************************************
	File name: sunset.cpp
	Author: ljfcnyali
	Create time: 2019年07月09日 星期二 10时08分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 500010;

int Begin[maxn][2], Next[maxn][2], To[maxn][2], e[2], W[maxn];
int n, m, q, anc[maxn][20], val[maxn], dfn[maxn], low[maxn];
int cnt, dis[maxn], a[maxn], tot, f[maxn];
bool vis[maxn];
stack<int> Stack;

inline int cha(int x) { return x == f[x] ? x : f[x] = cha(f[x]); }

inline void add(int u, int v, int opt) 
{ 
    To[++ e[opt]][opt] = v; 
    Next[e[opt]][opt] = Begin[u][opt]; 
    Begin[u][opt] = e[opt]; 
}

inline void Solve(int x)
{
    bool flag = false;
    REP(j, 1, tot)
    {
        int u = To[a[j]][0];
        for ( int i = Begin[u][1]; ~i; i = Next[i][1] ) 
            if ( u != x && dis[u] == dis[To[i][1]] ) flag = true;
        u = To[a[j] ^ 1][0];
        for ( int i = Begin[u][1]; ~i; i = Next[i][1] ) 
            if ( u != x && dis[u] == dis[To[i][1]] ) flag = true;
    }
    if ( flag == true ) REP(i, 1, tot) W[a[i]] = W[a[i] ^ 1] = 1;
}

inline void Tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ cnt; 
    dis[u] = dis[fa] ^ 1;
    for ( int i = Begin[u][0]; ~i; i = Next[i][0] ) 
    {
        int v = To[i][0]; if ( v == fa ) continue ;
        if ( !dfn[v] ) 
        {
            Stack.push(i); Tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if ( low[v] >= dfn[u] ) 
            {
                int y = 0; tot = 0;
                while ( y != i ) { y = Stack.top(); Stack.pop(); a[++ tot] = y; }
                Solve(u);
            }
        }
        else 
        {
            low[u] = min(low[u], dfn[v]); 
            if ( dfn[v] < dfn[u] ) add(u, v, 1);
        }
    }
}

inline void DFS(int u)
{
    vis[u] = true;
    for ( int i = Begin[u][0]; ~i; i = Next[i][0] ) 
    {
        int v = To[i][0]; if ( vis[v] ) continue ;
        anc[v][0] = u; dis[v] = dis[u] + 1;
        val[v] = val[u] + W[i];
        DFS(v);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 18; j >= 0; -- j ) 
        if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 18; j >= 0; -- j )
        if ( anc[x][j] != anc[y][j] ) 
        {
            x = anc[x][j];
            y = anc[y][j];
        }
    return anc[x][0];
}

int main()
{
    freopen("sunset.in", "r", stdin);
    freopen("sunset.out", "w", stdout);
    memset(Begin, -1, sizeof(Begin)); e[0] = e[1] = -1;
    scanf("%d%d", &n, &m);
    REP(i, 1, n) f[i] = i;
    REP(i, 1, m) 
    {
        int u, v; scanf("%d%d", &u, &v); 
        add(u, v, 0); add(v, u, 0); 
        int fx = cha(u), fy = cha(v);
        if ( fx != fy ) f[fx] = fy;
    }
    REP(i, 1, n) if ( !dfn[i] ) Tarjan(i, 0);
    REP(i, 1, n) if ( !vis[i] ) { dis[i] = 1; DFS(i); }
    REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    scanf("%d", &q);
    while ( q -- ) 
    {
        int u, v; scanf("%d%d", &u, &v);
        int fx = cha(u), fy = cha(v);
        if ( fx != fy ) puts("No");
        else if ( (dis[u] & 1) != (dis[v] & 1) ) puts("Yes");
        else if ( val[u] + val[v] - 2 * val[LCA(u, v)] > 0 ) puts("Yes");
        else puts("No");
    }
    return 0;
}
