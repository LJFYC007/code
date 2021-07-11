#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, Root = 1, f[maxn], dis[maxn], anc[maxn];
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    anc[u] = fa; f[u] = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v] = u;
        DFS(v, u); f[u] = max(f[u], f[v] + 1);
    }
}

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS1(v, u);
    }
    vis[u] ^= 1;
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree1.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS(1, 0);
    while ( m -- )
    {
        int op, u, v, x; scanf("%d", &op);
        if ( op == 1 ) 
        {
            scanf("%d%d", &u, &v);
            while ( u != v ) { if ( dis[u] < dis[v] ) swap(u, v); vis[u] ^= 1; u = anc[u]; }
            vis[u] ^= 1;
        }
        else { scanf("%d", &u); DFS1(u, anc[u]); }
        scanf("%d", &Root); dis[Root] = 1; DFS(Root, 0);
        int ans = 0; REP(i, 1, n) ans ^= !vis[i] ? f[i] : 0;
        printf("%d\n", ans);
    }
    return 0;
}