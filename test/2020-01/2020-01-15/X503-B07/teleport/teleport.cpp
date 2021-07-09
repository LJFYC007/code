/***************************************************************
	File name: teleport.cpp
	Author: ljfcnyali
	Create time: 2020年01月15日 星期三 10时32分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, T, type, l[maxn], r[maxn], ans, Begin[maxn << 1], Next[maxn << 1], To[maxn << 1], e, W[maxn << 1];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        l[u] = max(l[u], l[v] - W[i]);
        r[u] = min(r[u], r[v] + W[i]);
    }
    ans = max(ans, l[u] - r[u]);
}

int main()
{
    freopen("teleport.in", "r", stdin);
    freopen("teleport.out", "w", stdout);
    scanf("%d%d", &T, &type);
    while ( T -- ) 
    {
        e = 0; mem(Begin);
        scanf("%d", &n); ans = 0;
        REP(i, 1, n) scanf("%d", &l[i]);        
        REP(i, 1, n) scanf("%d", &r[i]);        
        REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
        DFS(1, 0);
        if ( type == 0 ) { if ( ans == 0 ) puts("0"); else puts("1"); }
        else printf("%d\n", (ans + 1) / 2);
    }
    return 0;
}
