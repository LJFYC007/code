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

const int maxn = 210;

int dp[maxn][maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn], n, q;
// int dis[maxn], sum[maxn];

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline void DFS(int u, int f)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( v == f ) continue ; 
        dp[v][1] = W[i];
        // dis[v] = dis[u] + W[i];
        // sum[v] = sum[u] + 1;
        DFS(v, u);
        for ( int j = q; j >= 1; -- j )
            REP(k, 0, j)
                // if ( (j - k - sum[v]) >= 0 )
                    // dp[u][j] = max(dp[u][j], dp[u][j - k - sum[v]] + dp[v][k] + dis[v]);
                if ( (j != k && j != 1) || u == 1 )
                    dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[v][k]);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &q);
    REP(i, 1, n - 1)
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    DFS(1, 0);
    printf("%d\n", dp[1][q]);
    return 0;
}
