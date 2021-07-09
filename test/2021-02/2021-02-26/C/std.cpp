
#include<bits/stdc++.h>
  
using namespace std;
  
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
  
const int maxn = 5010;
const int maxm = 2e6 + 10;
const int INF = 0x3f3f3f3f;
  
int a[maxn][maxn], n, id[maxn][maxn];
int Begin[maxm], To[maxm], Next[maxm], W[maxm], e = 1, dis[maxm];
  
inline void add(int u, int v, int w)
{
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
    swap(u, v); w = 0;
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
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
namespace Subtask
{
    inline int main()
    {
        int s = n * n + 1, t = n * n + 2, m = 0;
        REP(i, 1, n) REP(j, 1, i + i - 1) 
        {
            id[i][j] = ++ m; 
            if ( j & 1 ) add(s, m, 1); else add(m, t, 1);
        }
        REP(i, 1, n) REP(j, 1, i) if ( a[i][j] ) 
        {
            int x = j + j - 1;
            if ( j != 1 ) add(id[i][x], id[i][x - 1], 1);
            if ( j != i ) add(id[i][x], id[i][x + 1], 1);
            if ( i != n ) add(id[i][x], id[i + 1][x + 1], 1);
        }
        int flow = Solve(s, t);
        if ( flow != n * (n - 1) / 2 ) { puts("Impossible!"); return 0; }
		puts("Yes"); return 0;
        REP(i, 1, n) 
        {
            REP(j, 1, i)
            {
                if ( a[i][j] == 0 ) { printf("-"); continue ; }
                int u = id[i][j + j - 1], x = j + j - 1;
                for ( int o = Begin[u]; o; o = Next[o] ) 
                {
                    int v = To[o]; if ( v == s || W[o] ) continue ; 
                    if ( v == id[i][x - 1] ) printf("1");
                    else if ( v == id[i + 1][x + 1] ) printf("2");
                    else printf("3");
                }
            }
            puts("");
        }
        return 0;
    }
}
  
int main()
{
#ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output1.txt", "w", stdout);
#endif
    scanf("%d", &n);
    bool flag = true;
    REP(i, 1, n) 
    {
        bool tmp = false;   
        REP(j, 1, i) { scanf("%1d", &a[i][j]); if ( a[i][j] == 0 ) tmp = true; } 
        if ( !tmp ) flag = false;
    }
    if ( n <= 500 ) return Subtask :: main();
        if ( flag ) 
        {
                REP(i, 1, n)
                {
                        bool flag = false;
                        REP(j, 1, i)
                        {
                                if ( a[i][j] == 0 ) { flag = true; printf("-"); }
                                else if ( !flag ) printf("3"); 
                                else printf("1");
                        }
                        puts("");
                }
        }
        else puts("Impossible!");
        return 0;
}
