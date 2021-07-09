/***************************************************************
	File name: ARC062F.cpp
	Author: ljfcnyali
	Create time: 2020年07月26日 星期日 09时29分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, k, Begin[maxn], Next[maxn], To[maxn], e;
int p[maxn], cnt, low[maxn], dfn[maxn], tot, Stack[maxn], top;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ tot; Stack[++ top] = u;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( !dfn[v] ) 
        {
            Tarjan(v, u); low[u] = min(low[u], low[v]);
            if ( low[v] >= dfn[u] ) 
            {
            }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, n) if ( !dfn[i] ) Tarjan(i, 0);
    return 0;
}
