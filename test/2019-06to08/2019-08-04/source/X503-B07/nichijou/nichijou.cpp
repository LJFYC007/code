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
int top[maxn], son[maxn], dis[maxn], f[maxn], size[maxn];
clock_t t1;

struct node
{
    int a, b, d;
} a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u)
{
    size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == f[u] ) continue ;
        f[v] = u; dis[v] = dis[u] + 1; DFS1(v);
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

namespace Subtask1
{
    inline void Solve()
    {
        DFS2(1, 1);
        REP(i, 1, n) 
        {
            bool flag = true;
            REP(j, 1, m)
                if ( Dis(i, a[j].a) + Dis(i, a[j].b) > a[j].d ) { flag = false; break ; }
            if ( flag == true ) { printf("%d\n", i); return ; }
            // if ( i % 100 == 0 && (double)clock() - t1 / CLOCKS_PER_SEC > 3 ) break ;
        }
        puts("NO\n");
    }
}

namespace Subtask2
{
    int root = 1, Min = 100000000;

    inline void DFS(int u)
    {
        int Max = 0;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == f[u] ) continue ;
            DFS(v);
            Max = max(Max, size[v]);
        }
        Max = max(Max, n - size[u]);
        if ( Max < Min ) { Min = Max; root = u; }
    }
    
    inline void Solve()
    {
        DFS(1);
        printf("%d\n", root);
        exit(0);
    }
}

namespace Subtask3
{
    int p[maxn];
    inline void Solve()
    {
        REP(i, 1, m) scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].d);
        REP(i, 1, m) if ( a[i].b - a[i].a > a[i].d ) { puts("NO\n"); return ; }
        REP(i, 1, m) ++ p[max(0, a[i].b - a[i].d)], -- p[min(n, a[i].a + a[i].d + 1)];
        REP(i, 1, n) { p[i] += p[i - 1]; if ( p[i] == n ) { printf("%d\n", i); exit(0) ; } }
        puts("NO\n");
        exit(0);
    }
}

int main()
{
    freopen("nichijou.in", "r", stdin);
    freopen("nichijou.out", "w", stdout);
    t1 = clock();
    scanf("%d%d", &n, &m);
    bool flag = true, flag2 = true;;
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); if ( u + 1 != v ) flag2 = false; add(u, v); add(v, u); }
    if ( flag2 == true ) Subtask3 :: Solve();
    dis[1] = 1; DFS1(1);
    REP(i, 1, m) { scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].d); if ( a[i].d != 2000000 ) flag = false; } 
    if ( flag == true ) Subtask2 :: Solve();
    Subtask1 :: Solve();
    return 0;
}
