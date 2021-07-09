/***************************************************************
	File name: flow.cpp
	Author: ljfcnyali
	Create time: 2019年08月10日 星期六 14时42分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 10010;
const int Mod = 19260817;

int n, m, Begin[maxn], Next[maxn], To[maxn], e = 1, x;
int p[maxn], cnt, f[maxn], id, dfn[maxn], low[maxn], ans, tot;
bool vis[maxn];
LL Hash[maxn];
stack<int> Stack;

inline int cha(int x) { return x == f[x] ? x : f[x] = cha(f[x]); }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    dfn[u] = low[u] = ++ cnt; Stack.push(u);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( (i ^ 1) == id || i == id ) continue ;
        if ( vis[i] || vis[i ^ 1] ) continue ;
        if ( !dfn[v] ) { vis[i] = vis[i ^ 1] = true; DFS(v); low[u] = min(low[u], low[v]); vis[i] = vis[i ^ 1] = false; }
        else low[u] = min(low[u], dfn[v]);
    }
    if ( dfn[u] == low[u] )
    {
        p[u] = ++ tot;
        while ( Stack.top() != u ) { p[Stack.top()] = tot; Stack.pop(); }
        Stack.pop();
    }
}

inline int js(int s, int t)
{
    int fx = cha(s), fy = cha(t); if ( fx != fy ) return 0;
    if ( p[s] != p[t] ) return 1;
    if ( Hash[s] == Hash[t] ) return 3;
    return 2;
}

int main()
{
    freopen("flow.in", "r", stdin);
    freopen("flow.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &x);
    REP(i, 1, n) f[i] = i;
    REP(i, 1, m) 
    { 
        int u, v; scanf("%d%d", &u, &v);
        add(u, v); add(v, u); 
        int fx = cha(u), fy = cha(v); if ( fx != fy ) f[fx] = fy;
    }
    REP(i, 1, m + 1)
    {
        id = i * 2; mem(dfn); mem(low); mem(vis); cnt = 0;
        REP(j, 1, n) if ( !dfn[j] ) DFS(j);
        REP(j, 1, n) Hash[j] = Hash[j] * Mod + p[j];
    }
    REP(i, 1, n - 1) REP(j, i + 1, n) ans += js(i, j);
    printf("%d\n", ans);
    return 0;
}
