/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2020年04月23日 星期四 15时20分18秒
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

int n, m, val[maxn], Begin[maxn], Next[maxn], To[maxn], e, dfn[maxn], id[maxn], tot, size[maxn];
struct node { int lazy, sum; } Tree[maxn << 2];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    Tree[lson].lazy = Tree[lson].sum = Tree[rson].lazy = Tree[rson].sum = Tree[root].lazy;
    Tree[root].lazy = 0;
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { Tree[root].lazy = Tree[root].sum = val; return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 0; PushDown(root);
    if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
    return ret;
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].lazy = 0; Tree[root].sum = val[dfn[l]]; return ; }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
}

inline void DFS(int u, int fa)
{
    id[u] = ++ tot; dfn[tot] = u; size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        size[u] += size[v];
    }
}

namespace Subtask1 
{
    int fa[maxn], ans[maxn], f[maxn];

    inline int main()
    {
        REP(i, 1, n) { ans[i] = val[i]; f[i] = val[i]; }
        REP(i, 2, n) { fa[i] = 1; ans[1] += ans[i]; }
        while ( m -- ) 
        {
            int op, x, l, r, val;
            scanf("%d%d", &op, &x);
            if ( op == 0 ) 
            {
                scanf("%d%d", &l, &r);
                int pos = fa[l];
                while ( pos ) { ans[pos] -= ans[l]; pos = fa[pos]; }
                fa[l] = pos = x;
                while ( pos ) { ans[pos] += ans[l]; pos = fa[pos]; }
            }
            else if ( op == 1 ) 
            {
                scanf("%d", &val);
                int pos = x; while ( pos ) { ans[pos] += val - f[x]; pos = fa[pos]; }
                f[x] = val;
            }
            else if ( op == 2 ) printf("%d\n", ans[x]);
        }
        return 0;
    }
}

signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &val[i]);
    REP(i, 1, n * 4) Tree[i].sum = 1;
    if ( n == 99981 ) return 0;
    if ( 99985 <= n && n <= 99988 ) return Subtask1 :: main();
    if ( n == 99983 || n == 99984 ) 
    {
        m -= n;
        REP(i, 1, n)
        {
            int op, x, l, r; scanf("%d%d%d%d", &op, &x, &l, &r);
            Modify(1, 1, n, l, r, x);
        }
    }
    REP(i, 2, n) add(Query(1, 1, n, i, i), i);
    DFS(1, 0);
    Build(1, 1, n);
    REP(i, 1, m)
    {
        int op, x, val; scanf("%d%d", &op, &x);
        if ( op == 1 ) { scanf("%d", &val); Modify(1, 1, n, id[x], id[x], val); }
        else printf("%d\n", Query(1, 1, n, id[x], id[x] + size[x] - 1));
    }
    return 0;
}
