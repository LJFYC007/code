/***************************************************************
	File name: oitree.cpp
	Author: ljfcnyali
	Create time: 2019年08月11日 星期日 10时41分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1010;
const int maxm = 100010;
const int INF = 0x3f3f3f3f;	

int n, m, f[maxn][maxn], d[maxn];
bool flag1 = true, flag2 = true;

struct node
{
    int u, v, w;
} a[maxm];

namespace Subtask1
{
    int dis[maxm]; 

    inline void Solve()
    {
        REP(i, 2, n) dis[i] = dis[i - 1] + a[i - 1].w;
        int x; scanf("%d", &x); dis[n + 1] = dis[n] + x;
        REP(i, 1, m)
        {
            int u, v; scanf("%d%d", &u, &v);
            if ( u > v ) swap(u, v);
            int ans = dis[v] - dis[u];
            ans = min(ans, dis[n + 1] - dis[v] + dis[u]);
            printf("%d\n", ans);
        }
    }
}

namespace Subtask2
{
    int dis[maxn];

    inline void Solve()
    {
        REP(i, 1, n - 1) dis[a[i].v] = a[i].w;
        REP(i, 2, n) { int x; scanf("%d", &x); dis[i] = min(dis[i], x); }
        REP(i, 1, m)
        {
            int u, v; scanf("%d%d", &u, &v);
            if ( u > v ) swap(u, v);
            if ( u == 1 ) printf("%d\n", dis[v]);
            else printf("%d\n", dis[u] + dis[v]);
        }
    }
}

int main()
{
    freopen("oitree.in", "r", stdin);
    freopen("oitree.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) 
    { 
        int fa, w; scanf("%d%d", &fa, &w); 
        a[i].u = fa; a[i].v = i + 1; a[i].w = w; 
        if ( a[i].u + 1 != a[i].v ) flag1 = false;
        if ( a[i].u != 1 ) flag2 = false;
    }
    if ( flag1 == true ) { Subtask1 :: Solve(); return 0; }
    if ( flag2 == true ) { Subtask2 :: Solve(); return 0; }
    REP(i, 1, n) REP(j, 1, n) f[i][j] = INF;
    REP(i, 1, n) f[i][i] = 0;
    REP(i, 1, n - 1) { ++ d[a[i].u]; ++ d[a[i].v]; f[a[i].u][a[i].v] = f[a[i].v][a[i].u] = min(f[a[i].u][a[i].v], a[i].w); }
    REP(i, 2, n) if ( d[i] == 1 ) { int w; scanf("%d", &w); f[i][1] = f[1][i] = min(f[1][i], w); }
    REP(k, 1, n)
        REP(i, 1, n)
        {
            if ( k == i ) continue ;
            int t = (k < i) ? f[i][k] : f[k][i];
            if ( t == INF ) continue ;
            REP(j, 1, min(k, i)) f[i][j] = min(f[i][j], t + f[k][j]);
            REP(j, k + 1, i) f[i][j] = min(f[i][j], t + f[j][k]);
        }
    REP(i, 1, m)
    {
        int u, v; scanf("%d%d", &u, &v);
        if ( u < v ) swap(u, v);
        printf("%d\n", f[u][v]);
    }
    return 0;
}
