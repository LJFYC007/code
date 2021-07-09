/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2021年01月15日 星期五 15时12分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 0x3f3f3f3f;

int n, Begin[3010], Next[maxn], To[maxn], e = 1, W[maxn], a[3010], b[3010];
int s, t, ans, dis[maxn];
bool vis[3010];

inline void add(int u, int v, int w)
{
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
    swap(u, v); w = 0;
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
}

inline bool BFS()
{
    queue<int> Q; Q.push(s); mem(dis); dis[s] = 1;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( !W[i] || dis[v] ) continue ; 
            dis[v] = dis[u] + 1; Q.push(v);
        }
    }
    return dis[t];
}

inline int DFS(int u, int flow)
{
    if ( !flow || u == t ) return flow;
    int f = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( !W[i] || dis[v] != dis[u] + 1 ) continue ; 
        int x = DFS(v, min(flow, W[i]));
        if ( x ) 
        {
            f += x; flow -= x;
            W[i] -= x; W[i ^ 1] += x;
        }
    }
    dis[u] = 0; return f;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n) scanf("%d", &b[i]);
    t = n + 1; t = n + 2;
    REP(i, 1, n) 
    {
        if ( b[i] > 0 ) { ans += b[i]; add(s, i, b[i]); }
        else add(i, t, -b[i]);
        mem(vis);
        for ( int j = i - 1; j >= 1; -- j ) if ( !vis[a[j]] && a[i] % a[j] == 0 )
        {
            vis[a[j]] = true;
            add(i, j, INF);
        }
    }
    while ( BFS() ) ans -= DFS(s, INF);
    printf("%d\n", ans);
    return 0;
}
