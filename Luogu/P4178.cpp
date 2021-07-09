/***************************************************************
	File name: P4178.cpp
	Author: ljfcnyali
	Create time: 2019年10月15日 星期二 16时19分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1000010;
const int INF = 0x3f3f3f3f;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, k, dis[maxn], Root, Maxx, size[maxn], Size;
int p[maxn], id[maxn], tot, ans;
bool use[maxn];
pii a[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void Get_Root(int u, int fa)
{
    size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( use[v] || v == fa ) continue ;
        Get_Root(v, u); 
        size[u] += size[v];
        Max = max(Max, size[v]);
    }
    Max = max(Max, Size - size[u]);
    if ( Max < Maxx ) { Maxx = Max; Root = u; }
}

inline void Get_Dis(int u, int fa)
{
    if ( dis[u] > k ) return ; ++ p[id[u]];
    ++ ans; a[++ tot] = make_pair(dis[u], id[u]);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( use[v] || v == fa ) continue ;
        dis[v] = dis[u] + W[i]; id[v] = id[u];
        Get_Dis(v, u);
    }
}

inline void Solve(int u)
{
    tot = 0; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( use[v] ) continue ;
        id[v] = v; dis[v] = W[i]; p[v] = 0;
        Get_Dis(v, u);
    }
    sort(a + 1, a + tot + 1);
    // puts("");
    // REP(i, 1, tot) printf("%lld %lld\n", a[i].first, a[i].second);
    int R = tot;
    REP(i, 1, tot)
    {
        -- p[a[i].second];
        while ( a[i].first + a[R].first > k && R ) { -- p[a[R].second]; -- R; }
        if ( i > R ) break ; 
        ans += R - i - p[a[i].second];
        // printf("%lld %lld %lld\n", i, R, p[a[i].second]);
    }
    // printf("%lld %lld\n", Root, ans);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( use[v] ) continue ;
        Maxx = INF; Size = size[v];
        Get_Root(v, u); use[Root] = true; Solve(Root);
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
    scanf("%lld", &k);
    Size = n; Maxx = INF; Get_Root(1, 0); use[Root] = true; Solve(Root);
    printf("%lld\n", ans);
    return 0;
}
