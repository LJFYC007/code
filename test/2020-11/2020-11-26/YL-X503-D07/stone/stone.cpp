/***************************************************************
	File name: stone.cpp
	Author: ljfcnyali
	Create time: 2020年11月26日 星期四 10时55分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6e5 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, m, p[maxn], cnt, pos, dis[maxn];
int anc[maxn][20], Stack[maxn], top, ans[maxn], f[maxn], g[maxn], dep[maxn];
vector<pii> Edge[maxn];
bool vis[maxn];

inline bool cmp(int a, int b) { return p[a] < p[b]; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Add(int u, int v) 
{ 
    if ( u == v ) return ;
    int w = abs(dis[u] - dis[v]); Edge[u].push_back(pii(v, w)); Edge[v].push_back(pii(u, w)); 
}

inline void DFS(int u, int fa)
{
    p[u] = ++ cnt;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    { 
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; DFS(v, u); anc[v][0] = u; 
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 18; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 18; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

inline int Get(int x, int t)
{
    for ( int i = 18; i >= 0; -- i ) if ( t >= (1 << i) ) { t -= (1 << i); x = anc[x][i]; }
    return x;
}

inline void Build(vector<int> a)
{
    sort(a.begin(), a.end(), cmp); top = 1; Stack[1] = a[0]; Edge[a[0]].clear();
    for ( int i = 1; i < a.size(); ++ i )
    {
        int it = a[i], t = LCA(it, Stack[top]);
        if ( t != Stack[top] ) 
        {
            while ( p[t] < p[Stack[top - 1]] ) 
            { 
                Add(Stack[top - 1], Stack[top]);
                -- top;
            }
            if ( t == Stack[top - 1] ) { Add(t, Stack[top]); -- top; }
            else { Edge[t].clear(); Add(t, Stack[top]); Stack[top] = t; }
        }
        Edge[it].clear(); Stack[++ top] = it;
    }
    while ( top > 1 ) { Add(Stack[top - 1], Stack[top]); -- top; }
}

inline void DFS1(int u, int fa)
{
    if ( dep[u] > dep[pos] ) pos = u;
    for ( auto v : Edge[u] ) if ( v.first != fa ) { dep[v.first] = dep[u] + v.second; DFS1(v.first, u); }
}

int main()
{
    freopen("stone.in", "r", stdin);
    freopen("stone.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 2, n) { int x; scanf("%d", &x); add(x, i); add(i, x); }
    dis[1] = 1; DFS(1, 0); REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    scanf("%d", &m);
    REP(i, 1, n) ans[i] = f[i] = g[i] = 2 * n; 
    REP(o, 1, m) 
    {
        vector<int> a; int k; scanf("%d", &k); 
        REP(j, 1, k) { int x; scanf("%d", &x); a.push_back(x); }
        Build(a); pos = a[0]; dep[pos] = 0; DFS1(a[0], 0); 
        int s = pos; dep[pos] = 0; DFS1(pos, 0); int t = pos, len = dep[pos], x;
        if ( dis[s] > dis[t] ) x = Get(s, len / 2);
        else x = Get(t, len / 2);
        if ( len & 1 ) g[x] = min(g[x], len);
        else f[x] = min(f[x], len);
    }
    queue<int> Q;
    REP(i, 1, n) 
    {
        if ( f[i] != 2 * n ) { ans[i] = min(ans[i], f[i]); if ( !vis[i] ) { Q.push(i); vis[i] = true; } }
        if ( g[i] != 2 * n ) 
        {
            ans[i] = min(ans[i], g[i] + 1); if ( !vis[i] ) { Q.push(i); vis[i] = true; }
            int x = anc[i][0]; if ( !x ) continue ;
            ans[x] = min(ans[x], g[i] + 1); if ( !vis[x] ) { Q.push(x); vis[x] = true; }
        }
    }
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( ans[v] > ans[u] + 2 ) 
            {
                ans[v] = ans[u] + 2;
                if ( !vis[v] ) { Q.push(v); vis[v] = true; }
            }
        }
        vis[u] = false;
    }
    REP(i, 1, n) printf("%d\n", ans[i] / 2);
    return 0;
}
