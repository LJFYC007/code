/***************************************************************
	File name: group.cpp
	Author: ljfcnyali
	Create time: 2020年08月08日 星期六 09时35分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, a[maxn], b[maxn], p[maxn], f[maxn], e, Begin[maxn], Next[maxn], To[maxn], W[maxn], deg[maxn];
int ans[maxn], dis[1510];

inline void INIT() { e = 1; mem(Begin); mem(deg); }

inline void add(int u, int v, int w)
{
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
    swap(u, v); 
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = 0;
}

inline void add(int u, int v, int l, int r) 
{ 
    deg[v] += l; deg[u] -= l; add(u, v, r - l); 
}

inline void Insert(int x, int y)
{
    if ( y <= 2 ) 
    { 
        add(x, 2 * n + y, f[y], f[y]); 
        add(2 * n + y + 3, n + x, f[y], f[y]); 
        ans[y] = e;
        add(4 * n + 4, 4 * n + y, f[y], f[y]);
        add(4 * n + 3, 4 * n + 5, f[y], f[y]);
    }
    else { add(x, 2 * n + y, 0, 1); add(2 * n + y + 3, n + x, 0, 1); ans[y] = e; }
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

inline bool Check(int S, int T, int s, int t) 
{
    int sum = 0;
    REP(i, 1, T)  
    {
        if ( deg[i] > 0 ) { add(s, i, deg[i]); sum += deg[i]; }
        else add(i, t, -deg[i]);
    } 
    if ( Solve(s, t) == sum ) return true; 
    return false;
}

inline void print()
{
    REP(i, 1, 2 * n) printf("%d", f[i] + W[ans[i]] + 1); puts("");
}

inline void DFS(int x, int sum)
{
    if ( sum > n ) return ;
    if ( x >= 3 && (f[x - 3] + f[x - 2] + f[x - 1] == 0 || f[x - 3] + f[x - 2] + f[x - 1] == 3) ) return ;
    if ( x == 2 * n + 1 ) 
    {
        if ( sum == n ) 
        {
            if ( f[2 * n] + f[2 * n - 1] + f[1] == 0 || f[2 * n] + f[2 * n - 1] + f[1] == 3 ) return ;
            if ( f[2 * n] + f[2] + f[1] == 0 || f[2 * n] + f[2] + f[1] == 3 ) return ;
            REP(i, 1, 2 * n) printf("%d", f[i] + 1); puts(""); 
            exit(0);
        }
        return ;
    }
    f[x] = 0; if ( (p[x] < x && f[x] != f[p[x]]) || p[x] > x ) DFS(x + 1, sum);
    f[x] = 1; if ( (p[x] < x && f[x] != f[p[x]]) || p[x] > x ) DFS(x + 1, sum + 1);
}

int main()
{
    freopen("group.in", "r", stdin);
    freopen("group.out", "w", stdout);
    scanf("%d", &n);    
    REP(i, 1, n) { scanf("%d%d", &a[i], &b[i]); ++ a[i]; ++ b[i]; p[a[i]] = b[i]; p[b[i]] = a[i]; }
    DFS(1, 0);
    /*
    REP(a1, 0, 1) REP(a2, 0, 1) 
    {
        f[1] = a1; f[2] = a2; INIT();
        int S = 4 * n + 4, T = S + 1, s = T + 1, t = s + 1;
        REP(i, 1, n) { add(S, i, 1, 1); add(n + i, T, 1, 1); }
        REP(i, 1, n) { Insert(i, a[i]); Insert(i, b[i]); }
        add(2 * n + 1, 2 * n + 2, 0, 3);
        add(2 * n + 2, 2 * n + 3, 0, 3);
        REP(i, 2 * n + 3, 4 * n + 2) add(i, i + 1, 1, 2);
        int num = n + a1 + a2;
        add(T, S, num, num);
        if ( Check(S, T, s, t) ) { print(); return 0; }
    }
    */
    puts("Impossible");
    return 0;
}
