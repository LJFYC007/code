/***************************************************************
	File name: J.cpp
	Author: ljfcnyali
	Create time: 2019年06月26日 星期三 11时08分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 20010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int dis[3][maxn], n, s, t, Max, p;
bool vis[maxn];

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline void DFS(int u, int fa, int x)
{
    vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[v] ) continue ;
        dis[x][v] = dis[x][u] + W[i];
        if ( dis[x][v] > Max ) { Max = dis[x][v]; p = v; }
        DFS(v, fa, x);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%d", &n) )
    {
        mem(Begin); e = 0; mem(dis); s = t = Max = 0;
        REP(i, 2, n) { int u, v; scanf("%d%d", &u, &v); add(i, u, v); add(u, i, v); }
        mem(vis);
        DFS(1, 0, 0); 
        Max = 0; s = p;
        mem(vis);
        DFS(s, s, 1); 
        Max = 0; t = p;
        mem(vis);
        DFS(t, t, 2);
//        printf("%d %d\n", s, t);
        REP(i, 1, n) printf("%d\n", max(dis[1][i], dis[2][i]));
    }
    return 0;
}
