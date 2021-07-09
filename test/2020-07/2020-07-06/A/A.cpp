/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年07月06日 星期一 08时52分34秒
***************************************************************/
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e18;

int n, m, N, ans[maxn], Stack[maxn], tot, h[maxn], a[maxn], dis[maxn], Min[maxn], Minn[maxn], val, anc[maxn][20];
bool vis[maxn];
vector<pii> Edge[maxn];

inline void Build();

inline void add(int u, int v, int w) { Edge[u].push_back(pii(v, w)); }

struct Tree
{
    int Begin[maxn], Next[maxn], To[maxn], e, W[maxn], dis[maxn];
    int Size, Max, Root, size[maxn], dfn[maxn], tot, Dis[maxn];
    bool use[maxn];
    
    inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

    inline void GetRoot(int u, int fa)
    {
        int MAX = 0; size[u] = 1;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( use[v] || v == fa ) continue ;
            GetRoot(v, u); size[u] += size[v];
            MAX = max(MAX, size[v]);
        }
        MAX = max(MAX, Size - size[u]);
        if ( MAX < Max ) { Max = MAX; Root = u; }
    }

    inline void DFS1(int u, int fa)
    {
        size[u] = 1; h[++ m] = u; a[u] = dis[u];
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( use[v] || v == fa ) continue ;
            dis[v] = dis[u] + W[i];
            DFS1(v, u); size[u] += size[v];
        }
    }

    inline void Solve(int u)
    {
        Max = Size; Root = m = 0;
        GetRoot(u, 0); u = Root;
        dis[u] = 0; DFS1(u, 0); Build();

        use[u] = true; 
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( use[v] ) continue ;
            Size = size[v]; Solve(v);
        }
    }

    inline void DFS(int u, int fa)
    {
        dfn[u] = ++ tot;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            anc[v][0] = u; dis[v] = dis[u] + 1; Dis[v] = Dis[u] + W[i]; DFS(v, u);
        }
    }

    inline int LCA(int u, int v)
    {
        if ( dis[u] < dis[v] ) swap(u, v);
        for ( int j = 17; j >= 0; -- j ) if ( dis[anc[u][j]] >= dis[v] ) u = anc[u][j];
        if ( u == v ) return u;
        for ( int j = 17; j >= 0; -- j ) if ( anc[u][j] != anc[v][j] ) { u = anc[u][j]; v = anc[v][j]; }
        return anc[u][0];
    }

    inline int Ddis(int u, int v) { return Dis[u] + Dis[v] - 2 * Dis[LCA(u, v)]; }

    inline void INIT()
    {
        dis[1] = 1; DFS(1, 0);
        REP(j, 1, 17) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    }
} A, B;

inline void DFS(int u)
{
    Min[u] = Minn[u] = INF;
    if ( vis[u] ) Min[u] = dis[u] + a[u];
    for ( auto v : Edge[u] ) 
    {
        dis[v.first] = dis[u] + v.second; 
        DFS(v.first);
        if ( Min[v.first] < Min[u] ) { Minn[u] = Min[u]; Min[u] = Min[v.first]; }
        else Minn[u] = min(Minn[u], Min[v.first]);
    }
}

inline void DFS2(int u, int dep)
{
    if ( vis[u] ) ans[u] = min(ans[u], min(val, (Min[u] - dep == a[u] ? Minn[u] : Min[u]) - dep) + a[u]);
    int x = val;
    for ( auto v : Edge[u] ) 
    {
        if ( Min[v.first] == Min[u] ) val = min(val, Minn[u] - dep);
        else val = min(val, Min[u] - dep);
        val += v.second;
        DFS2(v.first, dep + v.second);
        val = x; 
    }
}

inline void Build()
{
    tot = Stack[1] = 1; 
    sort(h + 1, h + m + 1, [](int x, int y) { return B.dfn[x] < B.dfn[y]; });
    REP(i, 1, m) vis[h[i]] = true;
    Edge[1].clear();
    REP(i, 1, m)
    {
        if ( h[i] == 1 ) continue ;
        int x = B.LCA(h[i], Stack[tot]);
        if ( x != Stack[tot] ) 
        {
            while ( B.dfn[x] < B.dfn[Stack[tot - 1]] ) { add(Stack[tot - 1], Stack[tot], B.Ddis(Stack[tot - 1], Stack[tot])); -- tot; }
            if ( B.dfn[x] != B.dfn[Stack[tot - 1]] ) 
            {
                Edge[x].clear(); 
                add(x, Stack[tot], B.Ddis(Stack[tot], x));
                Stack[tot] = x;
            }
            else { add(x, Stack[tot], B.Ddis(Stack[tot], x)); -- tot; }
        }
        Edge[h[i]].clear(); Stack[++ tot] = h[i]; 
    }
    REP(i, 1, tot - 1) add(Stack[i], Stack[i + 1], B.Ddis(Stack[i], Stack[i + 1]));

    dis[1] = 0; DFS(1); val = INF; DFS2(1, 0);
    REP(i, 1, m) vis[h[i]] = a[h[i]] = 0;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); A.add(u, v, w); A.add(v, u, w); }
    REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); B.add(u, v, w); B.add(v, u, w); }
    B.INIT(); 
    REP(i, 1, n) ans[i] = INF;
    A.Size = n; A.Solve(1);
    int ret = 0;
    REP(i, 1, n) ret ^= ans[i];
    printf("%lld\n", ret);
    return 0;
}
