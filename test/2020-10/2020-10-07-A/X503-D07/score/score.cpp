/***************************************************************
	File name: score.cpp
	Author: ljfcnyali
	Create time: 2020年10月07日 星期三 15时56分03秒
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

const int maxn = 2e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, dfn[maxn], tot, size[maxn];
int cnt, ans, anc[maxn][20], dis[maxn], ctrcsqb, sum[maxn];
struct node { int l, r, val; node(int a = 0, int b = 0, int c = 0) { l = a; r = b; val = c; }; } ;
vector<node> a[maxn];
struct Node { int lazy, Max; } Tree[maxn << 2];

inline void PushTag(int root, int val) { Tree[root].lazy += val; Tree[root].Max += val; }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Modify1(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, val); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify1(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify1(rson, Mid + 1, r, L, R, val);
    Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
}

inline void Modify(int l1, int r1, int l2, int r2, int w)
{
    if ( l2 > r2 || l1 > r1 ) return ;
    a[l2].push_back(node(l1, r1, w));
    a[r2 + 1].push_back(node(l1, r1, -w));
    // cout << l1 << " " << r1 << " " << l2 << " " << r2 << " " << w << endl;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    size[u] = 1; dfn[u] = ++ tot; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1;
        DFS(v, u); size[u] += size[v]; anc[v][0] = u;
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int i = 18; i >= 0; -- i ) if ( dis[anc[x][i]] >= dis[y] ) x = anc[x][i];
    if ( x == y ) return x;
    for ( int i = 18; i >= 0; -- i ) if ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; }
    return anc[x][0];
}

int main()
{
    freopen("score.in", "r", stdin);
    freopen("score.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS(1, 0); REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, m)
    {
        int x, y, w; scanf("%d%d%d", &x, &y, &w);
        int t = LCA(x, y);
        if ( t == x && t == y ) 
        {
            Modify(dfn[x], dfn[x], dfn[y], dfn[y], -w);
            Modify(dfn[x], dfn[x] + size[x] - 1, 1, dfn[y], w);
            Modify(dfn[x], dfn[x] + size[x] - 1, dfn[y] + size[y], n, w);
            Modify(1, dfn[x], dfn[y], dfn[y] + size[y] - 1, w);
            Modify(dfn[x] + size[x], n, dfn[y], dfn[y] + size[y] - 1, w);
            sum[x] += w;
        }
        else if ( t == x ) 
        {
            ctrcsqb = y;
            for ( int j = 18; j >= 0; -- j ) if ( dis[anc[ctrcsqb][j]] > dis[x] ) ctrcsqb = anc[ctrcsqb][j];
            Modify(1, dfn[ctrcsqb] - 1, dfn[y], dfn[y] + size[y] - 1, w);
            Modify(dfn[ctrcsqb] + size[ctrcsqb], n, dfn[y], dfn[y] + size[y] - 1, w);
        }
        else if ( t == y ) 
        {
            ctrcsqb = x;
            for ( int j = 18; j >= 0; -- j ) if ( dis[anc[ctrcsqb][j]] > dis[y] ) ctrcsqb = anc[ctrcsqb][j];
            Modify(dfn[x], dfn[x] + size[x] - 1, 1, dfn[ctrcsqb] - 1, w);
            Modify(dfn[x], dfn[x] + size[x] - 1, dfn[ctrcsqb] + size[ctrcsqb], n, w);
        }
        else Modify(dfn[x], dfn[x] + size[x] - 1, dfn[y], dfn[y] + size[y] - 1, w);
    }
    REP(x, 1, n)
    {
        if ( !sum[x] ) continue ;
        for ( int j = Begin[x]; j; j = Next[j] ) 
        {
            int v = To[j]; if ( v == anc[x][0] ) continue ;
            Modify(dfn[v], dfn[v] + size[v] - 1, dfn[x] + 1, dfn[v] - 1, sum[x]);
            Modify(dfn[v], dfn[v] + size[v] - 1, dfn[v] + size[v], dfn[x] + size[x] - 1, sum[x]);
        }
    }
    REP(i, 1, n)
    {
        for ( int j = 0; j < a[i].size(); ++ j ) 
            Modify1(1, 1, n, a[i][j].l, a[i][j].r, a[i][j].val);
        ans = max(ans, Tree[1].Max);
    }
    printf("%d\n", ans);
    return 0;
}
