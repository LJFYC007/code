/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2020年11月30日 星期一 08时20分02秒
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

const int maxn = 2010;

int n, Begin[maxn], Next[maxn], To[maxn], e, p[maxn], dis[maxn];
pii Edge[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; DFS(v, u);
    }
}

inline int Dis(int x, int y)
{
    dis[x] = 0; DFS(x, 0);
    return dis[y];
}

inline int Solve()
{
    int sum = 0;
    REP(i, 1, n) sum += Dis(i, p[i]);
    return sum;
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n - 1) { scanf("%d%d", &Edge[i].x, &Edge[i].y); add(Edge[i].x, Edge[i].y); add(Edge[i].y, Edge[i].x); }
    REP(i, 1, n) scanf("%d", &p[i]);
    int now = Solve();
    while ( 1 ) 
    {
        REP(i, 1, n - 1)
        {
            swap(p[Edge[i].x], p[Edge[i].y]);
            if ( Solve() == now - 2 ) { now -= 2; printf("%d ", i); goto Next ; }
            swap(p[Edge[i].x], p[Edge[i].y]);
        }
        puts(""); return 0;
Next : ;
    }
    return 0;
}
