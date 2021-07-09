/***************************************************************
	File name: b.cpp
	Author: ljfcnyali
	Create time: 2019年12月17日 星期二 21时27分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, size[maxn], dis[maxn], f[maxn];
int id[maxn], p[maxn], son[maxn], head[maxn], cnt, a[maxn], anc[maxn][20];
struct node { int lazy, sum, len; } Tree[maxn << 4];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; f[v] = u; anc[v][0] = u;
        DFS1(v, u);
        size[u] += size[v];
        if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
    }
}

inline void DFS2(int u, int t)
{
    p[u] = ++ cnt; id[cnt] = u; head[u] = t;
    if ( son[u] ) DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == son[u] || v == f[u] ) continue ;
        DFS2(v, v);
    }
}

inline int LCA(int x, int y)
{
    while ( head[x] != head[y] ) { if ( dis[head[x]] < dis[head[y]] ) swap(x, y); x = f[head[x]]; }
    return dis[x] < dis[y] ? x : y;
}

inline void PushUp(int root) { Tree[root].sum = Tree[lson].sum + Tree[rson].sum; }

inline void PushDown(int root)
{
    if ( Tree[root].lazy == -1 ) return ;
    Tree[lson].sum = Tree[root].lazy * Tree[lson].len;
    Tree[rson].sum = Tree[root].lazy * Tree[rson].len;
    Tree[lson].lazy = Tree[rson].lazy = Tree[root].lazy;
    Tree[root].lazy = 0;
}

inline void Build(int root, int l, int r)
{
    Tree[root].lazy = -1; Tree[root].sum = Tree[root].len = r - l + 1;
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
}

inline int GetL(int ret1, int ret2, int x, int y, int fa)
{
    for ( int j = 18; j >= 0; -- j ) 
    {
        int u = anc[y][j];
        if ( dis[u] < dis[fa] ) continue ;
        int sum1 = ret1 + dis[u] - dis[fa];
        int sum2 = ret2 + dis[y] - dis[fa];
        if ( sum1 > sum2 ) { y = u; ret2 = sum2; }
    }
}

inline int Solve(int x, int y)
{
    int fa = LCA(x, y);
    int ret1 = dis[x] - dis[fa], ret2 = dis[y] - dis[fa];
    if ( ret1 < ret2 ) return GetL(ret1, 0, x, y, fa);
    return GetR(0, ret2, x, y, fa);
}

int main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS1(1, 0); DFS2(1, 1); Build(1, 1, n);
    REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    while ( m -- ) 
    {
        int k; scanf("%d", &k); 
        Tree[1].lazy = 1; Tree[1].sum = Tree[1].len;
        REP(i, 1, k) scanf("%d", &a[i]);
        REP(i, 2, k) Solve(a[1], a[i]);
    }
    return 0;
}
