/***************************************************************
	File name: travel.cpp
	Author: ljfcnyali
	Create time: 2019年08月05日 星期一 10时25分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1010;
const int maxm = 6510;
const int INF = 0x3f3f3f3f;

int Begin[maxm], Next[maxm], To[maxm], e, in[maxn], out[maxn];
int T, type, n, m, num;
bool vis[maxn];

struct node
{
    int u, v;
} a[maxm];

inline void Add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

namespace Dinic
{
    int Begin[maxn], To[maxn], Next[maxn], W[maxn];
    int e, dis[maxn];

    inline void INIT()
    {
        mem(Begin); e = 1;
    }

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

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( !vis[v] ) { vis[v] = true; DFS(v); }
    }
}

int main()
{
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    scanf("%d%d", &T, &type);
    while ( T -- ) 
    {
        mem(Begin); e = num = 0; mem(in); mem(out); mem(vis);
        scanf("%d%d", &n, &m);
        Dinic :: INIT();
        REP(i, 1, m)
        {
            int u, v; char c; scanf("%d%d %c", &u, &v, &c);
            Add(u, v); ++ out[u]; ++ in[v]; 
            if ( c == 'U' ) Dinic :: add(u, v, 1);
            // if ( c == 'U' ) a[++ num].u = u, a[num].v = v;
        }
        vis[1] = true; DFS(1);
        bool flag = true;
        REP(i, 1, n) if ( !vis[i] && (in[i] || out[i]) ) { puts("NO"); flag = false; break ; }
        if ( flag == false ) continue ;
        REP(i, 1, n) if ( out[i] != in[i] ) { flag = false; break ; }
        if ( flag == true ) { puts("YES"); continue ; }
        flag = true; 
        REP(i, 1, n) if ( (abs(out[i] - in[i])) % 2 == 1 ) { puts("NO"); flag = false; break ; }
        if ( flag == false ) continue ;
        int sum1 = 0, sum2 = 0, s = 0, t = n + 1;
        // REP(i, 1, n) cerr << out[i] << " " << in[i] << endl;
        REP(i, 1, n) 
        {
            if ( out[i] > in[i] ) { Dinic :: add(s, i, (out[i] - in[i]) / 2); sum1 += (out[i] - in[i]) / 2; }
            if ( in[i] > out[i] ) { Dinic :: add(i, t, (in[i] - out[i]) / 2); sum2 += (in[i] - out[i]) / 2; }
        }
        int sum = min(sum1, sum2);
        if ( sum == Dinic :: Solve(s, t) ) puts("YES"); else puts("NO");
    }
    return 0;
}
