/***************************************************************
	File name: check.cpp
	Author: ljfcnyali
	Create time: 2020年07月13日 星期一 15时46分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e ,dis[maxn], anc[maxn], num[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v] = u; DFS(v, u);
    }
}

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v ==fa ) continue ; 
        DFS1(v, u); num[u] += num[v];
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    REP(i, 1, n) { int u, v; scanf("%d%d", &u ,&v); add(u, v); add(v, u); }
    dis[1] = 1; DFS(1, 0);
    freopen("output.txt", "r", stdin);
    scanf("%d", &m);
    REP(i, 1, m)
    {
        int u, v; scanf("%d%d", &u ,&v);
        ++ num[u]; ++ num[v];
        if ( dis[u] < dis[v] ) swap(u, v);
        while ( dis[u] > dis[v] ) u = anc[u];
        while ( anc[u] != anc[v] ) { u = anc[u]; v = anc[v]; }
        num[anc[u]] -= 2;
    }
    DFS1(1, 0);
    REP(i, 2, n) assert(num[i] > 0);
    return 0;
}
