#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int maxn = 200010;

int Begin[maxn], Next[maxn], To[maxn], e, n, m, cnt;
int dfn[maxn], low[maxn], DAG[maxn], a[maxn], val[maxn], dp[maxn], Index;
int Stack[maxn], top;
bool vis[maxn];

struct node
{
    int u, v;
} p[maxn];

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void Tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ Index;
    vis[u] = true;
    Stack[++ top] = u;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( v == fa ) continue ;
        if ( !dfn[v] ) Tarjan(v, u);
        if ( vis[v] ) low[u] = min(low[u], low[v]);
    }
    if ( dfn[u] == low[u] )
    {
        ++ cnt;
        while ( Stack[top + 1] != u ) 
        {
            DAG[Stack[top]] = cnt;
            val[cnt] += a[Stack[top]];
            vis[Stack[top]] = false;
            -- top;
        }
    }
}

inline void DFS(int u, int fa)
{
    if ( dp[u] ) return ;
    dp[u] = val[u];
    int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( v == fa ) continue ;
        DFS(v, u);
        Max = max(Max, dp[v]);
    }
    dp[u] += Max;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, m)
    {
        int u, v; scanf("%d%d", &u, &v);
        add(u, v);
        p[i].u = u; p[i].v = v;
    }
    REP(i, 1, n) if ( !dfn[i] ) Tarjan(i, 0);
    e = 0; mem(Begin);
    REP(i, 1, m) if ( DAG[p[i].u] != DAG[p[i].v] ) add(DAG[p[i].u], DAG[p[i].v]);
    REP(i, 1, cnt) if ( !dp[i] ) DFS(i, 0);
    int ans = 0;
    REP(i, 1, cnt) ans = max(ans, dp[i]);
    printf("%d\n", ans);
    return 0;
}
