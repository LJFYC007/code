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

const int maxn = 400010;
const int INF = 1000001;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn], n, k;
int size[maxn], Max[maxn], Size, root, cnt, ans = INF;
bool vis[maxn], use[maxn];

struct node
{
    int dis, p, sum;
} dis[maxn];

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline void Get_Root(int u, int fa)
{
    size[u] = 1; Max[u] = 0;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i];
        if ( use[v] || v == fa ) continue ;
        Get_Root(v, u);
        size[u] += size[v];
        Max[u] = max(Max[u], size[v]);
    }
    Max[u] = max(Max[u], Size - size[u]);
    if ( Max[u] < Max[root] ) root = u;
}

inline bool cmp(node a, node b)
{
    return a.dis < b.dis || (a.dis == b.dis && a.sum < b.sum);
}

inline void Get_Dis(int u, int fa, int s)
{
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i];
        if ( use[v] || v == fa ) continue ;
        dis[++ cnt].dis = dis[s].dis + W[i]; 
        dis[cnt].sum = dis[s].sum + 1;
        dis[cnt].p = dis[s].p;
        if ( dis[cnt].sum > ans || dis[cnt].dis > k ) { -- cnt; continue ; }
        Get_Dis(v, u, cnt);
    }
}

inline void Get_Ans(int u)
{
    cnt = 1;
    dis[cnt].dis = 0; dis[cnt].sum = 0; dis[cnt].p = u;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i];
        if ( use[v] ) continue ;
        dis[++ cnt].dis = W[i]; dis[cnt].p = v; dis[cnt].sum = 1;
        if ( dis[cnt].sum > ans || dis[cnt].dis > k ) { -- cnt; continue; }
        Get_Dis(v, u, cnt);
    }
    sort ( dis + 1, dis + cnt + 1, cmp );
    if ( dis[cnt].dis == k ) ans = min(ans, dis[cnt].sum);
    REP(i, 1, cnt - 1)
    {
        if ( dis[i].dis + dis[cnt].dis < k ) continue ;
        if ( dis[i].dis == k ) ans = min(ans, dis[i].sum);
        if ( dis[i].dis >= k ) continue ;
        int l = i, r = cnt, s = -1;
        while ( l <= r ) 
        {
            int Mid = (l + r) / 2;
            if ( dis[Mid].dis + dis[i].dis >= k ) 
            {
                s = Mid; r = Mid - 1;
            }
            else l = Mid + 1;
        }
        while ( dis[i].dis + dis[s].dis == k && s <= cnt && dis[i].sum + dis[s].sum < ans ) 
        {
            if ( dis[s].p != dis[i].p ) ans = min(ans, dis[s].sum + dis[i].sum);
            ++ s;
        }
    }
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i];
        if ( use[v] ) continue ;
        root = v; Size = size[v]; Max[root] = Size;
        Get_Root(v, 0);
        use[root] = true;
        Get_Ans(root);
    }
}

inline void Solve()
{
    root = 0; Size = n; Max[root] = Size;
    Get_Root(0, 0);
    use[root] = true;
    Get_Ans(root);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    REP(i, 1, n - 1)
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    Solve();
    if ( ans == INF ) printf("-1\n");
    else printf("%d\n", ans);
    return 0;
}
