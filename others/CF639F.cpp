/***************************************************************
	File name: CF639F.cpp
	Author: ljfcnyali
	Create time: 2021年01月18日 星期一 09时22分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

int n, m, q, Begin[maxn], Next[maxn], To[maxn], e = 1, dfn[maxn], low[maxn], tot, Stack[maxn], cnt, num;
int p[maxn], Root[maxn], Col[maxn], dis[maxn], anc[300010][20], S, N, id[maxn], belong[maxn];
LL R;
vector<int> Edge[maxn], V, a;
vector<pii> E;
bool vis[maxn], op, flag;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }
inline void Add(int u, int v) { add(u, v); add(v, u); }

inline void Tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ cnt; Stack[++ tot] = u; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( (i ^ 1) == fa ) continue ;
        if ( !dfn[v] ) 
        {
            Tarjan(v, i); low[u] = min(low[u], low[v]);
            if ( low[v] > dfn[u] ) 
            { 
                ++ m; p[v] = m; if ( !op ) Col[m] = num;
                while ( Stack[tot] != v ) p[Stack[tot --]] = m; -- tot; 
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}

inline void DFS1(int u, int fa)
{
    id[u] = ++ tot;
    for ( auto v : Edge[u] ) if ( v != fa ) 
    {
        dis[v] = dis[u] + 1; anc[v][0] = u;
        DFS1(v, u);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int i = 19; i >= 0; -- i ) if ( dis[anc[x][i]] >= dis[y] ) x = anc[x][i];
    if ( x == y ) return x;
    for ( int i = 19; i >= 0; -- i ) if ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; }
    return anc[x][0];
}

inline void Build()
{
    sort(a.begin(), a.end(), [](int &x, int &y) { return id[x] < id[y]; });
    // for ( auto it : a ) cout << it << " "; cout << endl;
    S = a[0]; e = 1; dfn[S] = low[S] = Begin[S] = 0; tot = 1; Stack[1] = S;
    for ( auto x : a ) 
    {
        if ( Col[x] != Col[Stack[tot]] ) 
        {
             while ( tot > 1 ) { Add(Stack[tot], Stack[tot - 1]); -- tot; } 
             Stack[tot] = S = x; dfn[x] = low[x] = Begin[x] = 0; 
        }
        if ( x == S ) continue ;
        int t = LCA(x, Stack[tot]);
        // cout << t << " " << x << " " << Stack[tot] << endl;
        if ( id[t] != id[Stack[tot]] ) 
        {
            while ( id[t] < id[Stack[tot - 1]] ) { Add(Stack[tot], Stack[tot - 1]); -- tot; } 
            if ( id[t] == id[Stack[tot - 1]] ) { Add(Stack[tot], Stack[tot - 1]); -- tot; }  
            else { dfn[t] = low[t] = Begin[t] = 0; Add(Stack[tot], t); Stack[tot] = t; } 
        }
        dfn[x] = low[x] = Begin[x] = 0; Stack[++ tot] = x;
    }
    while ( tot > 1 ) { Add(Stack[tot], Stack[tot - 1]); -- tot; } 
}

inline void Rotate(int &x) { x = ((LL)x + R) % N; if ( !x ) x = N; x = belong[x]; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); 
        if ( u == v ) continue ; 
        add(u, v); add(v, u); 
        if ( i == 1 && u == 82505 && v == 228842 ) flag = true;
    } 
    m = 0; REP(i, 1, n) if ( !dfn[i] ) 
    { 
        ++ num; Tarjan(i, 0); ++ m; Root[num] = m; Col[m] = num;
        while ( tot ) p[Stack[tot --]] = m;
    }
    // REP(i, 1, n) cout << p[i] << " "; cout << endl;
    REP(u, 1, n) for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( p[u] == p[v] ) continue ;
        Edge[p[u]].push_back(p[v]);
    }
    tot = 0; REP(i, 1, num) { dis[Root[i]] = 1; DFS1(Root[i], 0); } N = n;
    REP(j, 1, 19) REP(i, 1, m) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, n) belong[i] = p[i]; op = true;

    REP(o, 1, q)
    {
        scanf("%d%d", &n, &m); V.clear(); E.clear(); a.clear();
        // if ( o == 434 && flag ) { cout << n << " " << m << " "; } 
        REP(i, 1, n) 
        { 
            int x; scanf("%d", &x); Rotate(x); V.push_back(x); 
            if ( !vis[x] ) { vis[x] = true; a.push_back(x); }
        }
        REP(i, 1, m) 
        { 
            int u, v; scanf("%d%d", &u, &v); Rotate(u); Rotate(v); 
            if ( u == v ) continue ; 
            E.push_back(pii(u, v)); 
            if ( !vis[u] ) { vis[u] = true; a.push_back(u); }
            if ( !vis[v] ) { vis[v] = true; a.push_back(v); }
        }
        Build(); for ( auto it : E ) Add(it.first, it.second);
        cnt = tot = m = 0; 
        for ( auto it : a ) if ( !dfn[it] ) { Tarjan(it, 0); ++ m; while ( tot ) p[Stack[tot --]] = m; }

        // if ( o == 434 && flag ) { for ( auto it : V ) cout << it << " "; }
        for ( int i = 1; i < V.size(); ++ i ) if ( p[V[i]] != p[V[i - 1]] ) { puts("NO"); goto Next ; } 
        puts("YES"); R += o;
Next : ; 
        for ( auto it : V ) vis[it] = false;
        for ( auto it : E ) vis[it.first] = vis[it.second] = false;
    }
    return 0;
}
