#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
 
const int maxn = 4e5 + 10;
const int Mod = 1e9 + 7;
const int inv2 = (Mod + 1) / 2;
 
int n, m, q, k, N, d[maxn], w[maxn], Begin[maxn], Next[maxn], To[maxn], e, num[maxn];
int dfn[maxn], low[maxn], tot, Stack[maxn], cnt, now, ans, f[maxn], g[maxn], h[maxn], b[maxn], anc[maxn];
vector<int> c[maxn], Edge[maxn];
map<int, int> Map[maxn];
bool vis[maxn];
 
inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 
inline void ADD(int u, int v) { Edge[u].push_back(v); Edge[v].push_back(u); w[v] += w[u]; }
 
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
 
inline void DFS1(int u, int fa)
{
    if ( d[u] == now ) f[u] = 1;
    for ( auto v : Edge[u] ) if ( v != fa ) { anc[v] = u; DFS1(v, u); f[u] = (f[u] + f[v]) % Mod; } 
    if ( vis[u] ) f[u] = (f[u] + f[u]) % Mod;
}
 
inline void DFS2(int u, int fa)
{
    if ( vis[fa] ) g[u] = (g[u] + g[u]) % Mod; if ( d[fa] == now ) ++ g[u]; 
    int sum = 0; for ( auto v : Edge[u] ) if ( v != fa ) sum = (sum + f[v]) % Mod;
    for ( auto v : Edge[u] ) if ( v != fa ) { g[v] = (g[u] + sum - f[v]) % Mod; DFS2(v, u); }
    for ( auto v : Edge[u] ) b[u] = (b[u] + (v == fa ? g[u] : f[v])) % Mod;
    h[u] = 1ll * b[u] * b[u] % Mod; 
    for ( auto v : Edge[u] ) h[u] = (h[u] - 1ll * (v == fa ? g[u] : f[v]) * (v == fa ? g[u] : f[v])) % Mod;
    h[u] = 1ll * h[u] * inv2 % Mod;
}
 
inline void DFS3(int u, int fa)
{
    for ( auto v : Edge[u] ) if ( v != fa ) DFS3(v, u);
    if ( u <= n ) 
    {
        int sum = 0; if ( d[u] == now ) ++ sum;
        for ( auto v : Edge[u] ) 
        {
            int x = v == fa ? g[u] : f[v];
            num[u] = (num[u] + 1ll * x * sum) % Mod; sum = (sum + x) % Mod;
        }
		// return ; 
        for ( auto v : Edge[u] ) 
        {
            num[u] = (num[u] + h[v]) % Mod;
            if ( v == fa ) num[u] = (num[u] - 1ll * f[u] * (b[v] - f[u])) % Mod;
            else num[u] = (num[u] - 1ll * g[v] * (b[v] - g[v])) % Mod;
            continue ;
            sum = 0;
            for ( auto t : Edge[v] ) if ( t != u ) 
            {
                int x = t == anc[v] ? g[v] : f[t];
                num[u] = (num[u] + 1ll * x * sum) % Mod; sum = (sum + x) % Mod;
            }
        }
    }
}
 
inline void Solve()
{
    ans = 0;
    REP(i, 1, k) 
    { 
        now = i; mem(f); mem(g); mem(b); mem(h); 
        DFS1(1, 0); DFS2(1, 0); DFS3(1, 0);
    }
}
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, n) { scanf("%d", &d[i]); c[d[i]].push_back(i); } 
    REP(i, 1, n) scanf("%d", &w[i]);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); ++ Map[u][v]; ++ Map[v][u]; } 
    N = n; Tarjan(1); REP(i, n + 1, N) if ( Edge[i].size() > 2 || Map[Edge[i][0]][Edge[i][1]] >= 2 ) vis[i] = true;
    Solve(); REP(i, 1, n) ans = (ans + 1ll * w[i] * num[i]) % Mod; printf("%d\n", (ans + Mod) % Mod);
	// REP(i, 1, n) cout << num[i] << " "; cout << endl;
    scanf("%d", &q);
    REP(i, 1, q) { int x, y; scanf("%d%d", &x, &y); ans = (ans + 1ll * y * num[x]) % Mod; printf("%d\n", (ans + Mod) % Mod); }
    return 0;
}
