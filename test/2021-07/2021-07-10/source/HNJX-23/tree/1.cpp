#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>

const int maxn = 4e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, f[maxn], g[maxn], h[maxn], a[maxn], ans;
int dis[maxn], anc[maxn], Root = 1, size[maxn], id[maxn], dfn[maxn], tot, son[maxn]; 
bool b[maxn];

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
    a[u] = f[u]; b[u] = true; ans ^= a[u];
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
    dfn[u] = ++ tot; id[tot] = u;
    if ( son[u] ) DFS3(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == son[u] || v == anc[u] ) continue ;
        DFS3(v, v);
    }
}

inline void Change(int l, int r)
{
    REP(i, l, r)
    {
        int x = id[i];
        ans ^= a[x]; b[x] ^= 1; 
    }
}

inline void Modify(int x, int val)
{
    if ( b[x] ) ans ^= a[x] ^ val;
    a[x] = val;
}

inline int LCA(int x, int y)
{
    while ( x != y ) 
    {
        if ( dis[x] < dis[y] ) swap(x, y);
        x = anc[x];
    }
    return x;
}

inline void Rotate(int x)
{
    Modify(x, max(h[x], f[x])); 
    int t = LCA(Root, x);
    while ( Root != t ) 
    {
        Modify(Root, f[Root]);
        Root = anc[Root];
    }
    Root = x;
    while ( x != t ) 
    {
        Modify(anc[x], g[x]);
        x = anc[x];
    }
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d%d", &n, &m); g[1] = -1;
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS1(1, 0); DFS2(1, 0); DFS3(1, 1);
    while ( m -- ) 
    {
        int op, u, v, x; scanf("%d", &op);
        if ( op == 1 ) 
        {
            scanf("%d%d%d", &u, &v, &x);
            while ( u != v )
            {
                if ( dis[u] < dis[v] ) swap(u, v);
                ans ^= a[u]; b[u] ^= 1; u = anc[u];
            }
            ans ^= a[u]; b[u] ^= 1; 
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
                    int x = Root; while ( anc[x] != u ) x = anc[x];
                    Change(dfn[x], dfn[x] + size[x] - 1);
                }
            }
        }
        Rotate(x); printf("%d\n", ans); 
    }
    return 0;
}