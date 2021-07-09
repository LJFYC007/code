#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>

const int maxn = 4e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, a[maxn];
int size[maxn], dfn[maxn], son[maxn], p[maxn], f[maxn], tot, top[maxn];
set<pii> Set[maxn];

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
    if ( son[u] ) { DFS2(son[u]); top[u] = top[son[u]]; }
    else top[u] = u;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
        DFS2(v);
    }
}

inline int Solve(int u, int val)
{
    auto it = Set[u].lower_bound(pii(val, 0));
    if ( it != Set[u].end() ) return Solve(it -> second, val);
    return u;
}

int main()
{
    freopen("fall.in", "r", stdin);
    freopen("fall.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    DFS1(1, 0); DFS2(1); 
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
        }
        else 
        {
            int val; scanf("%d", &val);
            printf("%d\n", Solve(1, val));
        }
    }
    return 0;
}