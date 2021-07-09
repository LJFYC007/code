/***************************************************************
	File name: dag.cpp
	Author: ljfcnyali
	Create time: 2020年07月15日 星期三 10时13分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e4 + 10;
const int maxm = 1e5 + 10;

int n, m, q, Begin[maxm], Next[maxm], To[maxm], e, deg[maxm], a[maxm], w[maxm];
bitset<maxn> Set[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[v]; }

inline void toposort()
{
    queue<int> Q; 
    REP(i, 1, n) if ( !deg[i] ) Q.push(i);
    int tot = 0;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        a[++ tot] = u;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; -- deg[v];
            if ( !deg[v] ) Q.push(v);
        }
    }
}

int main()
{
    freopen("dag.in", "r", stdin);
    freopen("dag1.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); }
    toposort();  
    for ( int i = n; i >= 1; -- i ) 
    {
        int u = a[i]; Set[u][u] = 1;
        for ( int j = Begin[u]; j; j = Next[j] ) Set[u] |= Set[To[j]];
    }
    REP(i, 1, q)
    {
        int op, u, x; scanf("%d", &op);
        if ( op == 1 ) 
        {
            scanf("%d%d", &u, &x);
            for ( int j = Set[u]._Find_first(); j <= n; j = Set[u]._Find_next(j) )
                w[j] = x;
        }
        else if ( op == 2 ) 
        {
            scanf("%d%d", &u, &x);
            for ( int j = Set[u]._Find_first(); j <= n; j = Set[u]._Find_next(j) )
                w[j] = min(w[j], x);
        }
        else
        {
            scanf("%d", &x);
            // printf("%d\n", w[x]);
        }
        if ( i == 118 ) { REP(j, 1, n) printf("%d ", w[j]); puts(""); }
    }
    return 0;
}
