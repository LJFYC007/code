#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define pii pair<int, int>

const int maxn = 6e5 + 10;

int n, r[maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn], deg[maxn], ans; 
vector<int> Edge[maxn], E[maxn]; bool vis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS(int u, int fa, int dep)
{
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( dep >= W[i] ) 
        { 
            Edge[u].push_back(v); ++ deg[v];
            E[v].push_back(u);
            DFS(v, u, dep - W[i]);
        }
    }
}

inline void DFS1(int u)
{
    vis[u] = true;
    for ( auto v : Edge[u] ) if ( !vis[v] ) DFS1(v);
}

int main()
{
    freopen("infect.in", "r", stdin);
    freopen("infect.out", "w", stdout);
    scanf("%d", &n); REP(i, 1, n) scanf("%d", &r[i]);
    REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
    REP(i, 1, n) DFS(i, 0, r[i]);
    REP(i, 1, n) if ( !deg[i] ) { ++ ans; DFS1(i); }
    REP(i, 1, n) for ( auto it : E[i] ) Edge[i].push_back(it);
    REP(i, 1, n) if ( !vis[i] ) { ++ ans; DFS1(i); }
    printf("%d\n", ans);
    return 0;
}