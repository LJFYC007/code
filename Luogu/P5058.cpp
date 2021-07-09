/***************************************************************
	File name: P5058.cpp
	Author: ljfcnyali
	Create time: 2019年07月01日 星期一 18时57分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10010;

int Begin[maxn], Next[maxn], To[maxn], e;
int low[maxn], dfn[maxn], n, s, t, cnt;
bool cut[maxn], vis[maxn];

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void Tarjan(int u)
{
    low[u] = dfn[u] = ++ cnt;
    int son = 0;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i];
        if ( !low[v] ) 
        { 
            Tarjan(v); 
            low[u] = min(low[u], low[v]); 
            if ( low[v] >= dfn[u] && u != s ) cut[u] = true;
            ++ son;
        }
        else low[u] = min(low[u], dfn[v]);
    }
    if ( u == s && son > 1 ) cut[u] = true;
}

inline bool BFS(int x)
{
    queue<int> Q; Q.push(s);
    vis[s] = vis[x] = true;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        if ( u == t ) return false;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; 
            if ( vis[v] ) continue ;
            vis[v] = true;
            Q.push(v);
        }
    }
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    int u, v;
    while ( ~scanf("%d%d", &u, &v) && u + v ) 
    {
        add(u, v); add(v, u);
    }
    scanf("%d%d", &s, &t);
    Tarjan(s);
    REP(i, 1, n) if ( cut[i] ) { mem(vis); if ( BFS(i) ) { printf("%d\n", i); return 0; } }
    printf("No solution\n");
    return 0;
}
