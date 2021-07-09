/***************************************************************
	File name: 1.cpp
	Author: ljfcnyali
	Create time: 2019年08月11日 星期日 11时17分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int LL
typedef long long LL;

const int maxn = 500010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, dis[maxn], d[maxn], anc[maxn][20], H1[maxn], H2[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u;
        H1[v] = H1[u] + W[i];
        DFS1(v, u);
    }
}

inline void DFS2(int u, int fa)
{
    int sum = 1e15;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( !H2[v] ) DFS2(v, u);
        sum = min(sum, H2[v] + W[i]);
    }
    H2[u] = sum;
}

inline void DFS3(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        H2[v] = min(H2[v], H2[u] + W[i]);
        DFS3(v, u);
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

signed main()
{
    freopen("oitree.in", "r", stdin);
    freopen("oitree.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 2, n) { int fa, w; scanf("%lld%lld", &fa, &w); add(fa, i, w); add(i, fa, w); ++ d[fa]; }
    dis[1] = 1; DFS1(1, 0);
    REP(j, 1, 19) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, n) 
        if ( !d[i] ) 
        {
            int x; scanf("%lld", &x);
            H2[i] = x;
        }
    DFS2(1, 0); H2[1] = 1e15; DFS3(1, 0); H2[1] = 0;
    REP(i, 1, m)
    {
        int u, v; scanf("%lld%lld", &u, &v);
        int ans = H1[u] + H1[v] - 2 * H1[LCA(u, v)];
        ans = min(ans, H1[u] + H2[v]);
        ans = min(ans, H2[u] + H1[v]);
        ans = min(ans, H2[u] + H2[v]);
        printf("%lld\n", ans);
    }
    return 0;
}
