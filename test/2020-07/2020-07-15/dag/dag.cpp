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
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e, deg[maxn], a[maxn], w[maxn], t[maxn], tag[maxn], T[maxn], id[maxn];
int Min[390][maxn];
bitset<390> Set[maxn];
struct node { int op, u, x; } Q[maxn];

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
    freopen("dag.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); }
    toposort();  
    int block = 400;
        //sqrt(n);
    REP(i, 1, q)
    {
        scanf("%d", &Q[i].op);
        if ( Q[i].op <= 2 ) scanf("%d%d", &Q[i].u, &Q[i].x);
        else scanf("%d", &Q[i].x);
    }
    memset(Min, 0x3f, sizeof(Min));
    for ( int l = 1, r = min(q, block); l <= q; l += block, r = min(q, r + block) )
    {
        REP(i, 1, n) { Set[i].reset(); id[i] = T[i] = 0; tag[i] = -1; }
        int tot = 0;
        REP(i, l, r) if ( Q[i].op == 3 && !id[Q[i].x] ) id[Q[i].x] = ++ tot; 

        for ( int i = n; i >= 1; -- i ) 
        {
            int u = a[i]; if ( id[u] ) Set[u][id[u]] = 1;
            for ( int j = Begin[u]; j; j = Next[j] ) Set[u] |= Set[To[j]];
        }

        REP(i, l, r)
        {
            if ( Q[i].op <= 2 ) continue ;
            int ans = w[Q[i].x], Time = t[Q[i].x];
            REP(j, l, i) if ( Q[j].op == 1 && Set[Q[j].u][id[Q[i].x]] ) { ans = Q[j].x; Time = j; }

            int posl = (Time - 1) / block + 1, posr = (i - 1) / block + 1;
            if ( posl == posr ) 
            {
                REP(j, Time, i) if ( Q[j].op == 2 && Set[Q[j].u][id[Q[i].x]] ) ans = min(ans, Q[j].x);
                printf("%d\n", ans);
                continue ;
            }

            REP(j, l, i) if ( Q[j].op == 2 && Set[Q[j].u][id[Q[i].x]] ) ans = min(ans, Q[j].x);
            REP(j, Time, posl * block) if ( Q[j].op == 2 && Set[Q[j].u][id[Q[i].x]] ) ans = min(ans, Q[j].x);
            REP(j, posl + 1, posr - 1) ans = min(ans, Min[j][Q[i].x]);
            printf("%d\n", ans);
        }

        REP(i, l, r) if ( Q[i].op == 1 ) { tag[Q[i].u] = Q[i].x; T[Q[i].u] = i; }
        REP(i, 1, n)
        {
            int u = a[i];
            if ( tag[u] != -1 ) { w[u] = tag[u]; t[u] = T[u]; }

            for ( int j = Begin[u]; j; j = Next[j] ) 
            {
                int v = To[j];
                if ( T[v] < T[u] ) { tag[v] = tag[u]; T[v] = T[u]; }
            }
        }

        int pos = (l - 1) / block + 1;
        REP(i, l, r) if ( Q[i].op == 2 ) Min[pos][Q[i].u] = min(Min[pos][Q[i].u], Q[i].x);
        REP(i, 1, n)
        {
            int u = a[i];
            for ( int j = Begin[u]; j; j = Next[j] ) Min[pos][To[j]] = min(Min[pos][To[j]], Min[pos][u]);
        }
    }
    return 0;
}
