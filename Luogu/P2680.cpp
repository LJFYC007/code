/***************************************************************
	File name: P2680.cpp
	Author: ljfcnyali
	Create time: 2019年07月05日 星期五 10时14分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

struct node
{
    int u, v, w, lca;
} a[maxn];

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, sum[maxn], anc[maxn][20], dis[maxn], ans, Max, k;
int cnt[maxn], tot;

inline int cmp(node a, node b)
{
    return a.w > b.w;
}

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        sum[v] = sum[u] + W[i];
        anc[v][0] = u;
        dis[v] = dis[u] + 1;
        DFS1(v, u);
    }
}

inline void DFS2(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS2(v, u);
        cnt[u] += cnt[v];
    }
    if ( cnt[u] > Max ) 
    {
        Max = cnt[u]; k = sum[u] - sum[anc[u][0]];; 
    }
    else if ( cnt[u] == Max ) k = max(k, sum[u] - sum[anc[u][0]]);
}

inline int LCA(int u, int v)
{
    if ( dis[u] < dis[v] ) swap(u, v);
    for ( int j = 19; j >= 0; -- j )
        if ( dis[anc[u][j]] >= dis[v] ) u = anc[u][j];
    if ( u == v ) return u;
    for ( int j = 19; j >= 0; -- j )
        if ( anc[u][j] != anc[v][j] ) 
        {
            u = anc[u][j];
            v = anc[v][j];
        }
    return anc[u][0];
}

inline bool check(int x)
{
    mem(cnt);
    tot = Max = k = 0;
    REP(i, 1, m)
    {
        if ( a[i].w <= x ) break ;
        ++ tot;
        ++ cnt[a[i].u]; ++ cnt[a[i].v];
        cnt[a[i].lca] -= 2;
    }
    DFS2(1, 0);
/*    if ( x == 11 ) 
    {
        REP(i, 1, n) printf("%d ", cnt[i]);
        puts("");
        printf("%d %d %d\n", tot, Max, k);
    }*/
    if ( Max < tot ) return false; 
    if ( a[1].w - k > x ) return false;
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
    DFS1(1, 0);
    REP(j, 1, 19)
        REP(i, 1, n)
            anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, m)
    {
        scanf("%d%d", &a[i].u, &a[i].v);
        a[i].lca = LCA(a[i].u, a[i].v);
        a[i].w = sum[a[i].u] + sum[a[i].v] - 2 * sum[a[i].lca];
    }
    sort(a + 1, a + m + 1, cmp);
//    REP(i, 1, m)
//        printf("%d %d %d\n", a[i].u, a[i].v, a[i].w);
    int L = 0, R = a[1].w;
    while ( L <= R ) 
    {
        int Mid = L + R >> 1;
        if ( check(Mid) ) { ans = Mid; R = Mid - 1; } 
        else L = Mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}
