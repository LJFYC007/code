/***************************************************************
	File name: P4074.cpp
	Author: ljfcnyali
	Create time: 2019年10月23日 星期三 15时19分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 200010;

int n, m, q, V[maxn], W[maxn], Color[maxn], tot1, tot2, C[maxn], Block;
int Begin[maxn], Next[maxn], To[maxn], e, pos[maxn], sum[maxn], num;
int f[maxn], g[maxn], anc[maxn][20], dis[maxn], ans[maxn], cnt, id[maxn];
bool vis[maxn];

struct node1 
{ 
    int l, r, t, id; 
    bool operator < (const node1 x) const 
    {
        return pos[l] < pos[x.l] || (pos[l] == pos[x.l] && (pos[r] < pos[x.r] || (pos[r] == pos[x.r] && t < x.t)));
    }
} a[maxn];
struct node2 { int pos, last, now; } b[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    f[u] = ++ cnt; id[cnt] = u;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u;
        DFS(v, u);
    }
    g[u] = ++ cnt; id[cnt] = u;
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 17; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 17; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

inline void add(int x)
{
    if ( !vis[x] ) { ++ sum[Color[x]]; num += V[Color[x]] * W[sum[Color[x]]]; }
    else { num -= V[Color[x]] * W[sum[Color[x]]]; -- sum[Color[x]]; }
    vis[x] ^= 1;
}

inline void Modify(int pos, int val)
{
    if ( vis[pos] ) { add(pos); Color[pos] = val; add(pos); }
    else Color[pos] = val;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &q);
    REP(i, 1, m) scanf("%lld", &V[i]);
    REP(i, 1, n) scanf("%lld", &W[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, n) { scanf("%lld", &Color[i]); C[i] = Color[i]; }
    dis[1] = 1; DFS(1, 0);
    REP(j, 1, 17) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    Block = pow(n, 2.0 / 3);
    REP(i, 1, cnt) pos[i] = (i - 1) / Block;
    REP(i, 1, q)
    {
        int opt; scanf("%lld", &opt);
        if ( opt == 0 ) 
        {
            int x, y; scanf("%lld%lld", &x, &y);
            b[++ tot2].pos = x; b[tot2].last = Color[x]; 
            b[tot2].now = Color[x] = y;
            continue ;
        }
        int u, v; scanf("%lld%lld", &u, &v);
        if ( f[u] > f[v] ) swap(u, v);
        a[++ tot1].l = LCA(u, v) == u ? f[u] : g[u]; a[tot1].r = f[v];
        a[tot1].id = tot1; a[tot1].t = tot2;
    }
    REP(i, 1, n) Color[i] = C[i]; 
    sort(a + 1, a + tot1 + 1);
    int L = 0, R = 0, T = 1;
    REP(i, 1, tot1)
    {
        while ( T <= a[i].t ) { Modify(b[T].pos, b[T].now); ++ T; }
        while ( T > a[i].t ) { Modify(b[T].pos, b[T].last); -- T; }
        while ( L < a[i].l ) { add(id[L]); ++ L; } 
        while ( L > a[i].l ) { -- L; add(id[L]); }
        while ( R < a[i].r ) { ++ R; add(id[R]); }
        while ( R > a[i].r ) { add(id[R]); -- R; }
        int u = id[L], v = id[R], x = LCA(u, v);
        if ( x != u && x != v ) add(x);
        ans[a[i].id] = num;
        if ( x != u && x != v ) add(x);
    }
    REP(i, 1, tot1) printf("%lld\n", ans[i]);
    return 0;
}
