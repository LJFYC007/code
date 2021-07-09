/***************************************************************
	File name: Fastset.cpp
	Author: ljfcnyali
	Create time: 2019年10月30日 星期三 08时22分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 600010;

int n, Begin[maxn], Next[maxn], To[maxn], e, dis[300010], anc[300010][20];
LL ans;
struct node 
{ 
    int l, r, pos; 
    node ( int L = 0, int R = 0, int Pos = 0 ) { l = L; r = R; pos = Pos; }
    bool operator < (const node &a) const { return l < a.l; } 
} ;
set<node> Set;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u;
        DFS(v, u);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 19; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 19; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

inline LL Dis(int x, int y) { return dis[x] + dis[y] - 2 * dis[LCA(x, y)]; }

inline decltype(Set.lower_bound(node(0,0,0))) Split(int x)
{
    auto it = -- Set.upper_bound(node(x, 0, 0));
    if ( it -> l == x ) return it;
    int l = it -> l, r = it -> r, p = it -> pos;
    Set.erase(it);
    Set.insert(node(l, x - 1, p));
    Set.insert(node(x, r, p));
    return Set.lower_bound(node(x, 0, 0));
}

inline void assign(int l, int r, int p)
{
    auto itr = Split(r + 1), itl = Split(l);
    Set.erase(itl, itr);
    Set.insert(node(l, r, p));
}

int main()
{
    freopen("Fastset.in", "r", stdin);
    freopen("Fastset.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS(1, 0);
    REP(j, 1, 19) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, n) Set.insert(node(i, i, i));
    REP(i, 1, n)
    {
        int l, r, p; scanf("%d%d%d", &l, &r, &p);
        auto itr = Split(r + 1), itl = Split(l);
        for ( ; itl != itr; ++ itl ) ans += (itl -> r - itl -> l + 1) * Dis(itl -> pos, p);
        assign(l, r, p);
    }
    printf("%lld\n", ans);
    return 0;
}
