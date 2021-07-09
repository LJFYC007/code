/***************************************************************
	File name: P1453.cpp
	Author: ljfcnyali
	Create time: 2019年06月23日 星期日 20时47分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int Begin[maxn * 2], Next[maxn * 2], To[maxn * 2], e;
int n, p[maxn], dp[maxn][2], s, t, k1, k2;
double ans, k;
bool vis[maxn];

inline void add(int u, int v)
{
    ++ u; ++ v;
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS(int u, int fa)
{
    vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( v == fa ) continue ;
        if ( vis[v] ) 
        { 
            s = u; t = v; 
            k1 = i; k2 = (i % 2 == 0) ? i - 1 : i + 1;
            continue ; 
        }
        vis[v] = true;
        DFS(v, u);
    }
}

inline void DP(int u, int fa)
{
    dp[u][1] = p[u]; dp[u][0] = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        if ( i == k1 || i == k2 ) continue ;
        int v = To[i];
        if ( v == fa ) continue ;
        DP(v, u);
        dp[u][1] += dp[v][0];
        dp[u][0] += max(dp[v][0], dp[v][1]);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); REP(i, 1, n) scanf("%d", &p[i]);
    REP(i, 1, n) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    scanf("%lf", &k);
    DFS(1, 0);
    DP(s, 0); 
    ans = max(ans, (double)dp[s][0]);
    DP(t, 0);
    printf("%.1lf\n", k * max(ans, (double)dp[t][0]));
    return 0;
}
