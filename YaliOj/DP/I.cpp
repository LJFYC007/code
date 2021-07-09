/***************************************************************
	File name: P2016.cpp
	Author: ljfcnyali
	Create time: 2019年06月24日 星期一 09时42分19秒
***************************************************************/
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>
#include<map>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;

int Begin[maxn], Next[maxn], To[maxn], e;
int dp[maxn][3], n;

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS(int u, int fa)
{
    dp[u][0] = 1;
    int Min = 0x3f3f3f3f;
    bool flag = false;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        dp[u][0] += min(dp[v][0], min(dp[v][1], dp[v][2]));
        dp[u][2] += min(dp[v][0], dp[v][1]);
        if ( dp[v][0] < dp[v][1] )
        {
            flag = true;
            dp[u][1] += dp[v][0];
        }
        else
        {
            Min = min(Min, dp[v][0] - dp[v][1]);
            dp[u][1] += dp[v][1];
        }
    }
    if ( flag == false ) dp[u][1] += Min;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n - 1)
    {
        int u, v; scanf("%d%d", &u, &v);
        add(u, v); add(v, u);
    }
    DFS(1, 0);
    printf("%d\n", min(dp[1][0], dp[1][1]));
    return 0;
}
