#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1

const int maxn = 4e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, f[maxn], g[maxn], h[maxn];
int dis[maxn], anc[maxn], Root = 1, size[maxn], id[maxn], dfn[maxn], top[maxn], tot, son[maxn]; 
struct node { int f, g, a, sf, sg, sa, lazy, tag; } Tree[maxn << 2];

inline void PushUp(int root) 
{
    Tree[root].a = Tree[lson].a ^ Tree[rson].a;
    Tree[root].sf = Tree[lson].sf ^ Tree[rson].sf;
    Tree[root].sg = Tree[lson].sg ^ Tree[rson].sg;
    Tree[root].sa = Tree[lson].sa ^ Tree[rson].sa;
}

inline void PushTag1(int root, int lazy)
{
    Tree[root].lazy = lazy; 
    Tree[root].a = lazy == 1 ? Tree[root].f : Tree[root].g;
    Tree[root].sa = lazy == 1 ? Tree[root].sf : Tree[root].sg;
}

inline void PushTag2(int root)
{
    Tree[root].tag ^= 1;
    Tree[root].sa ^= Tree[root].a; Tree[root].sf ^= Tree[root].f; Tree[root].sg ^= Tree[root].g;
}

inline void PushDown(int root)
{
    if ( Tree[root].lazy ) { PushTag1(lson, Tree[root].lazy); PushTag1(rson, Tree[root].lazy); Tree[root].lazy = 0; }
    if ( Tree[root].tag ) { PushTag2(lson); PushTag2(rson); Tree[root].tag = 0; }
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) 
    {
        Tree[root].f = Tree[root].sf = Tree[root].a = Tree[root].sa = f[id[l]];
        Tree[root].g = Tree[root].sg = g[son[id[l]]]; return ;
    }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Tree[root].f = Tree[lson].f ^ Tree[rson].f; Tree[root].g = Tree[lson].g ^ Tree[rson].g;
    PushUp(root);
}

inline void Modify1(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) { PushTag2(root); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify1(lson, l, Mid, L, R);
    if ( Mid < R ) Modify1(rson, Mid + 1, r, L, R);
    PushUp(root);
}

inline void Modify2(int root, int l, int r, int pos, int val)
{
    if ( l == r ) 
    { 
        Tree[root].a = val;
        Tree[root].sa = Tree[root].tag ? 0 : val;
        return ; 
    }
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) Modify2(lson, l, Mid, pos, val);
    else  Modify2(rson, Mid + 1, r, pos, val);
    PushUp(root);
}

inline void Modify3(int root, int l, int r, int L, int R, int val)
{
    if ( L > R ) return ;
    if ( L <= l && r <= R ) { PushTag1(root, val); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify3(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify3(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        dis[v] = dis[u] + 1; anc[v] = u;
        DFS1(v, u); size[u] += size[v];
        if ( size[v] > size[son[u]] ) son[u] = v;
        f[u] = max(f[u], f[v] + 1);
    }
}

inline void DFS2(int u, int fa)
{
    int Max = -1, pos = 0, Maxx = -1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( f[v] > Max ) { Maxx = Max; Max = f[v]; pos = v; }
        else Maxx = max(Maxx, f[v]);
    }
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        if ( v == pos ) g[v] = max(g[u], Maxx) + 1;
        else g[v] = max(g[u], Max) + 1;
        h[v] = g[v] + 1; DFS2(v, u);
    }
}

inline void DFS3(int u, int t)
{
    dfn[u] = ++ tot; id[tot] = u; top[u] = t;
    if ( son[u] ) DFS3(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == son[u] || v == anc[u] ) continue ;
        DFS3(v, v);
    }
}

inline void Change(int l, int r) { if ( l <= r ) Modify1(1, 1, n, l, r); }
inline int LCA(int x, int y)
{
    while ( top[x] != top[y] ) { if ( dis[top[x]] < dis[top[y]] ) swap(x, y); x = anc[top[x]]; }
    return dis[x] < dis[y] ? x : y;
}

inline void Rotate(int x)
{
    Modify2(1, 1, n, dfn[x], max(h[x], f[x])); 
    int t = LCA(Root, x);
    while ( top[Root] != top[t] ) 
    {
        Modify3(1, 1, n, dfn[top[Root]], dfn[Root], 1);
        Root = anc[top[Root]];
    }
    Modify3(1, 1, n, dfn[t] + 1, dfn[Root], 1);
    Root = x;
    while ( top[x] != top[t] ) 
    {
        Modify3(1, 1, n, dfn[top[x]], dfn[x] - 1, 2);
        Modify2(1, 1, n, dfn[anc[top[x]]], g[top[x]]);
        x = anc[top[x]];
    }
    Modify3(1, 1, n, dfn[t], dfn[x] - 1, 2);
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d%d", &n, &m); g[1] = -1;
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS1(1, 0); DFS2(1, 0); DFS3(1, 1);
    Build(1, 1, n);
    while ( m -- ) 
    {
        int op, u, v, x; scanf("%d", &op);
        if ( op == 1 ) 
        {
            scanf("%d%d%d", &u, &v, &x);
            while ( top[u] != top[v] ) 
            {
                if ( dis[top[u]] < dis[top[v]] ) swap(u, v);
                Change(dfn[top[u]], dfn[u]); u = anc[top[u]];
            }
            if ( dis[u] > dis[v] ) swap(u, v);
            Change(dfn[u], dfn[v]);
        }
        else 
        {
            scanf("%d%d", &u, &x);
            if ( dfn[Root] < dfn[u] || dfn[Root] > dfn[u] + size[u] - 1 ) 
                Change(dfn[u], dfn[u] + size[u] - 1);
            else 
            {
                Change(1, n);
                if ( u != Root ) 
                {
                    int x = Root; while ( dis[anc[top[x]]] > dis[u] ) x = anc[top[x]];
                    if ( anc[top[x]] != u ) x = son[u]; else x = top[x];
                    Change(dfn[x], dfn[x] + size[x] - 1);
                }
            }
        }
        Rotate(x); printf("%d\n", Tree[1].sa); 
    }
    return 0;
}