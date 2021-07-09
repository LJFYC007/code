/***************************************************************
	File name: portal.cpp
	Author: ljfcnyali
	Create time: 2020年11月16日 星期一 15时22分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], f[maxn], dis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline int Solve(int u, int fa, int x)
{
    int Max = x, ans = 0, pos = -1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        ans += Solve(v, u, x + W[i]) + W[i];
        if ( dis[v] + W[i] > Max ) { Max = dis[v] + W[i]; pos = v; }
    }
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || v == pos ) continue ;
        ans += min(dis[v] + W[i], x);
    }
    dis[u] = Max; return ans;
}

inline void DFS(int u, int fa)
{
    f[u] = Solve(u, fa, 0);
    int ret = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u); ret += f[v] + 2 * W[i];
    }
    f[u] = min(f[u], ret);
}

signed main()
{
    freopen("portal.in", "r", stdin);
    freopen("portal.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
    DFS(1, 0);
    printf("%lld\n", f[1]);    
    return 0;
}
