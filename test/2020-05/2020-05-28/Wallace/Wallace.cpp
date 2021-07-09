/***************************************************************
	File name: Wallace.cpp
	Author: ljfcnyali
	Create time: 2020年05月29日 星期五 09时49分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010 + 10;
const int INF = 0x3f3f3f3f;

int n, a[maxn], ans, sum;
struct node
{
    int Begin[maxn], Next[maxn], To[maxn], e, f[maxn];

    inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

    inline void DFS(int u, int fa)
    {
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            f[v] = u; DFS(v, u);
        }
    }
} A, B;

namespace Dinic
{
const int maxn = 1e6 + 10;
    int Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], W[maxn];

    inline void INIT() { mem(Begin); e = 1; }

    inline void add(int u, int v, int w)
    {
        To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; 
        swap(u, v);
        To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = 0; 
    }

    inline bool BFS(int s, int t)
    {
        REP(i, 1, t) dis[i] = 0; dis[s] = 1; 
        queue<int> Q; Q.push(s);
        while ( !Q.empty() ) 
        {
            int u = Q.front(); Q.pop();
            for ( int i = Begin[u]; i; i = Next[i] )
            {
                int v = To[i]; if ( dis[v] || !W[i] ) continue ;
                dis[v] = dis[u] + 1; Q.push(v);
                if ( v == t ) return true;
            }
        }
        return false;
    }

    inline int DFS(int u, int t, int flow)
    {
        if ( !flow || u == t ) return flow;
        int ret = 0;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( dis[v] != dis[u] + 1 ) continue ;
            int x = DFS(v, t, min(flow, W[i]));
            if ( x ) 
            {
                W[i] -= x; W[i ^ 1] += x;
                flow -= x; ret += x;
            }
        }
        return ret;
    }

    inline int Solve(int s, int t)
    {
        int ret = 0;
        while ( BFS(s, t) ) while ( int x = DFS(s, t, INF) ) ret += x;
        return ret;
    }
}

int main()
{
    freopen("Wallace.in", "r", stdin);
    freopen("Wallace.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d", &a[i]); if ( a[i] > 0 ) sum += a[i]; }
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); ++ u; ++ v; A.add(u, v); A.add(v, u); }
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); ++ u; ++ v; B.add(u, v); B.add(v, u); }
    REP(i, 1, n)
    {
        A.DFS(i, 0); B.DFS(i, 0);
        Dinic :: INIT();
        int S = n + 1, T = n + 2;
        REP(j, 1, n)
        {
            if ( j == i ) continue ;
            if ( a[j] > 0 ) Dinic :: add(S, j, a[j]);
            else Dinic :: add(j, T, -a[j]);
            if ( A.f[j] != i ) Dinic :: add(j, A.f[j], INF);
            if ( B.f[j] != i ) Dinic :: add(j, B.f[j], INF);
        }
        int ret = (sum - (a[i] > 0 ? a[i] : 0)) - Dinic :: Solve(S, T) + a[i];
        ans = max(ans, ret);
    }
    printf("%d\n", ans);
    return 0;
}
