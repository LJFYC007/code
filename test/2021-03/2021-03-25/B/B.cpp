#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
 
const int maxn = 1e6 + 10;
const int MAXN = 5e5 + 10;
const int maxm = 2e6 + 10;
const int Mod = 1e9 + 7;
const int inv2 = (Mod + 1) / 2;
 
int n, m, q, k, N, d[maxn], w[maxn], Begin[maxm], Next[maxm], To[maxm], e, num[maxn], dis[maxn], tag3[maxn];
int dfn[maxn], low[maxn], tot, Stack[maxn], cnt, now, ans, f[maxn], g[maxn], h[maxn], b[maxn], Root, W[maxm], fac[maxn];
int Begin1[maxm], Next1[maxm], To1[maxm], e1, deg[maxn], size[maxn], top[maxn], son[maxn], anc[maxn], tag1[maxn], tag2[maxn];
vector<int> c[MAXN]; vector<pii> p[MAXN];
bool vis[maxn];
 
inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = 1ll * r * a % Mod; a = 1ll * a * a % Mod; b >>= 1; } return r; } 
inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }
inline void ADD(int u, int v) 
{ 
    To1[++ e1] = v; Next1[e1] = Begin1[u]; Begin1[u] = e1;
    swap(u, v); ++ deg[u]; ++ deg[v];
    To1[++ e1] = v; Next1[e1] = Begin1[u]; Begin1[u] = e1;
}
inline void Add(int u, int v)
{
    int w = 1ll * fac[anc[v]] * power(fac[u], Mod - 2) % Mod;
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
    swap(u, v); To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w;
}
 
inline void Tarjan(int u)
{
    dfn[u] = low[u] = ++ tot; Stack[++ cnt] = u;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        if ( !dfn[v] ) 
        {
            Tarjan(v); low[u] = min(low[u], low[v]);
            if ( low[v] == dfn[u] ) 
            {
                ++ N; ADD(u, N); 
                while ( Stack[cnt] != v ) ADD(Stack[cnt --], N);
                ADD(v, N); -- cnt;
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}
 
inline void DFS4(int u, int fa)
{
    dfn[u] = ++ tot; size[u] = 1;
    for ( int i = Begin1[u]; i; i = Next1[i] ) 
    {
        int v = To1[i]; if ( v == fa ) continue ; 
        dis[v] = dis[u] + 1; anc[v] = u; fac[v] = fac[u]; 
        if ( vis[v] ) fac[v] = (fac[v] + fac[v]) % Mod; 
        DFS4(v, u); size[u] += size[v]; if ( size[v] > size[son[u]] ) son[u] = v;
    }
}
 
inline void DFS5(int u, int t)
{
    top[u] = t;
    if ( son[u] ) DFS5(son[u], t);
    for ( int i = Begin1[u]; i; i = Next1[i] ) 
    {
        int v = To1[i]; if ( v == anc[u] || v == son[u] ) continue ; 
        DFS5(v, v);
    }
}
 
inline int LCA(int x, int y)
{
    while ( top[x] != top[y] ) 
    {
        if ( dis[top[x]] < dis[top[y]] ) swap(x, y);
        x = anc[top[x]];
    }
    return dis[x] < dis[y] ? x : y;
}
 
inline int Get(int x, int y) { while ( top[x] != top[y] ) x = anc[top[x]]; return anc[x] == y ? x : son[y]; }
 
inline void DFS1(int u, int fa)
{
    if ( d[u] == now ) f[u] = 1; else f[u] = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        DFS1(v, u); f[u] = (f[u] + 1ll * f[v] * W[i]) % Mod; 
    }
    if ( vis[u] ) f[u] = (f[u] + f[u]) % Mod;
}
 
inline void DFS2(int u, int fa)
{
    int sum = 0; b[u] = h[u] = 0; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i], val = (v == fa ? g[u] : 1ll * f[v] * W[i] % Mod);
        b[u] = (b[u] + val) % Mod; h[u] = (h[u] - 1ll * val * val) % Mod;
        if ( v == fa ) continue ;
        sum = (sum + 1ll * f[v] * W[i]) % Mod;
    }
    h[u] = (1ll * b[u] * b[u] + h[u]) % Mod * inv2 % Mod;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        int val = (g[u] + sum - 1ll * f[v] * W[i]) % Mod;
        if ( vis[u] ) val = (val + val) % Mod; if ( d[u] == now ) ++ val;
        g[v] = 1ll * val * W[i] % Mod; DFS2(v, u); 
    }
}
 
