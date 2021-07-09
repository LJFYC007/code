/***************************************************************
	File name: P2740.cpp
	Author: ljfcnyali
	Create time: 2019年07月15日 星期一 10时19分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), -1, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 410;
const int INF = 0x3f3f3f3f;

int Begin[maxn], Next[maxn], To[maxn], e = -1, W[maxn];
int n, m, ans, dis[maxn];
queue<int> Q;

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline bool BFS(int s, int t)
{
    mem(dis); dis[s] = 1;
    while ( !Q.empty() ) Q.pop();
    Q.push(s);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        if ( u == t ) return true;
        for ( int i = Begin[u]; ~i; i = Next[i] )
        {
            int v = To[i]; 
            if ( dis[v] == -1 && W[i] > 0 ) 
            {
                dis[v] = dis[u] + 1;
                Q.push(v);
            }
        }
    }
    if ( dis[t] == -1 ) return false;
    return true;
}

inline int DFS(int u, int t, int Min)
{
    if ( u == t ) return Min;
    int x;
    for ( int i = Begin[u]; ~i; i = Next[i] ) 
    {
        int v = To[i];
        if ( dis[v] == dis[u] + 1 && W[i] != 0 )
        {
            x = DFS(v, t, min(Min, W[i]));
            if ( x > 0 ) 
            {
                W[i] -= x; W[i ^ 1] += x; return x;
            }    
        }
    }
    return 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &m, &n);
    mem(Begin);
    REP(i, 1, m)
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, 0);
    }
    while ( BFS(1, n) )
        while ( int flow = DFS(1, n, INF) )
            ans += flow;
    printf("%d\n", ans);
    return 0;
}
