/***************************************************************
	File name: P4311.cpp
	Author: ljfcnyali
	Create time: 2019年08月30日 星期五 15时58分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;
const int INF = 0x3f3f3f3f;

int n, m, k, s, t;
int Begin[maxn], Next[maxn], To[maxn], e = 1, W[maxn], dis[maxn];
bool a[110][110];

inline void add(int u, int v, int w) 
{
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
    To[++ e] = u; Next[e] = Begin[v]; Begin[v] = e; W[e] = 0;
}

inline bool BFS(int s, int t)
{
    mem(dis); dis[s] = 1;
    queue<int> Q; Q.push(s);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( dis[v] || !W[i] ) continue ;
            dis[v] = dis[u] + 1;
            Q.push(v);
        }
    }
    if ( dis[t] ) return true;
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

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k);
    t = n + m + 1;
    REP(i, 1, n) { int x; scanf("%d", &x); add(s, i, x); }
    REP(i, 1, m) { int x; scanf("%d", &x); add(n + i, t, x); }
    REP(i, 1, k) { int x, y; scanf("%d%d", &x, &y); a[x][y] = true; }
    REP(i, 1, n) REP(j, 1, m) if ( !a[i][j] ) add(i, n + j, 1);
    int ans = 0;
    while ( BFS(s, t) ) while ( int flow = DFS(s, t, INF) ) ans += flow;
    printf("%d\n", ans);
    return 0;
}
