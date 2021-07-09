/***************************************************************
	File name: P4180.cpp
	Author: ljfcnyali
	Create time: 2019年08月19日 星期一 16时06分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 2000010;

struct node
{
    int u, v, w;
    bool operator < (const node &a) const { return w < a.w; }
} a[maxn];

int f[maxn], n, m, dis[maxn], anc[maxn][22], Max[maxn][22], Maxx[maxn][22], root;
int Begin[maxn], Next[maxn], To[maxn], e, W[maxn], sum, ans = 0x3f3f3f3f3f3f, num;
bool use[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

inline void Kruskal()
{
    REP(i, 1, n) f[i] = i;
    REP(i, 1, m)
    {
        int fx = find(a[i].u), fy = find(a[i].v);
        if ( fx != fy )
        {
            f[fx] = fy; ++ num; sum += a[i].w;
            add(a[i].u, a[i].v, a[i].w);
            add(a[i].v, a[i].u, a[i].w);
            root = a[i].u;
            use[i] = true;
            if ( num == n - 1 ) return ;
        }
    }
}

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1;
        Max[v][0] = W[i]; Maxx[v][0] = -1;
        anc[v][0] = u;
        DFS(v, u);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 20; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 20; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

inline int Solve(int u, int v, int lca, int w)
{
    int MAX = 0;
    for ( int j = 20; j >= 0; -- j )
    {
        if ( dis[anc[u][j]] >= dis[lca] ) 
        {
            if ( Max[u][j] != w ) MAX = max(MAX, Max[u][j]);
            else MAX = max(MAX, Maxx[u][j]);
            u = anc[u][j];
        }
        if ( dis[anc[v][j]] >= dis[lca] ) 
        {
            if ( Max[v][j] != w ) MAX = max(MAX, Max[v][j]);
            else MAX = max(MAX, Maxx[v][j]);
            v = anc[v][j];
        }
    }
    return MAX;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) scanf("%lld%lld%lld", &a[i].u, &a[i].v, &a[i].w);
    sort(a + 1, a + m + 1);
    Kruskal();
    dis[root] = 1; DFS(root, 0);
    REP(j, 1, 20) REP(i, 1, n)
    {
        anc[i][j] = anc[anc[i][j - 1]][j - 1];
        int Max1 = Max[i][j - 1], Max2 = Max[anc[i][j - 1]][j - 1];
        int max1 = Maxx[i][j - 1], max2 = Maxx[anc[i][j - 1]][j - 1];
        if ( Max1 > Max2 ) 
        {
            Max[i][j] = Max1; Maxx[i][j] = max(Max2, max1);
        }
        else if ( Max1 < Max2 )
        {
            Max[i][j] = Max2; Maxx[i][j] = max(Max1, max2);
        }
        else
        {
            Max[i][j] = Max1; Maxx[i][j] = max(max1, max2);
        }
    }
    REP(i, 1, m)
    {
        if ( use[i] ) continue ;
        int Lca = LCA(a[i].u, a[i].v);
        ans = min(ans, sum - Solve(a[i].u, a[i].v, Lca, a[i].w) + a[i].w);
    }
    printf("%lld\n", ans);
    return 0;
}
