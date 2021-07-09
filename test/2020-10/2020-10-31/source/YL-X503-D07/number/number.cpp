/***************************************************************
	File name: number.cpp
	Author: ljfcnyali
	Create time: 2020年11月01日 星期日 15时30分36秒
***************************************************************/
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;
#define pii pair<LL, LL>

const int maxn = 6e5 + 10;

int n, q, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], cnt, id[maxn], h[maxn];
int belong[maxn], dfn[maxn], tot, st[maxn][20], K = 100, dep[maxn], lg[maxn];
int Stack[maxn], son[maxn], f[maxn];
LL Dis[maxn], dis[maxn], ans, Max;
vector<pii> Edge[maxn], p;
vector<int> ccc;
pii g[maxn];
struct node { vector<int> a; } Tree[maxn << 2];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS1(int u, int fa)
{
    dfn[u] = ++ tot; h[++ cnt] = u; id[u] = cnt;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dep[v] = dep[u] + 1; dis[v] = dis[u] + W[i];
        DFS1(v, u); h[++ cnt] = u;
    }
}

inline int LCA(int x, int y)
{
    int L = min(id[x], id[y]), R = max(id[x], id[y]);
    int len = lg[R - L + 1];
    return dep[st[L][len]] < dep[st[R - (1 << len) + 1][len]] ? st[L][len] : st[R - (1 << len) + 1][len];
}

inline void Add(int u, int v) { LL w = abs(dis[u] - dis[v]); Edge[u].push_back(pii(v, w)); Edge[v].push_back(pii(u, w)); }

inline void DFS3(int u, int fa)
{
    Dis[u] = 0; f[u] = u;
    for ( auto v : Edge[u] )
    {
        if ( v.first == fa ) continue ;
        DFS3(v.first, u);
        if ( Dis[v.first] + v.second > Dis[u] ) 
        {
            Dis[u] = Dis[v.first] + v.second;
            son[u] = v.first; f[u] = f[v.first];
        }
    }
    for ( auto v : Edge[u] ) 
    {
        if ( v.first == fa || v.first == son[u] ) continue ;
        p.push_back(pii(Dis[v.first] + v.second, f[v.first]));
    }
}

inline vector<int> Solve(vector<int> a, int k)
{
    sort(a.begin(), a.end(), [](int a, int b) { return dfn[a] < dfn[b]; });
    tot = 1; Stack[1] = a[0]; Edge[a[0]].clear();
    for ( auto it : a ) 
    {
        if ( it == a[0] ) continue ;
        int t = LCA(it, Stack[tot]);
        if ( t != Stack[tot] ) 
        {   
            while ( dfn[t] < dfn[Stack[tot - 1]] ) { Add(Stack[tot], Stack[tot - 1]); -- tot; }
            if ( t != Stack[tot - 1] ) { Edge[t].clear(); Add(Stack[tot], t); Stack[tot] = t; }
            else { Add(Stack[tot], Stack[tot - 1]); -- tot; }
        }
        Edge[it].clear(); Stack[++ tot] = it;
    }
    while ( tot > 1 ) { Add(Stack[tot], Stack[tot - 1]); -- tot; }

    int Root; Max = -1; for ( auto it : a ) if ( dis[it] > Max ) { Root = it; Max = dis[it]; }
    p.clear(); DFS3(Root, 0);
    if ( f[Root] != Root ) p.push_back(pii(Dis[Root], f[Root]));
    sort(p.begin(), p.end()); 
    a.clear(); a.push_back(Root); -- k;
    while ( k && p.size() ) 
    { 
        a.push_back(p.back().second); ans += p.back().first; 
        -- k; p.pop_back();
    }
    return a;
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) 
    { 
        REP(i, g[l].first, g[l].second) Tree[root].a.push_back(i);
        return ; 
    }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Tree[root].a = Tree[lson].a;
    for ( auto it : Tree[rson].a ) Tree[root].a.push_back(it);
    Tree[root].a = Solve(Tree[root].a, K);
}

inline void Query(int root, int l, int r, int L, int R, int k)
{
    if ( L <= l && r <= R ) 
    {
        for ( auto it : Tree[root].a ) ccc.push_back(it);
        ccc = Solve(ccc, k); return ;
    }
    int Mid = l + r >> 1; 
    if ( L <= Mid ) Query(lson, l, Mid, L, R, k);
    if ( Mid < R ) Query(rson, Mid + 1, r, L, R, k);
}

signed main()
{
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
    REP(i, 1, n) belong[i] = (i - 1) / K + 1;
    for ( int l = 1, r = K; l <= n; l += K, r = min(n, r + K) ) g[belong[l]] = pii(l, r);
    dep[1] = 1; DFS1(1, 0); 

    int m = cnt;
    lg[1] = 0; REP(i, 2, m) lg[i] = lg[i / 2] + 1;
    REP(i, 1, m) st[i][0] = h[i];
    REP(j, 1, 19) REP(i, 1, m - (1 << j) + 1) 
        st[i][j] = dep[st[i][j - 1]] < dep[st[i + (1 << j - 1)][j - 1]] ? st[i][j - 1] : st[i + (1 << j - 1)][j - 1];

    Build(1, 1, belong[n]);
    scanf("%d", &q);
    while ( q -- ) 
    {
        if ( q % 1000 == 0 ) cerr << q << endl;
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        ccc.clear();
        if ( belong[l] == belong[r] ) REP(i, l, r) ccc.push_back(i);
        else 
        {
            Query(1, 1, belong[n], belong[l] + 1, belong[r] - 1, k);
            REP(i, l, g[belong[l]].second) ccc.push_back(i); ccc = Solve(ccc, k);
            REP(i, g[belong[r]].first, r) ccc.push_back(i);
        }
        ans = 0; ccc = Solve(ccc, k);
        printf("%lld\n", ans);
    }
    return 0;
}
