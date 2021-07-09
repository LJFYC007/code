#include "swap.h"
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e = 1, W[maxn], deg[maxn], s, t, val[maxn];
bool vis[maxn], use[maxn], flag, Vis[maxn];
vector<pii> a;
struct node { int u, v, w; node(int a = 0, int b = 0, int c = 0) { u = a; v = b; w = c; } } Edge[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; ++ deg[v]; }

inline int DFS(int u)
{
    if ( u == t ) { use[u] = true; return 1; }
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[v] ) continue ;
        vis[v] = true; if ( DFS(v) ) { Vis[i] = Vis[i ^ 1] = use[u] = true; return 1; }
    }
    return 0;
}

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( vis[v] ) { flag = true; return ; }
        vis[v] = true; DFS1(v, u);
    }
}

inline bool Check(int x)
{
    REP(i, 1, e) Vis[i] = false;
    e = 1; REP(i, 1, n) Begin[i] = vis[i] = use[i] = deg[i] = 0;
    REP(i, 0, m - 1) if ( Edge[i].w <= x ) { add(Edge[i].u, Edge[i].v, Edge[i].w); add(Edge[i].v, Edge[i].u, Edge[i].w); }
    vis[s] = true; if ( !DFS(s) ) return false; 
    flag = false; 
    REP(i, 1, n) vis[i] = false; vis[s] = true; DFS1(s, 0);
    REP(i, 1, n) if ( vis[i] && deg[i] > 2 ) flag = true;
    return flag;
}

void init(int N, int M, vector<int> U, vector<int> V, vector<int> W) 
{
    n = N; m = M;
    REP(i, 0, m - 1) { ++ U[i]; ++ V[i]; val[V[i]] = W[i]; }
    REP(i, 0, m - 1) a.push_back(pii(W[i], V[i]));
    sort(a.begin(), a.end()); 
}

int getMinimumFuelCapacity(int X, int Y) 
{
    if ( X == 0 || Y == 0 ) return -1; ++ X; ++ Y;
    for ( auto i : a ) if ( i.second != Y && i.second != X ) return max(i.first, max(val[X], val[Y]));
    return -1;
    ++ X; ++ Y; s = X; t = Y;
    int L = 1, R = 1e9, ans = -1;
    while ( L <= R ) 
    {
        int Mid = (L + R) >> 1;
        if ( Check(Mid) ) { ans = Mid; R = Mid - 1; }
        else L = Mid + 1;
    }
    return ans;
}
