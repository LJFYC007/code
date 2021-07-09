/***************************************************************
	File name: moment.cpp
	Author: ljfcnyali
	Create time: 2019年11月01日 星期五 09时32分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 200010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, type, opt;
int c[maxn], a[maxn], last, p[maxn], d[maxn], f[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

namespace Subtask1
{
    inline void DFS(int u, int k)
    {
        if ( c[u] != -1 ) { a[u] = c[u]; return ; }
        int ret1 = 0, ret2 = 0;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; DFS(v, k);
            if ( a[v] == 0 ) ++ ret1; else ++ ret2;
        }
        if ( ret2 - ret1 >= k ) a[u] = 1; else a[u] = 0;
    }

    inline int main()
    {
        while ( m -- ) 
        {
            int opt, x, y; scanf("%d%d%d", &opt, &x, &y);
            if ( type ) x ^= last;
            if ( opt == 2 ) { c[x] = y; continue ; }
            DFS(x, y);
            if ( a[x] == 1 ) last = x;
            printf("%d\n", a[x]);
        }
        return 0;
    }
}

inline void toposort()
{
    queue<int> Q;
    REP(i, 1, n) if ( !d[i] ) Q.push(i);
    int j = 0;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop(); d[++ j] = u;
        -- d[f[u]]; if ( !d[f[u]] ) Q.push(f[u]);
    }
}

int main()
{
    freopen("moment.in", "r", stdin);
    freopen("moment.out", "w", stdout);
    scanf("%d%d%d%d", &opt, &n, &m, &type);
    REP(i, 2, n) { scanf("%d", &f[i]); add(f[i], i); ++ d[f[i]]; }
    REP(i, 1, n) scanf("%d", &c[i]);
    if ( opt == 3 ) return 0;
    return Subtask1 :: main();
}
