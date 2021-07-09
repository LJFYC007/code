/***************************************************************
  File name: teleport.cpp
Author: ljfcnyali
Create time: 2020年12月29日 星期二 10时24分28秒
 ***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2010;
const int INF = 1e18;

int n, k, son[maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn], fa[maxn];
int dis[maxn], f[maxn][maxn][22], anc[maxn], tot;

inline void add(int u, int v, int w) { fa[v] = u; To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

inline void DFS(int u)
{
    anc[++ tot] = u; REP(i, 1, tot - 1) REP(j, 0, min(20ll, k)) f[u][anc[i]][j] = INF;
    for ( int c = Begin[u]; c; c = Next[c] ) { int v = To[c]; dis[v] = dis[u] + W[c]; DFS(v); }
    REP(i, 1, tot - 1) REP(j, 0, min(20ll, k)) 
    {
        int sum1 = (j >= 1 ? dis[u] - dis[anc[i]] : 0), sum2 = INF;
        for ( int d = Begin[u]; d; d = Next[d] ) 
        {
            int v = To[d], tmp = min((j >= 1 ? f[v][u][j - 1] : INF), (anc[i] == n + 1 ? INF : f[v][anc[i]][j]));
            sum2 = min(sum2 + tmp, sum1 + f[v][anc[i]][j] + (j >= 1 ? - dis[u] + dis[anc[i]] : 0));
            sum1 += tmp;
        }
        f[u][anc[i]][j] = min(f[u][anc[i]][j], sum2);
    }
    if ( !son[u] ) REP(i, 1, tot - 1) REP(j, 0, min(20ll, k)) f[u][anc[i]][j] = dis[u] - dis[anc[i]];
    -- tot;
}

signed main()
{
    freopen("teleport.in", "r", stdin);
    freopen("teleport.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    REP(i, 2, n) { int f, w; scanf("%lld%lld", &f, &w); add(f, i, w); ++ son[f]; }
    anc[++ tot] = n + 1; DFS(1); REP(i, 1, min(k, 20ll)) printf("%lld\n", f[1][n + 1][i]);
    REP(i, 21, k) printf("%lld\n", f[1][n + 1][20]);
    return 0;
}
