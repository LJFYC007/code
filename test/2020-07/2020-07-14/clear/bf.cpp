#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a ) 
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a ; }
#define max maxx
#define min minn
#define abs abss
#define pii pair<int, int>

const int maxn = 300010 * 2;
const int INF = 0x3f3f3f3f;

namespace Dinic
{
    int Begin[maxn], To[maxn], Next[maxn], W[maxn];
    int e = 1, dis[maxn];

    inline void add(int u, int v, int w)
    {
        To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
        swap(u, v); w = 0;
        To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
    }

    inline bool BFS(int s, int t)
    {
        queue<int> Q; Q.push(s);
        mem(dis); dis[s] = 1;
        while ( !Q.empty() )
        {
            int u = Q.front(); Q.pop();
            for ( int i = Begin[u]; i; i = Next[i] )
            {
                int v = To[i]; if ( dis[v] || !W[i] ) continue ;
                dis[v] = dis[u] + 1;
                if ( v == t ) return true;
                Q.push(v);
            }
        }
        return false;
    }

    inline int DFS(int u, int t, int flow)
    {
        if ( u == t || !flow ) return flow;
        int f = 0;
        for ( int i = Begin[u]; i; i = Next[i] )
        {
            int v = To[i]; if ( dis[v] != dis[u] + 1 || !W[i] ) continue ;
            int x = DFS(v, t, min(flow, W[i]));
            if ( !x ) continue ;
            flow -= x; f += x;
            W[i] -= x; W[i ^ 1] += x;
        }
        if ( !f ) dis[u] = 0;
        return f;
    }

    inline int Solve(int s, int t)
    {
        int Maxflow = 0;
        while ( BFS(s, t) )
            while ( int flow = DFS(s, t, INF) )
                Maxflow += flow;
        return Maxflow;
    }
}

int n, m, t, x[maxn], y[maxn];
pii a[maxn];

int main()
{
#ifndef ONLINE_JUDGE 
    freopen("clear.in", "r", stdin);
    freopen("clear1.out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &t);
    REP(i, 1, n) scanf("%d", &x[i]);
    REP(i, 1, m) scanf("%d", &y[i]);
    REP(i, 1, t) scanf("%d%d", &a[i].first, &a[i].second);

    int S = n + m + t + 1, T = S + 1, l = 2, r;
    REP(i, 1, n + m) Dinic :: add(S, i, 1); 
    r = Dinic :: e - 1;
    REP(i, 1, n) REP(j, 1, t) if ( a[j].first < x[i] ) Dinic :: add(i, j + n + m, 1);
    REP(i, 1, m) REP(j, 1, t) if ( a[j].second < y[i] ) Dinic :: add(i + n, j + n + m, 1);
    REP(i, n + m + 1, n + m + t) Dinic :: add(i, T, 1);

    int ans = 1, num = 0; 
    while ( (num += Dinic :: Solve(S, T)) != t ) 
    {
        for ( int i = l; i <= r; i += 2 ) Dinic :: W[i] ++;
        ++ ans; 
        if ( ans > 1000 ) { puts("-1"); return 0; }
    }
    printf("%d\n", ans);
    return 0;
}

