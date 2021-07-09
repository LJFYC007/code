/***************************************************************
	File name: Slowset.cpp
	Author: ljfcnyali
	Create time: 2019年10月30日 星期三 09时02分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, f[maxn], g[maxn], ans;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        g[u] += f[v]; DFS(v, u);
    }
}

int main()
{
    freopen("Slowset.in", "r", stdin);
    freopen("Slowset1.out", "w", stdout);
    scanf("%d%d", &n, &m);    
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, n) f[i] = 1;
    REP(i, 1, m)
    {
        int x; scanf("%d", &x);
        mem(g);
        g[x] = f[x]; DFS(x, 0);
        REP(j, 1, n) if ( g[j] ) f[j] = 1; else f[j] = 0;
    }
    REP(i, 1, n) if ( f[i] ) ++ ans;
    printf("%d\n", ans);
    return 0;
}
