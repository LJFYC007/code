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

const int maxn = 200010;

int Begin[maxn], Next[maxn], To[maxn], e;
int dis[maxn], son[maxn], f[maxn], size[maxn], p[maxn], top[maxn];
int n, m, Mod, r, a[maxn], id[maxn], cnt;

struct node
{
    int l, r, len, val, lazy;
} Tree[maxn * 2];

inline void Push_up(int root)
{
    Tree[root].val = Tree[lson].val + Tree[rson].val;
}

inline void Push_down(int root)
{
    if ( Tree[root].len == 1 ) { Tree[root].lazy = 0; return ; }
    Tree[lson].lazy = (Tree[lson].lazy + Tree[root].lazy) % Mod;
    Tree[rson].lazy = (Tree[rson].lazy + Tree[root].lazy) % Mod;
    Tree[lson].val = (Tree[lson].val + Tree[lson].len * Tree[root].lazy) % Mod;
    Tree[rson].val = (Tree[rson].val + Tree[rson].len * Tree[root].lazy) % Mod;
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

inline void Update(int root, int l, int r, int val)
{
    if ( l <= Tree[root].l && Tree[root].r <= r ) 
    {
        Tree[root].val = (Tree[root].val + Tree[root].len * val) % Mod;
        Tree[root].lazy = (Tree[root].lazy + val) % Mod;
        return ;
    }
    Push_down(root);
    int Mid = Tree[root].l + Tree[root].r >> 1;
    if ( l <= Mid ) Update(lson, l, r, val);
    if ( Mid < r ) Update(rson, l, r, val);
    Push_up(root);
}

inline int Query(int root, int l, int r)
{
    Push_down(root);
    if ( l <= Tree[root].l && Tree[root].r <= r ) return Tree[root].val;
    int Mid = Tree[root].l + Tree[root].r >> 1, sum = 0; 
    if ( l <= Mid ) sum += Query(lson, l, r);
    if ( Mid < r ) sum += Query(rson, l, r);
    return sum % Mod;
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

inline void Update1(int u, int v, int val)
{
    val %= Mod;
    while ( top[u] != top[v] )
    {
        if ( dis[top[u]] < dis[top[v]] ) swap(u, v);
        Update(1, id[top[u]], id[u], val);
        u = f[top[u]];
    }
    if ( dis[u] > dis[v] ) swap(u, v);
    Update(1, id[u], id[v], val);
}

inline int Query1(int u, int v)
{
    int sum = 0;
    while ( top[u] != top[v] ) 
    {
        if ( dis[top[u]] < dis[top[v]] ) swap(u, v);
  //      printf("%d %d\n", id[top[u]], id[u]);
        sum = (sum + Query(1, id[top[u]], id[u])) % Mod;
        u = f[top[u]];
    }
    if ( id[u] == 0 || id[v] == 0 ) return sum % Mod;
    if ( dis[u] > dis[v] ) swap(u, v);
//    printf("%d %d\n", id[u], id[v]);
    sum += Query(1, id[u], id[v]);
    return sum % Mod;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &r, &Mod);
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
            scanf("%d%d%d", &x, &y, &z);
            Update1(x, y, z);
        }
        if ( k == 2 ) 
        {
            scanf("%d%d", &x, &y);
            printf("%d\n", Query1(x, y));
        }
        if ( k == 3 )
        {
            scanf("%d%d", &x, &z);
            Update(1, id[x], id[x] + size[x] - 1, z);
        }
        if ( k == 4 ) 
        {
            scanf("%d", &x);
            printf("%d\n", Query(1, id[x], id[x] + size[x] - 1));
        }
    }
  //  REP(i, 1, 15) Push_down(i);
  //  REP(j, 1, 15) printf("%d %d %d %d\n", Tree[j].l, Tree[j].r, Tree[j].val, Tree[j].lazy);
    return 0;
}
