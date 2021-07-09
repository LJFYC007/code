/***************************************************************
	File name: P6113.cpp
	Author: ljfcnyali
	Create time: 2020年05月04日 星期一 14时11分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, dfn[maxn], cnt;
int f[maxn], mat[maxn], Match[maxn], pre[maxn], ans, id[maxn];
queue<int> Q;

inline void add(int u, int v) 
{ 
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; 
    swap(u, v);
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; 
}

inline int Get(int x) { return x == f[x] ? x : f[x] = Get(f[x]); }

inline void Access(int x) { while ( x ) { int y = mat[pre[x]]; mat[x] = pre[x]; mat[pre[x]] = x; x = y; } }

inline int LCA(int x, int y)
{
    ++ cnt;
    while ( 1 )  
    {
        if ( dfn[x] == cnt ) return x;
        dfn[x] = cnt; x = Get(pre[mat[x]]);
        if ( y ) swap(x, y);
    }
    return 0;
}

inline void Link(int u, int v, int x)
{
    while ( Get(u) != x ) 
    {
        pre[u] = v; v = mat[u];
        if ( f[Get(u)] == u ) f[Get(u)] = x;
        if ( f[Get(v)] == v ) f[Get(v)] = x;
        if ( Match[v] == 2 ) { Match[v] = 1; Q.push(v); }
        u = pre[v];
    }
}

inline int BFS(int s)
{
    // 0 -> unvisited; 1 -> black; 2 -> white
    REP(i, 1, n + m * 7) { f[i] = i; Match[i] = pre[i] = 0; }
    while ( !Q.empty() ) Q.pop();
    Q.push(s); Match[s] = 1;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; 
            if ( Get(u) == Get(v) ) continue ;
            if ( Match[v] == 0 ) 
            {
                Match[v] = 2; pre[v] = u;
                if ( !mat[v] ) { Access(v); return 1; }
                Match[mat[v]] = 1; Q.push(mat[v]); 
            }
            else if ( Match[v] == 1 ) 
            {
                int x = LCA(u, v);
                Link(u, v, x); Link(v, u, x);
            }
        }
    }
    return 0;
}

int main()
{
    freopen("fortress.in", "r", stdin);
    freopen("fortress.out", "w", stdout);
    int T; scanf("%d", &T);
    while ( T -- ) 
    {
        e = cnt = ans = 0; mem(mat); mem(Begin); mem(dfn);
        scanf("%d%d", &n, &m);
        REP(i, 1, m) 
        {
            id[i] = n + (i - 1) * 7;
            add(id[i] + 1, id[i] + 2);
            add(id[i] + 2, id[i] + 3);
            add(id[i] + 3, id[i] + 4);
            add(id[i] + 4, id[i] + 5);
            add(id[i] + 5, id[i] + 1);
        
            add(id[i] + 1, id[i] + 6);
            add(id[i] + 2, id[i] + 6);
            add(id[i] + 3, id[i] + 6);
            add(id[i] + 4, id[i] + 6);
            add(id[i] + 5, id[i] + 6);

            add(id[i] + 1, id[i] + 7);
            add(id[i] + 2, id[i] + 7);
            add(id[i] + 3, id[i] + 7);
            add(id[i] + 4, id[i] + 7);
            add(id[i] + 5, id[i] + 7);
        }
        REP(i, 1, n)
        {
            int k; scanf("%d", &k);
            REP(j, 1, k)
            {
                int x; scanf("%d", &x);
                REP(o, id[x] + 1, id[x] + 5) add(i, o);
            }
        }
        REP(i, 1, n + m * 7) if ( !mat[i] ) ans += BFS(i);
        ans -= n;
        printf("%d\n", ans);
    }
    return 0;
}
