/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年07月11日 星期六 10时43分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], ans; 
bool vis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS(int u, int dep)
{
    ans = max(ans, dep);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[v] ) continue ;
        vis[v] = true; DFS(v, dep + W[i]); vis[v] = false;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%d", &n); 
    REP(i, 1, 3 * (n - 2))
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    REP(i, 1, n) { vis[i] = true; DFS(i, 0); vis[i] = false; }
    printf("%d\n", ans);
    return 0;
}
