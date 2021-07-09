/***************************************************************
	File name: P4126.cpp
	Author: ljfcnyali
	Create time: 2019年07月15日 星期一 14时36分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;
const int INF = 0x3f3f3f3f;

int Begin[maxn], Next[maxn], To[maxn], e = 1, W[maxn], num;
int dis[maxn], n, m, s, t, low[maxn], dfn[maxn], cnt, p[maxn];
stack<int> Stack;

struct node
{
    int u, v;
} a[maxn];

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
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
            dis[v] = dis[u] + 1; 
            Q.push(v);
            if ( v == t ) return true;
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
        W[i] -= x; W[i ^ 1] += x;
        flow -= x; f += x;
        if ( !flow ) break ;
    }
    if ( !f ) dis[u] = 0;
    return f;
}

inline void Tarjan(int u)
{
    dfn[u] = low[u] = ++ cnt; 
    Stack.push(u);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        if ( !W[i] ) continue ;
        int v = To[i];
        if ( !dfn[v] ) { Tarjan(v); low[u] = min(low[u], low[v]); }
        else if ( !p[v] ) low[u] = min(low[u], dfn[v]);
    }
    if ( dfn[u] == low[u] ) 
    {
        p[u] = ++ num;
        while ( Stack.top() != u ) { p[Stack.top()] = num; Stack.pop(); }
        Stack.pop();
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &s, &t);
    REP(i, 1, m) 
    { 
        int u, v, w; scanf("%d%d%d", &u, &v, &w); 
        add(u, v, w); add(v, u, 0); 
        a[i].u = u; a[i].v = v;
    }
    while ( BFS(s, t) )
        while ( DFS(s, t, INF) ) ;
    REP(i, 1, n) if ( !p[i] ) Tarjan(i);
    REP(i, 1, m)
    {
        if ( p[a[i].u] == p[a[i].v] || W[2 * i] ) { printf("0 0\n"); continue ; }
        printf("1 ");
        if ( p[a[i].u] == p[s] && p[a[i].v] == p[t] ) puts("1");
        else puts("0");
    }
    return 0;
}
