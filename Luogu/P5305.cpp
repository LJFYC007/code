/***************************************************************
	File name: P5305.cpp
	Author: ljfcnyali
	Create time: 2019年10月16日 星期三 16时28分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1000010;
const int Mod = 998244353;

int n, m, k, Begin[maxn], Next[maxn], To[maxn], e, ans[maxn];
int dis[maxn], son[maxn], size[maxn], top[maxn], id[maxn], p[maxn], f[maxn], cnt;
pair<int, pii> q[maxn];
struct node
{
    int sum, lazy, val;
} Tree[maxn << 2];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int power(int a, int b)
{
    int r = 1; 
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

inline void DFS1(int u, int fa)
{
    size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; f[v] = u;
        DFS1(v, u);
        size[u] += size[v];
        if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
    }
}

inline void DFS2(int u, int t)
{
    id[u] = ++ cnt; p[cnt] = u; top[u] = t;
    if ( son[u] ) DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
        DFS2(v, v);
    }
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) 
    { 
        Tree[root].val = (power(dis[p[l]], k) - power(dis[p[l]] - 1, k) + Mod) % Mod; 
        return ; 
    }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Tree[root].val = Tree[lson].val + Tree[rson].val % Mod;
}

inline void PushUp(int root) { Tree[root].sum = Tree[lson].sum + Tree[rson].sum; }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    int x = Tree[root].lazy; Tree[root].lazy = 0;
    Tree[lson].lazy += x; Tree[rson].lazy += x;
    Tree[lson].sum = (Tree[lson].sum + Tree[lson].val * x) % Mod;
    Tree[rson].sum = (Tree[rson].sum + Tree[rson].val * x) % Mod;
}

inline void Modify(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) 
    {
        ++ Tree[root].lazy; Tree[root].sum = Tree[root].sum + Tree[root].val % Mod;
        return ;
    }
    PushDown(root);
    int Mid = l + r >> 1;
    if ( L <= Mid ) Modify(lson, l, Mid, L, R);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    PushDown(root);
    int Mid = l + r >> 1, sum = 0;
    if ( L <= Mid ) sum += Query(lson, l, Mid, L, R);
    if ( Mid < R ) sum += Query(rson, Mid + 1, r, L, R);
    return sum % Mod;
}

inline void Update(int x)
{
    while ( top[x] ) { Modify(1, 1, n, id[top[x]], id[x]); x = f[top[x]]; }
}

inline int Solve(int x)
{
    int sum = 0;
    while ( top[x] ) { sum = (sum + Query(1, 1, n, id[top[x]], id[x])) % Mod; x = f[top[x]]; }
    return sum;
}

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &k); k %= Mod - 1;
    REP(i, 2, n) 
    { 
        int u; scanf("%lld", &u); 
        add(u, i); add(i, u); 
    }
    dis[1] = 1; DFS1(1, 0); DFS2(1, 1); Build(1, 1, n);
    REP(i, 1, m) { int x, y; read(x); read(y); q[i] = make_pair(x, make_pair(y, i)); }
    sort(q + 1, q + m + 1);
    int now = 1;
    REP(i, 1, n)
    {
        Update(i);
        while ( q[now].first == i && now <= m ) 
        {
            ans[q[now].second.second] = Solve(q[now].second.first);
            ++ now;
        }
    }
    REP(i, 1, m) printf("%lld\n", ans[i]);
    return 0;
}
