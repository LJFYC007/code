/***************************************************************
	File name: fibonacci.cpp
	Author: ljfcnyali
	Create time: 2020年05月03日 星期日 13时48分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

struct type
{
    int a, b;
    type(int x = 0, int y = 0) { a = x; b = y; }
} p1, p2;
type operator + (const type x, const type y) { return type((x.a + y.a) % Mod, (x.b + y.b) % Mod); }
type operator - (const type x, const type y) { return type((x.a - y.a) % Mod, (x.b - y.b) % Mod); }
type operator * (const type x, const type y) { return type((x.a * y.a + 5 * x.b * y.b) % Mod, (x.a * y.b + x.b * y.a) % Mod); }
type operator + (const type x, const int y) { return type((x.a + y) % Mod, x.b); }
type operator - (const type x, const int y) { return type((x.a - y) % Mod, x.b); }
type operator * (const type x, const int y) { return type(x.a * y % Mod, x.b * y % Mod); }

inline int power1(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline type power2(type a, int b) { type r = type(1, 0); while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; } return r; }

inline type Inv(type x) { return type(x.a, -x.b) * power1((x.a * x.a - 5 * x.b * x.b) % Mod, Mod - 2); }

struct node { type sum1, lazy1, val1, sum2, lazy2, val2; bool vis; } Tree[maxn << 2];
int n, m, Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], top[maxn];
int size[maxn], son[maxn], dfn[maxn], id[maxn], tot, f[maxn];
char s[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; 
        DFS1(v, u);
        size[u] += size[v]; if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
    }
}

inline void DFS2(int u, int t)
{
    dfn[u] = ++ tot; id[tot] = u; top[u] = t;
    if ( son[u] ) DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == son[u] || v == f[u] ) continue ;
        DFS2(v, v);
    }
}

inline void PushTag(int root, type x, type y)
{
    Tree[root].vis = true;
    Tree[root].sum1 = Tree[root].sum1 + Tree[root].val1 * x;
    Tree[root].sum2 = Tree[root].sum2 + Tree[root].val2 * y;
    Tree[root].lazy1 = Tree[root].lazy1 + x;
    Tree[root].lazy2 = Tree[root].lazy2 + y;
}

inline void PushDown(int root)
{
    if ( !Tree[root].vis ) return ;
    Tree[root].vis = false;
    PushTag(lson, Tree[root].lazy1, Tree[root].lazy2);
    PushTag(rson, Tree[root].lazy1, Tree[root].lazy2);
    Tree[root].lazy1 = Tree[root].lazy2 = type(0, 0);
}

inline void PushUp(int root)
{
    Tree[root].sum1 = Tree[lson].sum1 + Tree[rson].sum1;
    Tree[root].sum2 = Tree[lson].sum2 + Tree[rson].sum2;
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].val1 = power2(p1, dis[id[l]]); Tree[root].val2 = power2(p2, dis[id[l]]); return ; }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Tree[root].val1 = Tree[lson].val1 + Tree[rson].val1;
    Tree[root].val2 = Tree[lson].val2 + Tree[rson].val2;
}

inline void Modify(int root, int l, int r, int L, int R, type x, type y)
{
    if ( L <= l && r <= R ) { PushTag(root, x, y); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, x, y);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, x, y);
    PushUp(root);
}

inline type Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum1 - Tree[root].sum2;
    int Mid = l + r >> 1; type ans = (0, 0); PushDown(root);
    if ( L <= Mid ) ans = ans + Query(lson, l, Mid, L, R);
    if ( Mid < R ) ans = ans + Query(rson, Mid + 1, r, L, R);
    return ans;
}

inline int Solve(int u, int v)
{
    type ans = (0, 0);
    while ( top[u] != top[v] ) 
    {
        if ( dis[top[u]] < dis[top[v]] ) swap(u, v);
        ans = ans + Query(1, 1, n, dfn[top[u]], dfn[u]);
        u = f[top[u]];
    }
    if ( dis[u] > dis[v] ) swap(u, v);
    ans = ans + Query(1, 1, n, dfn[u], dfn[v]);
    return ans.b;
}

signed main()
{
    freopen("fibonacci.in", "r", stdin);
    freopen("fibonacci.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 2, n) { scanf("%lld", &f[i]); add(f[i], i); }
    p1 = type(1, 1) * power1(2, Mod - 2); p2 = type(1, -1) * power1(2, Mod - 2);
    dis[1] = 1; DFS1(1, 0); DFS2(1, 1); Build(1, 1, n);
    while ( m -- ) 
    {
        scanf("%s", s + 1);
        if ( s[1] == 'U' ) 
        {
            int u, k; scanf("%lld%lld", &u, &k); k -= dis[u];
            Modify(1, 1, n, dfn[u], dfn[u] + size[u] - 1, k >= 0 ? power2(p1, k) : power2(Inv(p1), -k), k >= 0 ? power2(p2, k) : power2(Inv(p2), -k)); 
        }
        else 
        {
            int u, v; scanf("%lld%lld", &u, &v);
            printf("%lld\n", (Solve(u, v) + Mod) % Mod);
        }
    }
    return 0;
}
