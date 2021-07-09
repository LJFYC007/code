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

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn], n;
int dis[maxn], size[maxn], S[maxn], Size, root, Max[maxn], Ans[3], ans;
bool vis[maxn], use[maxn];

inline int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

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
    for ( int i = Begin[u]; i; i = Next[i])
    {
        int v = To[i];
        if ( v == fa || use[v] ) continue ;
        Get_Root(v, u);
        size[u] += size[v];
        Max[u] = max(Max[u], size[v]);
    }
    Max[u] = max(Max[u], Size - size[u]);
    if ( Max[u] < Max[root] ) root = u;
}

inline void Get_Dis(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i];
        if ( v == fa || use[v] ) continue ;
        dis[v] = (dis[u] + W[i]) % 3;
        Ans[dis[v]] ++;
        Get_Dis(v, u);
    }
}

inline int calc(int x, int w)
{
    dis[root] = w;
    Ans[0] = Ans[1] = Ans[2] = 0;
    Ans[w % 3] ++;
    Get_Dis(x, 0);
    return Ans[0] * Ans[0] + Ans[1] * Ans[2] * 2;
}

inline void Get_Ans(int x)
{
    ans += calc(x, 0);
    for ( int i = Begin[x]; i; i = Next[i] )
    {
        int v = To[i];
        if ( use[v] ) continue ;
        ans -= calc(v, W[i]);
        Size = size[v]; root = v;
        Get_Root(v, 0);
        use[root] = true;
        Get_Ans(root);
    }
}

inline void Solve()
{
    root = 1; Size = n; Max[0] = n;
    Get_Root(1, 1);
    use[root] = true;
    Get_Ans(root);
    printf("%d/%d\n", ans / gcd(ans, n * n), n * n / gcd(ans, n * n));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n - 1) 
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    Solve();
    return 0;
}
