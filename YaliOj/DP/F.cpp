/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年06月25日 星期二 16时34分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int Begin[maxn], Next[maxn], To[maxn], e;
int a[maxn], n, dp[maxn][2];

inline void add(int u, int v)
{
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
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%d", &n) )
    {
        if ( n == 0 ) return 0;
        REP(i, 1, n) scanf("%d", &a[i]);
        mem(dp); mem(Begin); e = 0;
        REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
        DFS(1, 0);
        printf("%d\n", max(dp[1][0], dp[1][1]));
    }
    return 0;
}
