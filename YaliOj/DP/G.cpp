// luogu-judger-enable-o2
/***************************************************************
    File name: P2016.cpp
    Author: ljfcnyali
    Create time: 2019年06月24日 星期一 09时42分19秒
***************************************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
#include<stack>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 4010;

int Begin[maxn], Next[maxn], To[maxn], e;
int dp[maxn][2], n;

inline void add(int u, int v)
{
    ++ u; ++ v;
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS(int u, int fa)
{
    dp[u][0] = 0; dp[u][1] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        dp[u][0] += dp[v][1];
        dp[u][1] += min(dp[v][0], dp[v][1]);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~ scanf("%d", &n) ) 
    {
        mem(Begin); e = 0; mem(dp);
        REP(i, 1, n)
        {
            int u, x; scanf("%d:(%d)", &u, &x);
            REP(j, 1, x) { int v; scanf("%d", &v); add(u, v); add(v, u); }
        }
        DFS(1, 0);
        printf("%d\n", min(dp[1][0], dp[1][1]));
    }
    return 0;
}
