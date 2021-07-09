/***************************************************************
	File name: budget.cpp
	Author: ljfcnyali
	Create time: 2020年05月21日 星期四 15时19分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e3 + 10;
const int INF = 1e9;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, val[maxn];
bool vis[maxn];
map<LL, int> Map[41];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int Get(int u, LL &s)
{
    int sum = 0;
    if ( !((s >> u) & 1) ) { s |= 1ll << u; sum += val[u]; }
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( (s >> v) & 1 ) continue ;
        s |= 1ll << v; sum += val[v]; 
    }
    return sum;
}

inline int DFS(int u, LL s)
{
    int Min = INF;
    if ( Map[u].count(s) ) return Map[u][s];
    if ( u == n ) { Map[u][s] = 0; return 0; }
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[v] ) continue ;
        LL x = s; int num = Get(v, x);
        vis[v] = true; Min = min(Min, num + DFS(v, x)); vis[v] = false;
    }
    Map[u][s] = Min; return Min;
}

int main()
{
    freopen("budget.in", "r", stdin);
    freopen("budget.out", "w", stdout);
    while ( ~scanf("%d%d", &n, &m) )
    {
        mem(vis); mem(Begin); e = 0;
        REP(i, 1, n) Map[i].clear();
        REP(i, 1, n) scanf("%d", &val[i]); 
        REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
        vis[1] = true; 
        LL s = 0; int sum = Get(1, s);
        printf("%d\n", sum + DFS(1, s));
    }
    return 0;
}
