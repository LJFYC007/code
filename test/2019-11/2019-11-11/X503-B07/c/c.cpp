/***************************************************************
	File name: c.cpp
	Author: ljfcnyali
	Create time: 2019年11月11日 星期一 10时22分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2000010;

int T, n, Begin[maxn], Next[maxn], To[maxn], e, f[maxn], g[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    int son = 0; f[u] = g[u] = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        ++ son; DFS(v, u); 
        if ( f[v] == 1 ) f[u] = 1;
        g[u] += g[v];
    }
    if ( !son ) f[u] = g[u] = 1;
    if ( son == 1 && g[u] == 1 ) f[u] ^= 1;
}

int main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d", &n);
        REP(i, 1, n) Begin[i] = 0; e = 0;
        REP(i, 2, n) { int x; scanf("%d", &x); add(x, i); add(i, x); }
        DFS(1, 0);
        printf("%c\n", f[1] == 1 ? 'A' : 'B');
    }
    return 0;
}
