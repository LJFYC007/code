/***************************************************************
	File name: nichijou.cpp
	Author: ljfcnyali
	Create time: 2019年08月04日 星期日 09时00分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 4000010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e;
int anc[maxn][30], p[30], Max, k, dis[maxn];

struct node
{
    int a, b, d, lca, w;
} a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1;
        anc[v][0] = u;
        DFS(v, u);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 21; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 21; j >= 0; -- j )  if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

namespace Subtask
{
    int top[maxn], son[maxn], f[maxn], size[maxn];

    inline void DFS1(int u)
    {
        size[u] = 1; int Max = 0;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == f[u] ) continue ;
            f[v] = u; DFS1(v);
            if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
            size[u] += size[v];
        }
    }

    inline void DFS2(int u, int t)
    {
        top[u] = t;
        if ( !son[u] ) return ;
        DFS2(son[u], t);
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
            DFS2(v, v);
        }
    }

    inline int LCA(int x, int y)
    {
        while ( top[x] != top[y] ) 
        {
            if ( dis[top[x]] < dis[top[y]] ) swap(x, y);
            x = f[top[x]];
        }
        return dis[x] < dis[y] ? x : y;
    }

    inline int Dis(int x, int y)
    {
        return dis[x] + dis[y] - 2 * dis[LCA(x, y)];
    }

    inline bool Check(int x)
    {
        DFS1(1); DFS2(1, 1);
        REP(i, 1, m) if ( Dis(x, a[i].a) + Dis(x, a[i].b) > a[i].w ) return false;
        return true;
    }
}

int main()
{
    freopen("nichijou.in", "r", stdin);
    freopen("nichijou.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS(1, 0);
    REP(j, 1, 21) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    p[0] = 1; REP(i, 1, 21) p[i] = p[i - 1] * 2;
    REP(i, 1, m) 
    { 
        scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].d); 
        a[i].lca = LCA(a[i].a, a[i].b); a[i].w = a[i].lca;
        int x = a[i].d;
        a[i].d = a[i].d - dis[a[i].a] - dis[a[i].b] + 2 * dis[a[i].lca];
        a[i].d /= 2;
        for ( int j = 21; j >= 0; -- j ) if ( p[j] <= a[i].d ) { a[i].d -= p[j]; a[i].w = anc[a[i].w][j]; }
        if ( !a[i].w ) a[i].w = 1;
        if ( dis[a[i].w] > Max ) { Max = dis[a[i].w]; k = a[i].w; }
        a[i].d = x;
    } 
    if ( Subtask :: Check(k) ) printf("%d\n", k); else puts("NO\n");
    return 0;
}
