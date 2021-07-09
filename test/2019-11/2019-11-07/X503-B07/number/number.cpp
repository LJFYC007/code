/***************************************************************
	File name: number.cpp
	Author: ljfcnyali
	Create time: 2019年11月07日 星期四 08时27分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2000010;
const int Mod = 998244353;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], Stack[maxn], ans[maxn];
int dep[maxn], d[maxn], p[maxn][22], fac[maxn], dis[maxn], anc[maxn][22], LOG[maxn];
bool use[maxn], vis[maxn];
vector<pii> Edge[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    vis[u] = true; Stack[dep[u]] = u;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        if ( vis[v] ) { REP(i, dep[v], dep[u]) use[Stack[i]] = true; continue ; }
        if ( dep[v] ) continue ;
        dep[v] = dep[u] + 1; DFS(v); 
    }
    vis[u] = false;
}

inline void DFS1(int u)
{
    vis[u] = true;
    for ( auto i : Edge[u] ) if ( !vis[i.first] ) DFS1(i.first);
}

inline bool Check(int x, int y, int w)
{
    if ( p[x][0] != w ) return w < p[x][0];
    x = anc[x][0];
    for ( int j = max(LOG[dis[x]], LOG[dis[y]]) + 1; j >= 0; -- j ) if ( p[x][j] == p[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return p[y][0] < p[x][0];
}

inline void toposort()
{
    REP(i, 1, n) for ( auto j : Edge[i] ) if ( !vis[i] && !vis[j.first] ) ++ d[j.first];
    queue<int> Q; REP(i, 1, n) if ( !d[i] && !vis[i] ) Q.push(i);
    while ( !Q.empty() )
    {
        int u = Q.front(); Q.pop();
        REP(i, 1, 20) 
        {
            anc[u][i] = anc[anc[u][i - 1]][i - 1];
            p[u][i] = (p[u][i - 1] + p[anc[u][i - 1]][i - 1] * fac[1 << i - 1]) % Mod;
        }
        for ( auto i : Edge[u] ) 
        {
            int v = i.first;
            if ( vis[v] ) continue ;
            -- d[v];
            if ( dis[v] < dis[u] + 1 || (dis[v] == dis[u] + 1 && Check(v, u, i.second)) ) 
            {
                dis[v] = dis[u] + 1; ans[v] = 29 * (i.second + ans[u]) % Mod;
                anc[v][0] = u; p[v][0] = i.second;
            }
            if ( !d[v] ) Q.push(v);
        }
    }
    REP(i, 1, n) if ( vis[i] ) printf("Infinity\n"); else printf("%lld\n", ans[i]);
}

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    read(n); read(m);
    REP(i, 1, m) 
    { 
        int u, v, w; read(u); read(v); read(w);
        if ( u == v ) { use[u] = true; continue ; }
        add(u, v, w); Edge[v].push_back(pii(u, w));
    }
    REP(i, 1, n) if ( !vis[i] ) DFS(i);
    REP(i, 1, n) vis[i] = false;
    REP(i, 1, n) if ( !vis[i] && use[i] ) DFS1(i);
    fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * 103 % Mod;
    LOG[0] = 1; REP(i, 1, n) LOG[i << 1] = LOG[i] + 1;
    toposort();
    return 0;
}
