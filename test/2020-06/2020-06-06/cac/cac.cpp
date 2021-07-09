/***************************************************************
	File name: cac.cpp
	Author: ljfcnyali
	Create time: 2020年06月06日 星期六 11时35分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 998244353;

int N, n, m, q, Begin[maxn], Next[maxn], To[maxn], e, cur;
int dfn[maxn], low[maxn], tot, top, Stack[maxn], a[maxn], b[maxn];
vector<int> Edge[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int lowbit(int x) { return x & -x; }

inline void Modify(int pos, int val) { for ( int i = pos; i <= N; i += lowbit(i) ) b[i] = (b[i] + val) % Mod; }

inline int Query(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += b[i]; return sum % Mod; } 

inline void Tarjan(int u)
{
    dfn[u] = low[u] = ++ tot; Stack[++ top] = u;
    for ( auto v : Edge[u] ) 
        if ( !dfn[v] ) 
        {
            Tarjan(v); low[u] = min(low[u], low[v]); 
            if ( low[v] == dfn[u] ) 
            {
                ++ cur;
                for ( int x = 0; x != v; -- top ) { x = Stack[top]; add(x, cur); add(cur, x);  }
                add(u, cur); add(cur, u);
            }
        }
        else low[u] = min(low[u], dfn[v]);
}

namespace SplitTree
{
    int f[maxn], dis[maxn], size[maxn], top[maxn], son[maxn], p[maxn], id[maxn], tot;

    inline int Solve(int u, int v, int w)
    {
        while ( top[u] != top[v] ) 
        {
            if ( dis[top[u]] < dis[top[v]] ) swap(u, v);
            Modify(p[top[u]], w); Modify(p[u] + 1, -w);
            u = f[top[u]];
        }
        if ( dis[u] > dis[v] ) swap(u, v);
        Modify(p[u], w); Modify(p[v] + 1, -w);
        return u;
    }

    inline void DFS1(int u, int fa)
    {
        size[u] = 1;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            dis[v] = dis[u] + 1; f[v] = u;
            DFS1(v, u); size[u] += size[v];
            if ( size[v] > size[son[u]] ) son[u] = v;
        }
    }

    inline void DFS2(int u, int t)
    {
        top[u] = t; p[u] = ++ tot; id[tot] = u;
        if ( son[u] ) DFS2(son[u], t);
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
            DFS2(v, v);
        }
    }

    inline void INIT() { dis[1] = 1; DFS1(1, 0); DFS2(1, 1); }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("cac.in", "r", stdin);
    freopen("cac.out", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &q);
    REP(i, 1, m) 
    { 
        int u, v; scanf("%lld%lld", &u, &v); 
        Edge[u].push_back(v); Edge[v].push_back(u); 
    }
    cur = n; Tarjan(1); N = cur; SplitTree :: INIT();
    while ( q -- ) 
    {
        int op; scanf("%lld", &op);
        if ( op == 0 )
        {
            int u, v, w; scanf("%lld%lld%lld", &u, &v, &w);
            int t = SplitTree :: Solve(u, v, w), f = SplitTree :: f[t];
            if ( t > n && f <= n && f ) a[f] += w;
            if ( t <= n && (f > n || !f) ) a[t] += w;
        }
        else 
        {
            int x; scanf("%lld", &x);
            int ret = a[x], t = SplitTree :: f[x];
            if ( t > n ) ret += Query(SplitTree :: p[t]);
            ret %= Mod;
            printf("%lld\n", (ret + Mod) % Mod);
        }
    }
    return 0;
}
