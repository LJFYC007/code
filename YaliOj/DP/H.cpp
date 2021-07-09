/***************************************************************
	File name: H.cpp
	Author: ljfcnyali
	Create time: 2019年06月25日 星期二 15时55分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1010;

int Begin[maxn], Next[maxn], To[maxn], e;
int a[maxn], dp[maxn][maxn], n, m;

inline void add(int u, int v)
{
    ++ u; ++ v;
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS(int u, int fa)
{
    dp[u][1] = a[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        for ( int j = m; j >= 1; -- j ) 
            REP(k, 0, j - 1)
                dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[v][k]);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%d%d", &n, &m) )
    {
        REP(i, 1, n) scanf("%d", &a[i]);
        e = 0; mem(Begin); mem(dp);
        REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
        DFS(1, 0);
        int ans = 0;
        REP(i, 1, n) ans = max(ans, dp[i][m]);
        printf("%d\n", ans);
    }
    return 0;
}
