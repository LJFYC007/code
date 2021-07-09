#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> LL maxx(T a, T b) { return a > b ? a : b; }
template<class T> LL minn(T a, T b) { return a < b ? a : b; }
template<class T> LL abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int maxn = 2000010;

LL sum[maxn], n, Begin[maxn], To[maxn], Next[maxn], W[maxn], e, ans, dis[maxn];

struct node
{
    LL u, v, w;
} a[maxn];

inline void add(LL u, LL v, LL w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS(LL u, LL pa)
{
    sum[u] = 1;
    for ( LL i = Begin[u]; i; i = Next[i] )
    {
        LL v = To[i];
        if ( v == pa ) continue ;
        dis[v] = dis[u] + 1;
        DFS(v, u);
        sum[u] += sum[v];
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n - 1)
    {
        LL u, v, w; scanf("%lld%lld%lld", &u, &v, &w);
        add(u, v, w); add(v, u, w);
        a[i].u = u; a[i].v = v; a[i].w = w;
    }
    dis[1] = 1;
    DFS(1, 0);
    // REP(i, 1, n) printf("%lld ", dis[i]); puts("");
    REP(i, 1, n - 1)
    {
        LL u = a[i].u, v = a[i].v;
        if ( dis[u] > dis[v] ) swap(u, v);
        ans += a[i].w * abs(n - sum[v] - sum[v]);
    }
    printf("%lld\n", ans);
    return 0;
}