inline void DFS3(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; DFS3(v, u);
        int val = 1ll * f[v] * g[v] % Mod, x = Get(v, u);
        tag2[anc[v]] = (tag2[anc[v]] + val) % Mod; tag2[u] = (tag2[u] - val) % Mod;
        x = Get(v, u); val = 1ll * val * inv2 % Mod;
        tag1[v] = (tag1[v] + val) % Mod; tag1[x] = (tag1[x] - val) % Mod;
    }
    if ( u <= n ) 
    {
        int sum = 0; if ( d[u] == now ) ++ sum;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i], x = v == fa ? g[u] : 1ll * f[v] * W[i] % Mod;
            num[u] = (num[u] + 1ll * x * sum) % Mod; sum = (sum + x) % Mod;
        }
    }
    if ( vis[u] ) 
    {
        tag3[u] = (tag3[u] + h[u]) % Mod;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; 
            if ( v == fa ) num[anc[u]] = (num[anc[u]] - 1ll * g[u] * (b[u] - g[u])) % Mod;
            else { int x = Get(v, u); num[x] = (num[x] - 1ll * f[v] * W[i] % Mod * (b[u] - 1ll * f[v] * W[i] % Mod)) % Mod; }
        }
    }
}
 
inline void Build(int x)
{
    sort(c[x].begin(), c[x].end(), [](int a, int b) { return dfn[a] < dfn[b]; } );
    e = tot = 0; Stack[++ tot] = c[x][0]; Begin[c[x][0]] = 0;
    for ( auto it : c[x] ) if ( it != c[x][0] ) 
    {
        int t = LCA(it, Stack[tot]);
        if ( t != Stack[tot] ) 
        {
            while ( dfn[Stack[tot - 1]] > dfn[t] ) { Add(Stack[tot - 1], Stack[tot]); -- tot; } 
            if ( Stack[tot - 1] != t ) { Begin[t] = 0; Add(t, Stack[tot]); Stack[tot] = t; } 
            else { Add(Stack[tot - 1], Stack[tot]); -- tot; } 
        }
        Begin[it] = 0; Stack[++ tot] = it;
    }
    while ( tot > 1 ) { Add(Stack[tot - 1], Stack[tot]); -- tot; } 
}
 
inline void DFS(int u, int fa)
{
    int sum = 0;
    for ( int i = Begin1[u]; i; i = Next1[i] ) 
    {
        int v = To1[i]; if ( v == fa ) continue ; 
        DFS(v, u); sum = (sum + tag1[v]) % Mod; tag2[u] = (tag2[u] + tag2[v]) % Mod;
    }
    for ( int i = Begin1[u]; i; i = Next1[i] ) 
    {
        int v = To1[i]; 
        num[v] = (num[v] + tag3[u]) % Mod;
        if ( v == fa ) continue ; 
        num[v] = ((num[v] + sum) % Mod - tag1[v]) % Mod;
    }
    num[u] = (num[u] + tag2[u]) % Mod; tag1[u] = (tag1[u] + sum) % Mod;
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k); 
    REP(i, 1, n) { scanf("%d", &d[i]); c[d[i]].push_back(i); } 
    REP(i, 1, n) scanf("%d", &w[i]);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); } 
    N = n; Tarjan(1); 
    REP(i, n + 1, N) 
    {
        if ( deg[i] > 2 ) { vis[i] = true; continue ; } 
        int x = To1[Begin1[i]], y = To1[Next1[Begin1[i]]];
        if ( x > y ) swap(x, y); p[x].push_back(pii(y, i));
    }
    REP(i, 1, n) deg[i] = 0; 
    REP(u, 1, n) 
    {
        for ( int i = Begin[u]; i; i = Next[i] ) ++ deg[To[i]];
        for ( auto it : p[u] ) if ( deg[it.first] >= 2 ) vis[it.second] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) -- deg[To[i]];
    }
 
    dis[1] = fac[1] = 1; tot = 0; DFS4(1, 0); DFS5(1, 1);
    REP(i, 1, k) if ( c[i].size() ) 
    {
        now = i; Build(i); Root = Stack[1]; g[Root] = 0;
        DFS1(Root, 0); DFS2(Root, 0); DFS3(Root, 0);
    }
    DFS(1, 0);
    REP(i, 1, n) ans = (ans + 1ll * w[i] * num[i]) % Mod; printf("%d\n", (ans + Mod) % Mod);
    scanf("%d", &q);
    REP(i, 1, q) { int x, y; scanf("%d%d", &x, &y); ans = (ans + 1ll * y * num[x]) % Mod; printf("%d\n", (ans + Mod) % Mod); }
    return 0;
}
