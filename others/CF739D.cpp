/***************************************************************
	File name: CF739D.cpp
	Author: ljfcnyali
	Create time: 2020年11月09日 星期一 16时54分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define x first
#define y second
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, dis[maxn], num[maxn], f[maxn], h[maxn], Max;
pii a[maxn];

inline int read()
{
    int x = 0; char c = getchar();
    while ( (c < '0' || c > '9') && c != '?' ) c = getchar();
    if ( c == '?' ) return -1;
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
    return x;
}

namespace Dinic
{
    int Begin[maxn], To[maxn], Next[maxn], W[maxn], e, dis[maxn];

    inline void INIT() { mem(Begin); e = 1; }

    inline void add(int u, int v, int w)
    {
        To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
        To[++ e] = u; Next[e] = Begin[v]; Begin[v] = e; W[e] = 0;
    }

    inline bool BFS(int s, int t)
    {
        queue<int> Q; Q.push(s); mem(dis); dis[s] = 1;
        while ( !Q.empty() )
        {
            int u = Q.front(); Q.pop();
            for ( int i = Begin[u]; i; i = Next[i] )
            {
                int v = To[i]; if ( dis[v] || !W[i] ) continue ;
                dis[v] = dis[u] + 1; Q.push(v);
            }
        }
        return dis[t];
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
            flow -= x; f += x; W[i] -= x; W[i ^ 1] += x;
        }
        if ( !f ) dis[u] = 0; return f;
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

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) { int x = read(), y = read(); a[i] = pii(x, y); }
    REP(i, 1, n) 
    {
        if ( a[i].x != -1 && a[i].y != -1 ) dis[a[i].y] = max(dis[a[i].y], a[i].x);        
        if ( a[i].x == -1 && a[i].y != -1 ) ++ num[a[i].y];
        if ( a[i].x == 0 && a[i].y != -1 ) ++ h[a[i].y];
        if ( a[i].x != -1 && a[i].y == -1 ) Max = max(Max, a[i].x);
    }
    REP(i, 1, n) f[i] = (i - (h[i] % i)) % i;

    REP(o, 1, n)
    {
        int X = dis[o]; dis[o] = max(dis[o], Max); 
        int sum = 0; REP(i, 1, n) sum += dis[i]; if ( sum > n ) continue ;
                 
        dis[o] = X;
    }
    puts("-1");
    return 0;
}
