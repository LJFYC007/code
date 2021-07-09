/***************************************************************
	File name: P3258.cpp
	Author: ljfcnyali
	Create time: 2019年06月07日 星期五 08时52分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 3000010;

int anc[maxn][20], fa[maxn], f[maxn], n, a[maxn], sum[maxn], dis[maxn];
int Begin[maxn], Next[maxn], To[maxn], e;

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS(int u, int x)
{
    dis[u] = ++ x;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( dis[v] ) continue ;
        anc[v][0] = u; fa[v] = u; DFS(v, x);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 19; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 19; j >= 0; -- j )
        if ( anc[x][j] != anc[y][j] ) 
        {
            x = anc[x][j]; y = anc[y][j];
        }
    return anc[x][0];
}

inline void DFS2(int u)
{
    sum[u] = f[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa[u] ) continue ;
        DFS2(v);
        sum[u] += sum[v];
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    DFS(1, 0);
    REP(j, 1, 19) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, n - 1)
    {
        int v = LCA(a[i], a[i + 1]);
        ++ f[a[i]]; ++ f[a[i + 1]]; -- f[v]; -- f[fa[v]];
    }
//    ++ f[a[n]];
//    REP(i, 1, n) printf("%d ", f[i]); puts("");
    DFS2(1);
    REP(i, 2, n) -- sum[a[i]];
    REP(i, 1, n) printf("%d\n", sum[i]);
    return 0;
}
