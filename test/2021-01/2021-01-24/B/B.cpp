/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年01月24日 星期日 19时32分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;
const int INF = 1e6;

int n, m, k, s, f[maxn][21], Begin[maxn], Next[maxn * 3], To[maxn * 3], e, c[maxn], Val[maxn][21];
int dfn[maxn], low[maxn], tot, Stack[maxn], cnt, ans = INF, p[maxn], h[maxn], g[maxn], N;
vector<int> Edge[maxn], point;
bool vis[maxn], use[maxn], C[maxn], E[10][10];
map<int, bool> Map[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; Map[u][v] = true; } 

inline void Add(int u, int v) { Edge[u].push_back(v); Edge[v].push_back(u); } 

inline void Tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ tot; Stack[++ cnt] = u;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( !dfn[v] ) 
        { 
            Tarjan(v, u); low[u] = min(low[u], low[v]); 
            if ( low[v] == dfn[u] ) 
            {
                ++ m; Add(u, m);
                while ( Stack[cnt] != v ) { Add(Stack[cnt], m); -- cnt; }
                Add(Stack[cnt], m); -- cnt;
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}

inline void DFS1(int u)
{
    vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        if ( use[v] && !vis[v] ) DFS1(v);
    }
}

inline bool Check()
{
    for ( auto it : point ) { vis[it] = false; use[it] = true; } 
    DFS1(point[0]); 
    for ( auto it : point ) use[it] = false; 
    for ( auto it : point ) if ( !vis[it] ) return false;
    return true;
}

inline void DFS(int u, int fa)
{
    for ( auto v : Edge[u] ) if ( v != fa ) DFS(v, u);

    if ( u <= n ) REP(i, 1, k) 
    {
        for ( auto v : Edge[u] ) if ( v != fa ) f[u][i] += f[v][i] - 1;
        ++ f[u][i];
    }
    else 
    {
        N = 0; for ( auto v : Edge[u] ) p[++ N] = v;
        assert(N <= s);
        int pos = 0; REP(i, 1, N) if ( p[i] == fa ) pos = i;
        REP(i, 0, (1 << N) - 1) C[i] = false; REP(i, 1, N) C[1 << i - 1] = true;
        REP(i, 1, N) REP(j, 1, N) if ( Map[p[i]].count(p[j]) ) E[i][j] = true; else E[i][j] = false;
        REP(i, 1, (1 << N) - 1) if ( C[i] ) 
            REP(j, 1, N) if ( !((i >> j - 1) & 1) && !C[i | (1 << j - 1)] ) 
            {
                REP(k, 1, N) if ( ((i >> k - 1) & 1) && E[k][j] ) { C[i | (1 << j - 1)] = true; break ; } 
            }

        REP(i, 1, (1 << N) - 1) 
        {
            g[i] = INF; if ( !C[i] ) { REP(j, 1, k) Val[i][j] = INF; continue ; }
            point.clear(); REP(j, 1, N) if ( (i >> j - 1) & 1 ) point.push_back(p[j]); 
            REP(j, 1, k) 
            { 
                Val[i][j] = 1; 
                for ( auto it : point ) if ( it != fa ) Val[i][j] += f[it][j] - 1; 
                g[i] = min(g[i], Val[i][j]); 
            }
        }
        REP(i, 1, (1 << N) - 1) h[i] = INF;
        REP(i, 0, (1 << N) - 1) if ( h[i] < INF ) 
        {
            int s = (1 << N) - 1 - i;
            for ( int j = s; j; j = s & (j - 1) ) if ( !((j >> pos - 1) & 1) )
                h[i | j] = min(h[i | j], h[i] + g[j]);
        }
        REP(Col, 1, k)
        {
            f[u][Col] = INF;
            REP(i, 1, (1 << N) - 1) if ( (i >> pos - 1) & 1 ) 
                f[u][Col] = min(f[u][Col], Val[i][Col] + h[(1 << N) - 1 - i]);
        }
    }
    if ( c[u] ) { REP(i, 1, k) if ( i != c[u] ) f[u][i] = INF; }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &k, &s);
    REP(i, 1, n) scanf("%d", &c[i]);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    m = n; Tarjan(1, 0); DFS(1, 0);
    REP(i, 1, k) ans = min(ans, f[1][i]);
    printf("%d\n", ans);
    return 0;
}
