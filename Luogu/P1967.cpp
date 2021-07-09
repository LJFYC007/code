/*
 * Wrong !!!!!!
*/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int maxn = 100010;
const int INF = 2147483647;

int n, m, q, M, Begin[maxn], To[maxn], Next[maxn], e, W[maxn], dis[maxn], p[maxn][21];
int f[maxn], s, t, F[maxn][21], fa[maxn][21];

struct node
{
    int u, v, w;
}a[maxn];

inline bool cmp(node a, node b)
{
    return a.w > b.w;
}

inline int cha(int x)
{
    return x == f[x] ? x : f[x] = cha(f[x]);
}

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline void DFS(int x, int f)
{
    for ( int i = Begin[x]; i; i = Next[i] )
    {
        int u = To[i];
        if ( u == f ) continue ;
        if ( dis[u] > dis[x] + 1 ) 
        {
            dis[u] = dis[x] + 1;
            F[u][0] = x; p[x][0] = W[i];
            fa[x][0] = u;
            DFS(u, x);
        }
    }
}

inline void LCA(int s, int t)
{
    if ( dis[s] < dis[t] ) swap(s, t);
    int ans = INF;
    for ( int i = 20; i >= 0; -- i ) 
        if ( dis[F[s][i]] >= dis[t] ) 
        {
            s = F[s][i];
            ans = min(ans, p[s][i]);
        }
    if ( s == t ) { printf("%d\n", ans); return ; }
    for ( int i = 20; i >= 0; -- i )
        if ( F[s][i] != F[t][i] ) 
        {
            s = p[s][i];
            t = p[t][i];
            ans = min(ans, min(p[s][i], p[t][i]));
        }
    ans = min(ans, min(p[s][0], p[t][0]));
    printf("%d\n", ans);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m)
        scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
    REP(i, 1, n) f[i] = i;
    sort ( a + 1, a + m + 1, cmp );
    REP(i, 1, m)
    {
        if ( M == n - 1 ) break ;
        int fx = cha(a[i].u), fy = cha(a[i].v);
        if ( fx != fy ) 
        {
            ++ M;
            f[fx] = fy;
            add(a[i].u, a[i].v, a[i].w); add(a[i].v, a[i].u, a[i].w);
            if ( M == 1 ) s = a[i].u; 
            if ( M == n - 1 ) t = a[i].v;
        }
    }
    REP(i, 1, n) dis[i] = INF;
    dis[s] = 1;
    F[s][0] = 0;
    DFS(s, 0);     
    REP(i, 1, n)
        if ( dis[i] == INF ) { p[i][0] = INF; continue ; }
    REP(i, 1, 20)
        REP(j, 1, n)
        {
            if ( dis[i] == INF ) continue ;
            F[j][i] = F[F[j][i - 1]][i - 1];
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
            p[j][i] = min(p[j][i - 1], p[fa[j][i - 1]][i - 1]);
        }
    scanf("%d", &q);
    while ( q -- ) 
    {
        int u, v; scanf("%d%d", &u, &v);
        int fx = cha(u), fy = cha(v);
        if ( fx != fy ) printf("-1\n");
        else LCA(u, v);
    }
    return 0;
}
