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

int n, Begin[maxn], Next[maxn], To[maxn], e, p[maxn], f[maxn][maxn], anc[maxn];
pii Edge[maxn];
set<int> Set;
map<pii, int> Map;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        anc[v] = u; DFS1(v, u);
    }
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n - 1) { scanf("%d%d", &Edge[i].x, &Edge[i].y); add(Edge[i].x, Edge[i].y); add(Edge[i].y, Edge[i].x); }
    REP(i, 1, n) scanf("%d", &p[i]);

    DFS1(1, 0);
    REP(i, 1, n - 1) 
    {
        if ( anc[Edge[i].x] == Edge[i].y ) swap(Edge[i].x, Edge[i].y);
        Map[Edge[i]] = i;
    }
    REP(i, 1, n) 
    {
        REP(j, 1, n) f[i][j] = -1; f[i][i] = 0;
        int x = i;
        while ( anc[x] ) { f[i][anc[x]] = Map[pii(anc[x], x)]; x = anc[x]; }
    }

    REP(i, 1, n - 1)
        if ( f[p[Edge[i].x]][Edge[i].x] == i && f[p[Edge[i].y]][Edge[i].y] == -1 )
            Set.insert(i);

    while ( !Set.empty() ) 
    {
        int i = *Set.begin(); printf("%d ", i); Set.erase(Set.begin());
        int x = Edge[i].x, y = Edge[i].y; swap(p[x], p[y]);
        int j = f[p[y]][y];
        // cerr << p[y] << " " << y << " " << j  << endl;
        if ( j >= 1 && f[p[Edge[j].x]][Edge[j].x] == j && f[p[Edge[j].y]][Edge[j].y] == -1 )
            Set.insert(j);
        j = f[p[x]][x]; if ( j == -1 ) j = Map[pii(anc[x], x)];
        if ( j >= 1 && f[p[Edge[j].x]][Edge[j].x] == j && f[p[Edge[j].y]][Edge[j].y] == -1 )
            Set.insert(j);
    }
    puts("");
    return 0;
}
