#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>

const int maxn = 4e5 + 10;
const int INF = 0x3f3f3f3f;
#define lson root << 1
#define rson root << 1 | 1

int n, m, Begin[maxn], Next[maxn], To[maxn], e, a[maxn];
int size[maxn], dfn[maxn], son[maxn], p[maxn], f[maxn], tot, top[maxn];
set<pii> Set[maxn];

struct node { int Max, Min; } Tree[maxn << 2];

inline void Modify(int root, int l, int r, int pos, int val, int op)
{
    if ( l == r ) 
    {
        if ( op == 0 ) Tree[root].Max = val;
        if ( op == 1 ) Tree[root].Min = val;
        return ;
    }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val, op);
    else Modify(rson, Mid + 1, r, pos, val, op);
    Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
}

inline int Query(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) 
    {
        if ( l == r ) return (Tree[root].Max < val && Tree[root].Min >= val) ? l + 1 : l;
        int Mid = l + r >> 1;
        if ( Tree[lson].Max < val && Tree[lson].Min >= val ) return Query(rson, Mid + 1, r, L, R, val);
        return Query(lson, l, Mid, L, R, val);
    }
    int Mid = l + r >> 1;
    if ( L <= Mid ) 
    {
        int x = Query(lson, l, Mid, L, R, val);
        if ( x <= Mid ) return x;
    }
    if ( Mid < R ) return Query(rson, Mid + 1, r, L, R, val);
    return min(r, R) + 1;
}

inline void Maintain(int pos, int x)
{
    auto it = Set[x].lower_bound(pii(a[son[x]], 0)); int val = 0;
    if ( it != Set[x].begin() ) { -- it; val = it -> first; }
    Modify(1, 1, n, pos, val, 0);
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    size[u] = 1; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS1(v, u); f[v] = u; size[u] += size[v];
        if ( size[v] > size[son[u]] ) son[u] = v;
        Set[u].insert(pii(a[v], v));
    }
}

inline void DFS2(int u)
{
    dfn[u] = ++ tot; p[tot] = u;
    if ( son[u] ) { DFS2(son[u]); top[u] = top[son[u]]; Maintain(dfn[son[u]], u); }
    else top[u] = u;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
        DFS2(v);
    }
}

inline int Solve(int u, int val)
{
    int pos = p[Query(1, 1, n, dfn[u] + 1, dfn[top[u]], val) - 1];
    auto it = Set[pos].lower_bound(pii(val, 0));
    if ( it != Set[pos].end() ) return Solve(it -> second, val);
    return pos;
}

int main()
{
    freopen("fall.in", "r", stdin);
    freopen("fall.out", "w", stdout);
    scanf("%d%d", &n, &m); REP(i, 1, n * 4) Tree[i].Min = INF;
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    DFS1(1, 0); DFS2(1);
    REP(i, 1, n) Modify(1, 1, n, dfn[i], a[i], 1);

    while ( m -- ) 
    {
        int op; scanf("%d", &op);
        if ( op == 1 ) 
        {
            int x, val; scanf("%d%d", &x, &val);
            if ( x == 1 ) continue ;
            Set[f[x]].erase(pii(a[x], x));
            a[x] = val;
            Set[f[x]].insert(pii(a[x], x));
            Modify(1, 1, n, dfn[x], a[x], 1);
            Maintain(dfn[son[f[x]]], f[x]);
        }
        else 
        {
            int val; scanf("%d", &val);
            printf("%d\n", Solve(1, val));
        }
    }
    return 0;
}