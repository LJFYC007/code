/***************************************************************
	File name: P2472.cpp
	Author: ljfcnyali
	Create time: 2019年07月15日 星期一 15时26分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 20010;
const int maxm = 30;
const int INF = 0x3f3f3f3f;

int Begin[maxn], Next[maxn], To[maxn], e = 1, W[maxn];
int n, m, d, a[maxm][maxm], p[maxm][maxm][2], cnt, s, t;
int dis[maxn], ans;

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

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &d);
    int t = n * m * 2 + 1;
    REP(i, 1, n)
    {
        getchar(); getchar();
        REP(j, 1, m)
        {
            char c = getchar();
            a[i][j] = c - '0';
            p[i][j][0] = ++ cnt; p[i][j][1] = ++ cnt;
            if ( a[i][j] ) 
            { 
                add(cnt - 1, cnt, a[i][j]); 
                add(cnt, cnt - 1, 0); 
                if ( i <= d || j <= d || i + d > n || j + d > m ) 
                {
                    add(cnt, t, INF);
                    add(t, cnt, 0);
                }
            }
        }
    }
    REP(i, 1, n) 
        REP(j, 1, m)
            REP(k, 1, n)
                REP(o, 1, m)
                    if ( (k - i) * (k - i) + (o - j) * (o - j) <= d * d && (i != k || j != o) && a[i][j] && a[k][o] )
                    {
                        add(p[i][j][1], p[k][o][0], INF);
                        add(p[k][o][0], p[i][j][1], 0);
                    }
    REP(i, 1, n) 
    {
        getchar(); getchar();
        REP(j, 1, m)
        {
            char c = getchar();
            if ( c == 'L' ) { add(s, p[i][j][0], 1); add(p[i][j][0], s, 0); ++ ans; }
        }
    }
    while ( BFS(s, t) )
        while ( int flow = DFS(s, t, INF) )
            ans -= flow;
    printf("%d\n", ans); 
    return 0;
}
