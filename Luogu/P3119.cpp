/***************************************************************
	File name: P3119.cpp
	Author: ljfcnyali
	Create time: 2019年06月08日 星期六 15时59分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;
const int INF = 0x3f3f3f3f;

int Begin[maxn][3], Next[maxn][3], To[maxn][3], e[3];
int dfn[maxn], low[maxn], p[maxn], n, m, cnt, sum, size[maxn];
int dis[maxn][3], s, ans;
bool vis[maxn];
stack<int> Stack;

inline void add(int u, int v, int num)
{
    To[++ e[num]][num] = v;
    Next[e[num]][num] = Begin[u][num];
    Begin[u][num] = e[num];
}

inline void Tarjan(int u)
{
    dfn[u] = low[u] = ++ cnt;
    Stack.push(u);
    for ( int i = Begin[u][0]; i; i = Next[i][0] ) 
    {
        int v = To[i][0]; 
        if ( !dfn[v] ) { Tarjan(v); low[u] = min(low[u], low[v]); }
        else if ( !p[v] ) low[u] = min(low[u], dfn[v]);
    }
    if ( low[u] == dfn[u] ) 
    {
        p[u] = ++ sum; size[sum] = 1;
        while ( Stack.top() != u ) 
        {
            p[Stack.top()] = sum; Stack.pop(); ++ size[sum];
        }
        Stack.pop();
    }
}

inline void Spfa(int num)
{
    queue<int> Q;
    Q.push(s); 
    dis[s][num] = size[s];
    mem(vis);
    while ( !Q.empty() )
    {
        int u = Q.front(); Q.pop();
        vis[u] = false;
        for ( int i = Begin[u][num]; i; i = Next[i][num] )
        {
            int v = To[i][num];
            if ( dis[v][num] < dis[u][num] + size[v] ) 
            {
                dis[v][num] = dis[u][num] + size[v];
                if ( !vis[v] ) 
                {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v, 0); }
    REP(i, 1, n) if ( !dfn[i] ) 
    {
       // while ( !Stack.empty() ) Stack.pop();
        Tarjan(i);
    }
    REP(u, 1, n)
        for ( int i = Begin[u][0]; i; i = Next[i][0] )
        {
            int v = To[i][0];
            if ( p[u] == p[v] ) continue ;
            add(p[u], p[v], 1);
            add(p[v], p[u], 2);
        }
    s = p[1];
    Spfa(1); Spfa(2);
    ans = size[s];
    REP(u, 1, sum)
        for ( int i = Begin[u][2]; i; i = Next[i][2] )
        {
            int v = To[i][2];
            if ( dis[u][1] == INF || dis[v][2] == INF ) continue ;
            if ( dis[u][1] == 0 || dis[v][2] == 0 ) continue ;
            ans = max(ans, dis[u][1] + dis[v][2] - size[s]);
        }
    printf("%d\n", ans);
    return 0;
}
