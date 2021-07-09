/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2019年09月29日 星期一 09时20分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 600010;

int Begin[maxn], Next[maxn], To[maxn], e;
int dis[maxn], son[maxn], f[maxn], size[maxn], p[maxn], top[maxn];
int n, m, q, r, id[maxn], cnt;

struct node
{
    int u, v;
} a[maxn];

struct TREE
{
    int l, r, len;
    LL val, lazy;
} Tree[maxn * 2];

inline void Push_up(int root)
{
    Tree[root].val = Tree[lson].val + Tree[rson].val;
}

inline void Push_down(int root)
{
    if ( !Tree[root].lazy ) return ;
    Tree[lson].lazy += Tree[root].lazy;
    Tree[rson].lazy += Tree[root].lazy;
    Tree[lson].val += Tree[lson].len * Tree[root].lazy;
    Tree[rson].val += Tree[rson].len * Tree[root].lazy;
    Tree[root].lazy = 0;
}

inline void Build(int root, int l, int r)
{
    Tree[root].l = l; Tree[root].r = r; Tree[root].len = r - l + 1;
    Tree[root].lazy = 0;
    if ( l == r ) { Tree[root].val = 0; return ; }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Push_up(root);
}

inline void Update(int root, int l, int r, int val)
{
    if ( l <= Tree[root].l && Tree[root].r <= r ) 
    {
        Tree[root].val += Tree[root].len * val;
        Tree[root].lazy += val;
        return ;
    }
    Push_down(root);
    int Mid = Tree[root].l + Tree[root].r >> 1;
    if ( l <= Mid ) Update(lson, l, r, val);
    if ( Mid < r ) Update(rson, l, r, val);
    Push_up(root);
}

inline bool Query(int root, int l, int r)
{
    if ( l > r ) return false;
    if ( l <= Tree[root].l && Tree[root].r <= r ) return Tree[root].val;
    Push_down(root);
    int Mid = Tree[root].l + Tree[root].r >> 1;
    if ( l <= Mid ) if ( Query(lson, l, r) ) return true;
    if ( Mid < r ) if ( Query(rson, l, r) ) return true;
    return false;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

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

inline void Update1(int u, int v, int val)
{
    while ( top[u] != top[v] )
    {
        if ( dis[top[u]] < dis[top[v]] ) swap(u, v);
        Update(1, id[top[u]], id[u], val);
        u = f[top[u]];
    }
    if ( dis[u] > dis[v] ) swap(u, v);
    Update(1, id[u], id[v], val);
    Update(1, id[u], id[u], -val);
}

inline bool Query1(int u, int v)
{
    while ( top[u] != top[v] ) 
    {
        if ( dis[top[u]] < dis[top[v]] ) swap(u, v);
        if ( Query(1, id[top[u]], id[u]) ) return true;
        u = f[top[u]];
    }
    if ( dis[u] > dis[v] ) swap(u, v);
    return Query(1, id[u] + 1, id[v]); 
}

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    read(n); read(q);
    REP(i, 1, n - 1) { int u, v; read(u); read(v); add(u, v); add(v, u); }
    DFS1(1, 0); DFS2(1, 1); Build(1, 1, n);
    REP(i, 1, q)
    {
        int k, x, y; read(k);
        if ( k == 1 ) 
        {
            ++ m; read(a[m].u); read(a[m].v);
            Update1(a[m].u, a[m].v, 1);
        }
        if ( k == 2 ) 
        {
            read(x); read(y);
            if ( Query1(x, y) ) puts("YES");
            else puts("NO");
        }
        if ( k == 3 )
        {
            read(x);
            Update1(a[x].u, a[x].v, -1);
        }
    }
    return 0;
}
