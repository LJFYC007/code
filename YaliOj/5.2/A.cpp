/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年06月11日 星期二 14时20分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1010;

int son[maxn][2], n, m, a[maxn], dp[maxn][maxn];
int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int size[maxn];

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline void DFS(int u)
{
    size[u] = 1; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( size[v] ) continue ;
        a[v] = W[i];
        if ( son[u][0] ) son[u][1] = v;
        else son[u][0] = v;
        DFS(v); size[u] += size[v];
    }
}

inline int DFS1(int u, int sum)
{
    if ( sum == 0 ) return 0;
    int l = son[u][0], r = son[u][1];
//    cerr << u << " " << sum << " " << l << " " << r << endl;
    if ( !l && !r ) return a[u];
    if ( dp[u][sum] ) return dp[u][sum];
    REP(i, 0, sum - 1)
        dp[u][sum] = max(dp[u][sum], DFS1(l, i) + DFS1(r, sum - i - 1) + a[u]); 
    return dp[u][sum];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
    DFS(1);
    DFS1(1, m + 1);
    printf("%d\n", dp[1][m + 1]);
    return 0;
}
