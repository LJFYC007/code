#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>

const int maxn = 1e6 + 10;

int n, m, dfn[maxn], low[maxn], tot, S, T, size[maxn];
vector<int> Edge[maxn], b; bool use[maxn], vis[maxn];

inline void add(int u, int v) { Edge[u].push_back(v); }

inline void DFS(int u, int fa)
{
    low[u] = dfn[u] = ++ tot; size[u] = 1;
    for ( auto v : Edge[u] ) if ( use[v] ) 
    {
        if ( !dfn[v] ) 
        {
            DFS(v, u); low[u] = min(low[u], low[v]); size[u] += size[v];
            if ( low[v] > dfn[u] && size[v] % 2 == 1 ) { S = v; T = u; }
        }
        else if ( v != fa ) low[u] = min(low[u], dfn[v]);
    }
}

inline void DFS1(int u)
{
    b.push_back(u); use[u] = false;
    for ( auto v : Edge[u] ) if ( use[v] ) DFS1(v); 
}

inline bool Solve(vector<int> a)
{
    if ( !a.size() ) return true;
    // for ( auto it : a ) cerr << it << " "; cerr << endl;
    for ( auto it : a ) { use[it] = true; dfn[it] = low[it] = 0; vis[it] = false; } 
    tot = 0; S = T = 0;
    for ( auto it : a ) if ( !dfn[it] ) DFS(it, 0);
    if ( !S ) return false;
    for ( auto it : a ) vis[it] = false;

    use[S] = use[T] = false;
    vector<vector<int> > p;
    for ( auto it : a ) if ( use[it] ) 
    {
        b.clear(); DFS1(it);
        p.push_back(b);
    }

    for ( auto it : p ) if ( !Solve(it) ) return false;
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T; scanf("%d", &T); srand(time(0));
    while ( T -- )
    {
        scanf("%d%d", &n, &m); REP(i, 1, n) { use[i] = false; Edge[i].clear(); }
        REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
        vector<int> a; REP(i, 1, n) a.push_back(i);
        if ( Solve(a) ) puts("toutoi!");
        else puts("/dk");
    }
    return 0;
}