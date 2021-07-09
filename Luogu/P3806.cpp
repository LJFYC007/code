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

const int maxn = 40010;
const int INF = 0x3f3f3f3f;

int Begin[maxn], To[maxn], Next[maxn], e, W[maxn], a[maxn], S[maxn];
int n, m, k, size[maxn], root, Size, Max[maxn], F[maxn], cnt;
bool vis[maxn], use[maxn];

struct node
{
    int dis, fa;
}dis[maxn];

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline void Get_Root(int u, int fa)
{
    Max[u] = 0; size[u] = 1;
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

inline void Get_Dis(int u, int fa, int d)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( use[v] || v == fa ) continue ;
        dis[++ cnt].dis = dis[d].dis + W[i];
        dis[cnt].fa = dis[d].fa;
        Get_Dis(v, u, cnt);
    }
}

inline bool cmp(node a, node b)
{
    return a.dis < b.dis;
}

inline void Get_Ans(int x)
{
    // printf("%d\n", x);
    cnt = 0;
    for ( int i = Begin[x]; i; i = Next[i] )
    {
        int v = To[i];
        if ( use[v] ) continue ;
        dis[++ cnt].dis = W[i]; dis[cnt].fa = v;
        Get_Dis(v, v, cnt);
    }
    // if ( x == 4 ) 
    // {
        // REP(i, 1, cnt) printf("%d ", dis[i].dis);
    // }
    sort ( dis + 1, dis + cnt + 1, cmp );
    REP(i, 1, m)
    {
        k = a[i];
        if ( dis[cnt].dis == k ) a[i] = -1;
        REP(j, 1, cnt - 1)
        {
            if ( a[i] == -1 ) break ;
            if ( dis[j].dis == k ) { a[i] = -1; continue; }
            if ( dis[j].dis + dis[cnt].dis < k ) continue ; 
            int l = j + 1, r = cnt, ans;
            while ( l <= r ) 
            {
                int Mid = (l + r) / 2;
                if ( dis[Mid].dis + dis[j].dis < k ) l = Mid + 1;
                else { ans = Mid; r = Mid - 1; }
            }
            while ( dis[j].dis + dis[ans].dis == k ) 
            { 
                if ( dis[j].fa != dis[ans].fa ) 
                    a[i] = -1; 
                ++ j;
            }
        }
    }
    REP(i, 1, n) S[i] = size[i];
    for ( int i = Begin[x]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( use[v] ) continue ;
        Size = S[v]; root = v; Get_Root(v, 0);
        use[root] = true; Get_Ans(root);
    }
}

inline void Solve()
{
    Size = n; root = 1; 
    Get_Root(1, 1);
    use[root] = true;
    Get_Ans(root); 
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) 
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    REP(i, 1, m) scanf("%d", &a[i]);
    Solve();
    REP(i, 1, m) if ( a[i] == -1 ) printf("AYE\n"); else printf("NAY\n");
    return 0;
}
