/***************************************************************
	File name: P2495.cpp
	Author: ljfcnyali
	Create time: 2019年08月09日 星期五 19时56分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 2000010;
const int INF = 1000000000000000000;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, q, m, dis[maxn], dfn[maxn], cnt, anc[maxn][20];
int a[maxn], Stack[maxn], top, dp[maxn], H[maxn];
bool vis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void Add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    dfn[u] = ++ cnt;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u; H[v] = min(H[u], W[i]);
        DFS1(v, u);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 19; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 19; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

inline int cmp(int x, int y) { return dfn[x] < dfn[y]; }

inline void Get_Tree()
{
    Stack[top = 1] = 1; Begin[1] = 0;
    REP(i, 1, m)
    {
        if ( a[i] == 1 ) continue ;
        int fa = LCA(Stack[top], a[i]);
        if ( Stack[top] != fa ) 
        {
            while ( dfn[fa] < dfn[Stack[top - 1]] ) { Add(Stack[top - 1], Stack[top]); -- top; }
            if ( dfn[fa] != dfn[Stack[top - 1]] ) { Begin[fa] = 0; Add(fa, Stack[top]); Stack[top] = fa; }
            else Add(fa, Stack[top --]);
        }
        Begin[a[i]] = 0; Stack[++ top] = a[i];
    }
    REP(i, 1, top - 1) Add(Stack[i], Stack[i + 1]);
}

inline void DFS2(int u, int fa)
{
    int son = 0; dp[u] = 0;
    if ( vis[u] ) { dp[u] = H[u]; return ; }
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS2(v, u);
        dp[u] += min(dp[v], H[v]);
        ++ son;
    }
    if ( !son ) dp[u] = H[u];
    else dp[u] = min(dp[u], H[u]);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
    dis[1] = 1; H[1] = INF; DFS1(1, 0);
    REP(j, 1, 19) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    scanf("%lld", &q);
    REP(o, 1, q)
    {
        scanf("%lld", &m);
        REP(i, 1, m) { scanf("%lld", &a[i]); vis[a[i]] = true; }
        sort(a + 1, a + m + 1, cmp);
        Get_Tree();
        DFS2(1, 0);
        printf("%lld\n", dp[1]);
        REP(i, 1, m) vis[a[i]] = false;
    }
    return 0;
}
