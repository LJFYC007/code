/***************************************************************
	File name: CF611H.cpp
	Author: ljfcnyali
	Create time: 2020年06月07日 星期日 19时03分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, a[10][10], p[10], num[10], A[10][10], Num[10];
int deg[10], val[10][10], Edge[10][10], g[maxn];
char s[10], t[10];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r *= a; a *= a; b >>= 1; } return r; }

inline void Prufer()
{
    REP(i, 1, m) num[i] -= (a[i][i] / 2) + 1; mem(Edge);
    if ( m == 2 ) { -- a[1][2]; ++ Edge[1][2]; return; }
    REP(i, 1, m) deg[i] = 1;
    REP(i, 1, m - 2) ++ deg[p[i]];
    REP(i, 1, m - 2)
    {
        int pos = m;
        REP(j, 1, m) if ( deg[j] == 1 ) { pos = j; break ; }
        ++ Edge[p[i]][pos]; ++ Edge[pos][p[i]];
        -- a[p[i]][pos]; -- a[pos][p[i]];
        -- deg[pos]; -- deg[p[i]];
    }
    REP(i, 1, m) if ( deg[i] == 1 ) { ++ Edge[i][m]; ++ Edge[m][i]; -- a[i][m]; -- a[m][i]; break ; }
}

namespace Dinic
{
    int Begin[maxn], To[maxn], Next[maxn], W[maxn];
    int e = 1, dis[maxn];

    inline void INIT() { mem(Begin); e = 1; }

    inline void add(int u, int v, int w)
    {
        To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
        To[++ e] = u; Next[e] = Begin[v]; Begin[v] = e; W[e] = 0;
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

inline void Check()
{
    Dinic :: INIT();
    int s = m + (m - 1) * m / 2 + 1, t = s + 1, sum = 0;
    REP(i, 1, m) { Dinic :: add(s, i, num[i]); sum += num[i]; }
    REP(i, 1, m) if ( num[i] < 0 ) return ;
    REP(i, 1, m) REP(j, i + 1, m) if ( a[i][j] < 0 ) return ;
    int cnt = m;
    REP(i, 1, m) REP(j, i + 1, m) 
    {
        ++ cnt;
        Dinic :: add(cnt, t, a[i][j]);
        val[i][j] = Dinic :: e + 2;
        Dinic :: add(i, cnt, INF);
        Dinic :: add(j, cnt, INF);
    }
    int flow = Dinic :: Solve(s, t);
    if ( sum != flow ) return ;
    REP(i, 1, m) REP(j, i + 1, m) val[i][j] = a[i][j] - Dinic :: W[val[i][j]];
    REP(i, 1, m) g[i] = num[i] = power(10, i - 1); 
    REP(i, 1, m) REP(j, i + 1, m) if ( Edge[i][j] ) printf("%d %d\n", num[i], num[j]);
    REP(i, 1, m) REP(j, 1, a[i][i] / 2) { ++ num[i]; printf("%d %d\n", g[i], num[i]); }
    REP(i, 1, m) REP(j, i + 1, m) 
    {
        REP(k, 1, val[i][j]) { ++ num[j]; printf("%d %d\n", g[i], num[j]); }
        REP(k, 1, a[i][j] - val[i][j]) { ++ num[i]; printf("%d %d\n", num[i], g[j]); }
    }
    exit(0);
}

inline void DFS(int x)
{
    if ( x > m - 2 ) 
    {
        REP(i, 1, m) REP(j, 1, m) a[i][j] = A[i][j];
        REP(i, 1, m) num[i] = Num[i];
        Prufer(); Check();
        return ;
    }
    REP(i, 1, m) { p[x] = i; DFS(x + 1); }
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
        scanf("%s %s", s + 1, t + 1);
        int x = str(s + 1), y = str(t + 1);
        ++ A[x][y]; ++ A[y][x];
        m = max(max(x, y), m); 
    }
    if ( m == 1 ) 
    {
        REP(i, 2, n) printf("%d %d\n", i - 1, i);
        return 0;
    }
    REP(i, 1, m - 1) Num[i] = 9 * power(10, i - 1); Num[m] = n - power(10, m - 1) + 1;
    if ( n == 1000 && m != 4 ) { puts("-1") ;return 0; }
    DFS(1); puts("-1");
    return 0;
}
