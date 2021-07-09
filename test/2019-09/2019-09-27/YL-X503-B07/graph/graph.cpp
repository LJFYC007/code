/***************************************************************
	File name: graph.cpp
	Author: ljfcnyali
	Create time: 2019年09月27日 星期五 21时07分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e;
int dfn[maxn], low[maxn], cnt, ans;
bool f[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ cnt;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == fa || f[i] ) continue ;
        if ( !dfn[v] ) 
        { 
            Tarjan(v, u); 
            if ( low[v] > dfn[u] ) ++ ans;
            low[u] = min(low[u], low[v]); 
        }
        else low[u] = min(low[u], dfn[v]);
    }
}

inline void Solve()
{
    REP(i, 1, n) dfn[i] = low[i] = 0;
    ans = 0;
    Tarjan(1, 0);
    printf("%d\n", ans);
}

int main()
{
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    Solve();
    REP(i, 1, q)
    {
        int opt, u, v; scanf("%d%d%d", &opt, &u, &v);
        if ( opt == 1 ) { add(u, v); add(v, u); }
        else 
        {
            for ( int j = Begin[u]; j; j = Next[j] ) if ( To[j] == v && !f[j] ) { f[j] = true; break ; }
            for ( int j = Begin[v]; j; j = Next[j] ) if ( To[j] == u && !f[j] ) { f[j] = true; break ; }
        }
        Solve();
    }
    return 0;
}
