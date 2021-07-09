/***************************************************************
	File name: P2585.cpp
	Author: ljfcnyali
	Create time: 2019年06月25日 星期二 08时15分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 500010;

int n = 1, len, son[maxn][2], x, dp[maxn][2];
char s[maxn];

inline void DFS(int u)
{
    if ( s[x] == '0' ) return ;
    if ( s[x] == '1' ) { son[u][0] = ++ n; ++ x; DFS(n); }
    if ( s[x] != '2' ) return ;
    son[u][0] = ++ n; ++ x; DFS(n);
    son[u][1] = ++ n; ++ x; DFS(n);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s); len = str(s);
    n = 1;
    DFS(1);
    for ( int i = n; i >= 1; -- i ) 
    {
        dp[i][1] = dp[son[i][0]][0] + dp[son[i][1]][0] + 1;
        dp[i][0] = max(dp[son[i][0]][1] + dp[son[i][1]][0], dp[son[i][0]][0] + dp[son[i][1]][1]);
    }
    printf("%d ", max(dp[1][1], dp[1][0]));
//    memset(dp, 0, sizeof(dp));
    for ( int i = n; i >= 1; -- i ) 
    {
        dp[i][1] = dp[son[i][0]][0] + dp[son[i][1]][0] + 1;
        dp[i][0] = min(dp[son[i][0]][1] + dp[son[i][1]][0], dp[son[i][0]][0] + dp[son[i][1]][1]);
    }
    printf("%d\n", min(dp[1][1], dp[1][0]));
    return 0;
}
