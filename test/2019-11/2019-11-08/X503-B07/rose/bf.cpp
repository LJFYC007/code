/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年11月08日 星期五 14时23分31秒
***************************************************************/
#include<cstdio>
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], fa[maxn], ans;
struct node { int x, y, t; } a[maxn];
vector<int> h[maxn];
bool use[maxn], col[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u) 
{ 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa[u] ) continue ;
        fa[v] = u; dis[v] = dis[u] + 1; DFS1(v);
    }
}

inline int LCA(int x, int y)
{
    while ( x != y ) { if ( dis[x] < dis[y] ) swap(x, y); x = fa[x]; }
    return x;
}

inline void Col(int u, int fa)
{
    col[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || col[v] ) continue ;
        Col(v, u); 
    }
}

inline void DFS2(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS2(v, u);
    }
    for ( auto i : h[u] ) 
    {
        if ( col[a[i].x] || col[a[i].y] ) continue ;
        Col(u, fa); break ; 
    }
}

int main()
{
    freopen("rose.in", "r", stdin);
    freopen("rose.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS1(1);
    REP(i, 1, m) scanf("%d%d", &a[i].x, &a[i].y); 
    REP(i, 1, n)
    {
        if ( use[i] ) continue ;
        mem(col); mem(fa); dis[i] = 1; DFS1(i);
        REP(j, 1, n) h[j].clear();
        REP(j, 1, m) { a[j].t = LCA(a[j].x, a[j].y); h[a[j].t].push_back(j); }
        DFS2(i, 0);
        int ret = 0;
        REP(j, 1, n) if ( !col[j] ) { use[j] = true; ++ ret; }
        ans += ret * ret;
    }
    printf("%d\n", ans);
    return 0;
}
