// luogu-judger-enable-o2
/***************************************************************
    File name: A.cpp
    Author: ljfcnyali
    Create time: 2019年06月03日 星期一 14时56分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 200010;

int Begin[maxn], Next[maxn], To[maxn], e;
int dis[maxn], son[maxn], f[maxn], size[maxn], p[maxn], top[maxn];
int n, m, Mod = 2147483647, r, a[maxn], id[maxn], cnt;

struct node
{
    int l, r;
    LL len, val, lazy;
} Tree[maxn * 2];

inline void Push_up(int root)
{
    Tree[root].val = Tree[lson].val + Tree[rson].val;
}

inline void Push_down(int root)
{
    if ( Tree[root].len == 1 ) { Tree[root].lazy = 0; return ; }
    Tree[lson].lazy = (Tree[lson].lazy + Tree[root].lazy);
    Tree[rson].lazy = (Tree[rson].lazy + Tree[root].lazy);
    Tree[lson].val = (Tree[lson].val + Tree[lson].len * Tree[root].lazy);
    Tree[rson].val = (Tree[rson].val + Tree[rson].len * Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Build(int root, int l, int r)
{
    Tree[root].l = l; Tree[root].r = r; Tree[root].len = r - l + 1;
    Tree[root].lazy = 0;
    if ( l == r ) 
    {
        Tree[root].val = a[p[l]];
     //   printf("%d %d %d %d %d\n", root, l, r, Tree[root].val, p[l]);
        return ;
    }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Push_up(root);
 //   printf("%d %d %d %d\n", root, l, r, Tree[root].val);
}

inline void Update(int root, int l, int r, LL val)
{
    if ( l <= Tree[root].l && Tree[root].r <= r ) 
    {
        Tree[root].val = (Tree[root].val + Tree[root].len * val);
        Tree[root].lazy = (Tree[root].lazy + val);
        return ;
    }
    Push_down(root);
    int Mid = Tree[root].l + Tree[root].r >> 1;
    if ( l <= Mid ) Update(lson, l, r, val);
    if ( Mid < r ) Update(rson, l, r, val);
    Push_up(root);
}

inline LL Query(int root, int l, int r)
{
    Push_down(root);
    if ( l <= Tree[root].l && Tree[root].r <= r ) return Tree[root].val;
    int Mid = Tree[root].l + Tree[root].r >> 1;
    LL sum = 0; 
    if ( l <= Mid ) sum += Query(lson, l, r);
    if ( Mid < r ) sum += Query(rson, l, r);
    return sum;
}

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS1(int u, int x)
{
    dis[u] = ++ x; size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( dis[v] || f[u] == v ) continue ;
        f[v] = u;
        DFS1(v, x);
        if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
        size[u] += size[v];
    }
}

inline void DFS2(int u, int t)
{
    id[u] = ++ cnt; p[cnt] = u;
    top[u] = t;
    if ( !son[u] ) return ;
    DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
        DFS2(v, v);
    }
}

inline LL Query1(int u, int v)
{
    LL sum = 0;
    while ( top[u] != top[v] ) 
    {
        if ( dis[top[u]] < dis[top[v]] ) swap(u, v);
        sum = (sum + Query(1, id[top[u]], id[u]));
        u = f[top[u]];
    }
    if ( id[u] == 0 || id[v] == 0 ) return sum;
    if ( dis[u] > dis[v] ) swap(u, v);
    sum += Query(1, id[u], id[v]);
    return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("data1.in", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m); r = 1;
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    DFS1(r, 0);
    DFS2(r, r);
    Build(1, 1, n);
//    REP(i, 1, n) printf("%d ", id[i]);
    REP(i, 1, m)
    {
        int k, x, y, z; scanf("%d", &k);
        if ( k == 1 ) 
        {
            scanf("%d%d", &x, &z);
            Update(1, id[x], id[x], z);
        }
        if ( k == 2 )
        {
            scanf("%d%d", &x, &z);
            Update(1, id[x], id[x] + size[x] - 1, z);
        }
        if ( k == 3 ) 
        {
            scanf("%d", &x);
            printf("%lld\n", Query1(r, x));
        }
    }
    return 0;
}
