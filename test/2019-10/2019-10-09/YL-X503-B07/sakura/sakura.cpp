/***************************************************************
	File name: sakura.cpp
	Author: ljfcnyali
	Create time: 2019年10月09日 星期三 19时48分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5000010;
const int Mod = 998244353;

int Begin[maxn], Next[maxn], To[maxn], e = 1, W[maxn];
int n, m, p, ans, dis[maxn], anc[maxn], len[maxn], g[maxn];
int Min, pos, f[maxn], sum1[maxn], sum2[maxn], tot;
bool ban[maxn], use[maxn];
struct node
{
    int u, v, w;
    bool operator < (const node &a) const { return w > a.w; }
} a[maxn], b[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline int power(int a, int b)
{
    // printf("%lld %lld\n", a, b);
    int r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; }
    return r;
}

inline int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        anc[v] = u; dis[v] = dis[u] + 1; len[v] = W[i]; DFS(v, u);
    }
}

signed main()
{
    freopen("sakura.in", "r", stdin);
    freopen("sakura.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &p);
    REP(i, 1, m) scanf("%lld%lld%lld", &a[i].u, &a[i].v, &a[i].w);
    sort(a + 1, a + m + 1);
    REP(i, 1, n) f[i] = i;
    REP(i, 1, m)
    {
        int fx = find(a[i].u), fy = find(a[i].v);
        if ( fx == fy ) continue ;
        use[i] = true;
        add(a[i].u, a[i].v, a[i].w); add(a[i].v, a[i].u, a[i].w);
        f[fx] = fy;
    }
    dis[1] = 1; DFS(1, 0);
    REP(i, 1, m)
    {
        if ( !use[i] ) continue ;
        int u = a[i].u, v = a[i].v;
        if ( dis[u] > dis[v] ) g[u] = i; else g[v] = i;
    }
    REP(i, 1, m)
    {
        if ( use[i] ) continue ;
        int u = a[i].u, v = a[i].v;
        if ( dis[u] < dis[v] ) swap(u, v); Min = a[i].w; pos = i;
        while ( dis[anc[u]] >= dis[v] ) { if ( len[u] < Min ) { Min = len[u]; pos = g[u]; } u = anc[u]; }
        while ( u != v ) 
        {
            if ( len[u] < Min ) { Min = len[u]; pos = g[u]; }
            if ( len[v] < Min ) { Min = len[v]; pos = g[v]; }
            u = anc[u]; v = anc[v];
        }
        ban[pos] = true; if ( i != pos ) a[i].w += Min;
        u = a[i].u; v = a[i].v; 
        if ( dis[u] < dis[v] ) swap(u, v);
        while ( dis[anc[u]] >= dis[v] ) { if ( g[u] != pos ) a[g[u]].w += Min; u = anc[u]; }
        if ( u == v ) continue ;
        while ( u != v ) 
        { 
            if ( g[u] != pos ) a[g[u]].w += Min;
            if ( g[v] != pos ) a[g[v]].w += Min; 
            u = anc[u]; v = anc[v]; 
        }
    }
    REP(i, 1, n) 
    { 
        f[i] = i; 
        int x = ((i - 1) * n) % (Mod - 1);
        sum1[i] = power(p, x); 
        sum2[i] = power(p, i); 
    }
    REP(i, 1, m) if ( !ban[i] ) b[++ tot] = a[i];
    sort(b + 1, b + tot + 1);
    REP(i, 1, tot)
    {
        int fx = find(b[i].u), fy = find(b[i].v);
        int x = (sum1[fx] * sum2[fy]) % Mod, y = (sum1[fy] * sum2[fx]) % Mod;
        int sum = (x + y) % Mod; sum = (sum * b[i].w) % Mod;
        ans = (ans + sum) % Mod;
        sum1[fy] = (sum1[fy] + sum1[fx]) % Mod; 
        sum2[fy] = (sum2[fy] + sum2[fx]) % Mod;
        f[fx] = fy;
    }
    printf("%lld\n", ans);
    return 0;
}
