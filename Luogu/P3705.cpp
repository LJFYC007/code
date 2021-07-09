/***************************************************************
	File name: P3705.cpp
	Author: ljfcnyali
	Create time: 2019年10月11日 星期五 08时19分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100010;
const int INF = 0x3f3f3f3f;
const double eps = 1e-7;

int n, a[110][110], b[110][110], ans;

namespace MCMF 
{
    int Begin[maxn], Next[maxn], To[maxn], From[maxn], e = 1, W[maxn], a[maxn], pre[maxn];
    double F[maxn], dis[maxn];
    bool vis[maxn];

    inline void INIT() { mem(Begin); e = 1; }

    inline void add(int u, int v, int w, double f) 
    { 
        To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f; 
        To[++ e] = u; From[e] = v; Next[e] = Begin[v]; Begin[v] = e; W[e] = 0; F[e] = -f; 
    }

    inline bool BFS(int s, int t)
    {
        REP(i, 1, t) dis[i] = -INF; mem(vis);
        dis[s] = 0; a[s] = INF; vis[s] = true;
        queue<int> Q; Q.push(s);
        while ( !Q.empty() )
        {
            int u = Q.front(); Q.pop();
            for ( int i = Begin[u]; i; i = Next[i] ) 
            {
                int v = To[i];
                if ( dis[v] < dis[u] + F[i] && W[i] > 0 ) 
                {
                    dis[v] = dis[u] + F[i];
                    a[v] = min(a[u], W[i]);
                    pre[v] = i;
                    if ( !vis[v] ) { vis[v] = true; Q.push(v); }
                }
            }
            vis[u] = false;
        }
        if ( dis[t] == -INF ) return false;
        return true;
    }

    inline bool SPFA(int s, int t, int &flow, double &cost)
    {
        if ( !BFS(s, t) ) return false;
        flow += a[t]; cost += a[t] * dis[t];
        int u = t;
        while ( u != s ) 
        {
            W[pre[u]] -= a[t]; 
            W[pre[u] ^ 1] += a[t];
            u = From[pre[u]];
        }
        return true;
    }

    inline void Solve(int s, int t, int &flow, double &cost) 
    {
        flow = cost = 0;
        while ( SPFA(s, t, flow, cost) ) ;        
    }
}

inline bool Check(double x)
{
    MCMF :: INIT();
    int s = 0, t = n + n + 1, flow; double cost;
    REP(i, 1, n) 
    {
        MCMF :: add(s, i, 1, 0);
        MCMF :: add(n + i, t, 1, 0);
    }
    REP(i, 1, n) REP(j, 1, n) MCMF :: add(i, n + j, 1, a[i][j] - x * b[i][j]);
    MCMF :: Solve(s, t, flow, cost);
    return cost >= 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) REP(j, 1, n) scanf("%d", &a[i][j]);
    REP(i, 1, n) REP(j, 1, n) scanf("%d", &b[i][j]);
    double L = 0, R = 10000;
    REP(i, 1, 100)
    {
        double Mid = (L + R) / 2;
        if ( Check(Mid) ) L = Mid;
        else R = Mid;
    }
    printf("%.6lf\n", L);
    return 0;
}
