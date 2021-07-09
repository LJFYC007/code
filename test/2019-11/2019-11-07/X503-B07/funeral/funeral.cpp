/***************************************************************
	File name: funeral.cpp
	Author: ljfcnyali
	Create time: 2019年11月07日 星期四 10时37分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define DEBUG fprintf ( stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__ )
typedef long long LL;

const int maxn = 200010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e;
int id[maxn], p[maxn], cnt, T;

namespace Segment_Tree
{
#define lson root << 1
#define rson root << 1 | 1
    struct node { int sum[3], len, col_son, col_lazy, t_self, t_son; } Tree[maxn << 2];

    inline void Build(int root, int l, int r)
    {
        Tree[root].sum[0] = Tree[root].len = r - l + 1;
        Tree[root].col_lazy = Tree[root].col_son = -1;
        if ( l == r ) return ;
        int Mid = l + r >> 1;
        Build(lson, l, Mid); Build(rson, Mid + 1, r);
    }

    inline void PushTag(int root, int col, int val) { REP(i, 0, 2) Tree[root].sum[i] = 0; Tree[root].sum[col] = val; }

    inline void PushDown(int root)
    {
        if ( Tree[root].col_lazy == -1 ) return ;
        PushTag(lson, Tree[root].col_lazy, Tree[lson].len); Tree[lson].t_self = Tree[root].t_self;
        PushTag(rson, Tree[root].col_lazy, Tree[rson].len); Tree[rson].t_self = Tree[root].t_self;
        Tree[lson].col_lazy = Tree[rson].col_lazy = Tree[root].col_lazy;
        Tree[root].col_lazy = -1;
    }

    inline void PushUp(int root) { REP(i, 0, 2) Tree[root].sum[i] = Tree[lson].sum[i] + Tree[rson].sum[i]; }

    inline void Modify(int root, int l, int r, int L, int R, int col1, int col2)
    {
        if ( L > R ) return ;
        if ( L <= l && r <= R ) 
        {
            if ( col1 != -1 ) { Tree[root].col_lazy = col1; Tree[root].t_self = T; PushTag(root, col1, Tree[root].len); }
            if ( col2 != -1 ) { Tree[root].col_son = col2; Tree[root].t_son = T; }
            return ;
        }
        PushDown(root);
        int Mid = l + r >> 1;
        if ( L <= Mid ) Modify(lson, l, Mid, L, R, col1, col2);
        if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, col1, col2);
        PushUp(root);
    }

    inline int Query(int root, int l, int r, int L, int R, int col)
    {
        if ( L <= l && r <= R ) return Tree[root].sum[col];
        PushDown(root);
        int Mid = l + r >> 1, ret = 0;
        if ( L <= Mid ) ret += Query(lson, l, Mid, L, R, col);
        if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R, col);
        return ret;
    }

    inline void Query3(int root, int l, int r, int pos, int &col, int &t, int opt)
    {
        if ( l == r ) 
        { 
            if ( opt == 0 ) { REP(i, 0, 2) if ( Tree[root].sum[i] ) col = i; t = Tree[root].t_self; }
            else { col = Tree[root].col_son; t = Tree[root].t_son; }
            return ;
        }
        PushDown(root);
        if ( Tree[root].col_son != -1 ) 
        {
            int x = Tree[root].col_son;
            if ( Tree[root].t_son > Tree[lson].t_son ) { Tree[lson].t_son = Tree[root].t_son; Tree[lson].col_son = Tree[root].col_son; }
            if ( Tree[root].t_son > Tree[rson].t_son ) { Tree[rson].t_son = Tree[root].t_son; Tree[rson].col_son = Tree[root].col_son; }
            Tree[root].col_son = -1;
        }
        int Mid = l + r >> 1;
        if ( pos <= Mid ) Query3(lson, l, Mid, pos, col, t, opt);
        else Query3(rson, Mid + 1, r, pos, col, t, opt);
    }

    inline void print(int root, int l, int r)
    {
        printf("%d %d %d\n", root, l, r);
        printf("Color : "); REP(i, 0, 2) printf("%d ", Tree[root].sum[i]); puts("");
        printf("Lazys : "); printf("%d %d; %d %d\n", Tree[root].col_lazy, Tree[root].t_self, Tree[root].col_son, Tree[root].t_son);
        if ( l == r ) return ;
        int Mid = l + r >> 1;
        print(lson, l, Mid); print(rson, Mid + 1, r);
    }
}

using namespace Segment_Tree;

namespace TreeSection
{
    int size[maxn], top[maxn], son[maxn], dis[maxn], anc[maxn][20];

    inline void DFS1(int u, int fa)
    {
        size[u] = 1; int Max = 0;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            dis[v] = dis[u] + 1; anc[v][0] = u;
            DFS1(v, u);
            size[u] += size[v];
            if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
        }
    }

    inline void DFS2(int u, int t)
    {
        id[u] = ++ cnt; p[cnt] = u; top[u] = t;
        if ( son[u] ) DFS2(son[u], t);
        for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != anc[u][0] && To[i] != son[u] ) DFS2(To[i], To[i]);
    }

    inline int Query1(int x, int y, int col)
    {
        int ret = 0;
        while ( top[x] != top[y] ) 
        {
            if ( dis[top[x]] < dis[top[y]] ) swap(x, y);
            ret += Query(1, 1, n, id[top[x]] + 1, id[x], col);
            int col1, col2, t1, t2;
            Query3(1, 1, n, id[top[x]], col1, t1, 0);
            Query3(1, 1, n, id[anc[top[x]][0]], col2, t2, 1);
            if ( col1 == -1 ) t1 = -1;
            if ( col2 == -1 ) t2 = -1;
            if ( t1 >= t2 ) ret += col1 == col; else ret += col2 == col;
            // printf("%d %d %d %d %d\n", x, col1, t1, col2, t2);
            x = anc[top[x]][0];
        }
        if ( dis[x] > dis[y] ) swap(x, y);
        // printf("%d %d %d\n", x, y, ret);
        ret += Query(1, 1, n, id[x] + 1, id[y], col);
        return ret;
    }

    inline void Modify1(int x, int y, int col1, int col2)
    {
        if ( son[x] ) Modify(1, 1, n, id[son[x]], id[son[x]], col2, -1);
        if ( son[y] ) Modify(1, 1, n, id[son[y]], id[son[y]], col2, -1);
        ++ T;
        while ( top[x] != top[y] )
        {
            if ( dis[top[x]] < dis[top[y]] ) swap(x, y);
            Modify(1, 1, n, id[top[x]], id[x], col1, col2);
            x = anc[top[x]][0];
            if ( son[x] ) Modify(1, 1, n, id[son[x]], id[son[x]], col2, -1);
        }
        if ( dis[x] > dis[y] ) swap(x, y);
        Modify(1, 1, n, id[x] + 1, id[y], col1, col2);
        Modify(1, 1, n, id[x], id[x], col2, col2);
        // REP(i, 1, n) printf("%d ", id[i]); puts("");
        // if ( col1 == 0 ) print(1, 1, n);
    }
    
    inline void Modify2(int rt, int x, int col)
    {
        int u = rt;
        for ( int j = 18; j >= 0; -- j ) if ( dis[anc[u][j]] > dis[x] ) u = anc[u][j];
        if ( u == x ) Modify(1, 1, n, 1, n, col, -1);
        else if ( anc[u][0] != x ) Modify(1, 1, n, id[x] + 1, id[x] + size[x] - 1, col, -1);
        else
        {
            Modify(1, 1, n, 1, id[u] - 1, col, -1);
            Modify(1, 1, n, id[u] + size[u], n, col, -1);
        }
    }
}

using namespace TreeSection;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

int main()
{
    freopen("funeral.in", "r", stdin);
    freopen("funeral.out", "w", stdout);
    scanf("%d", &n);    
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS1(1, 0); DFS2(1, 1); Build(1, 1, n);
    REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    scanf("%d", &m);
    while ( m -- ) 
    {
        int opt; scanf("%d", &opt); ++ T;
        if ( opt == 1 ) 
        {
            int x, y, col; scanf("%d%d%d", &x, &y, &col);
            printf("%d\n", Query1(x, y, col));
        }
        if ( opt == 2 ) 
        {
            int x, y, col1, col2; scanf("%d%d%d%d", &x, &y, &col1, &col2);
            Modify1(x, y, col1, col2);
        }
        if ( opt == 3 ) 
        {
            int rt, x, col; scanf("%d%d%d", &rt, &x, &col);
            Modify2(rt, x, col);
        }
    }
    return 0;
}
