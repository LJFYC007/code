/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年01月10日 星期日 11时47分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 1e18;

int N, n, m, k, q, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], dfn[maxn], low[maxn], dep[maxn];
int f[maxn], Stack[maxn], tot, cnt, sum, ans, size[maxn], anc[maxn][20], dis[maxn], s, W[maxn];
vector<int> Edge[maxn];

inline int LCA(int x, int y)
{
    if ( !dis[x] ) return 0;
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int i = 18; i >= 0; -- i ) if ( dis[anc[x][i]] >= dis[y] ) x = anc[x][i];
    if ( x == y ) return x;
    for ( int i = 18; i >= 0; -- i ) if ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; }
    return anc[x][0];
}

inline int Dis(int x, int y) 
{ 
    int t = LCA(x, y);
    // cout << x << " " << y << " " << t << endl;
    return dep[x] + dep[y] - dep[t] - dep[anc[t][0]]; 
}

inline void add(int u, int v) 
{ 
    int w = Dis(u, v);
    // cout << u << " " << v << " " << w << endl;
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
    swap(u, v);
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; 
} 

inline void Tarjan(int u)
{
    dfn[u] = low[u] = ++ cnt; Stack[++ tot] = u;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( !dfn[v] ) 
        {
            Tarjan(v); low[u] = min(low[u], low[v]);
            if ( low[v] == dfn[u] ) 
            {
                ++ n; Edge[n].push_back(u); Edge[u].push_back(n);
                do { Edge[n].push_back(Stack[tot]); Edge[Stack[tot]].push_back(n); -- tot; } while ( Stack[tot + 1] != v ) ; 
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}

inline void DFS(int u, int fa)
{
    dfn[u] = ++ cnt;
    for ( auto v : Edge[u] ) if ( v != fa ) 
    {
        dis[v] = dis[u] + 1; dep[v] = dep[u] + (v <= N); anc[v][0] = u;
        DFS(v, u);
    }
}

inline void DFS1(int u, int fa, int t)
{
    size[u] = f[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS1(v, u, t); size[u] += size[v]; 
    }
    // cout << u << " " << Dis(u, fa) << " " << fa << " " << size[u] << endl;
    if ( u != t ) sum += size[u] * (Dis(u, fa) - (fa <= N));
}

inline void DFS2(int u, int fa)
{
    if ( u <= N ) ans = min(ans, sum);
    else 
    {
        int Max = -INF;
        for ( int i = Begin[u]; i; i = Next[i] ) 
            if ( To[i] != fa ) Max = max(Max, size[To[i]]);
            else Max = max(Max, k - size[u]);
        // if ( u == 11 ) cout << sum << " " << Max << endl;
        ans = min(ans, sum - Max);   
    }
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        sum -= size[v] * (W[i] - (u <= N)); 
        sum += (k - size[v]) * (W[i] - (v <= N));
        DFS2(v, u);
        sum += size[v] * (W[i] - (u <= N)); 
        sum -= (k - size[v]) * (W[i] - (v <= N));
    }
}

inline void Build()
{
    sort(a + 1, a + k + 1, [](int a, int b) { return dfn[a] < dfn[b]; });
    tot = 1; s = a[1]; Stack[1] = s; e = Begin[s] = 0;
    REP(i, 2, k) if ( a[i] != a[i - 1] )
    {
        int x = LCA(a[i], Stack[tot]);
        if ( x != Stack[tot] ) 
        {
            while ( dfn[x] < dfn[Stack[tot - 1]] ) { add(Stack[tot], Stack[tot - 1]); -- tot; }
            if ( dfn[x] > dfn[Stack[tot - 1]] ) { Begin[x] = 0; add(Stack[tot], x); Stack[tot] = x; }
            else { add(Stack[tot], Stack[tot - 1]); -- tot; } 
        }
        Begin[a[i]] = 0; Stack[++ tot] = a[i];
    }
    while ( tot > 1 ) { add(Stack[tot], Stack[tot - 1]); -- tot; }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &q);
    REP(i, 1, m) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); }
    N = n; Tarjan(1);
    // REP(i, 1, n) for ( auto it : Edge[i] ) cout << it << " " << i << endl;
    dis[1] = dep[1] = 1; cnt = 0; DFS(1, 0); REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    while ( q -- ) 
    {
        scanf("%lld", &k); REP(i, 1, k) { scanf("%lld", &a[i]); ++ f[a[i]]; } 
        Build(); sum = 0; ans = INF; DFS1(s, 0, s); DFS2(s, 0);
        printf("%lld\n", (N - 1) * k - ans);
        REP(i, 1, k) -- f[a[i]];
    }
    return 0;
}
