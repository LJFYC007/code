/***************************************************************
	File name: f.cpp
	Author: ljfcnyali
	Create time: 2019年12月15日 星期日 14时38分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
#define lson root << 1
#define rson root << 1 | 1
#define int long long 
#define inv(x) power(x, Mod - 2);
typedef long long LL;

const int maxn = 2e5 + 10;
const int Mod = 1e9 + 7;

int n, Begin[maxn], Next[maxn], To[maxn], e, size[maxn], dfn[maxn], dis[maxn], p[maxn], id[maxn];
int head[maxn], son[maxn], f[maxn], cnt, tot, ans, N, sum1, sum2, sum3, g[maxn];
vector<int> a[maxn];
struct node { int lazy, sum; } Tree[maxn << 2];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    size[u] = 1; int Max = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        f[v] = u; dis[v] = dis[u] + 1; 
        DFS1(v, u);
        size[u] += size[v];
        if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
    }
}

inline void DFS2(int u, int t)
{
    head[u] = t; p[u] = ++ cnt; id[cnt] = u;
    if ( son[u] ) DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == f[u] || v == son[u] ) continue ;
        DFS2(v, v);
    }
}

inline void PushUp(int root) { Tree[root].sum = (Tree[lson].sum + Tree[rson].sum) % Mod; }

inline void PushTag(int root, int l, int r, int val) 
{ 
    Tree[root].lazy = (Tree[root].lazy + val) % Mod; 
    Tree[root].sum = (Tree[root].sum + (r - l + 1) * val) % Mod;
}

inline void PushDown(int root, int l, int r)
{
    if ( !Tree[root].lazy ) return ;
    int Mid = l + r >> 1;
    PushTag(lson, l, Mid, Tree[root].lazy);
    PushTag(rson, Mid + 1, r, Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Modify2(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, l, r, val); return ; }
    PushDown(root, l, r);
    int Mid = l + r >> 1;
    if ( L <= Mid ) Modify2(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify2(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Query2(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    PushDown(root, l, r);
    int Mid = l + r >> 1, ret = 0;
    if ( L <= Mid ) ret += Query2(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query2(rson, Mid + 1, r, L, R);
    return ret % Mod;
}

inline void Modify1(int x, int val)
{
    while ( x ) { Modify2(1, 1, n, p[head[x]], p[x], val); x = f[head[x]]; }
}

inline int Query1(int x)
{
    int ret = 0;
    while ( x ) { ret += Query2(1, 1, n, p[head[x]], p[x]); x = f[head[x]]; }
    return ret % Mod;
}

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("f.in", "r", stdin);
    freopen("f.out", "w", stdout);
#endif
    scanf("%lld", &n); 
    int sum = 1;
    REP(i, 1, n) 
    { 
        int x, y; scanf("%lld%lld", &x, &y); 
        g[i] = y - x + 1; sum = sum * g[i] % Mod; g[i] = inv(g[i]);
        a[x].push_back(i); a[y + 1].push_back(-i); N = max(N, y); 
    }
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS1(1, 0); DFS2(1, 1);
    int ret = 0;
    REP(i, 1, N) 
    {
        for ( int j : a[i] ) 
        {
            int x = j;
            if ( x > 0 ) 
            {
                sum1 = (sum1 + dis[x] * g[x] % Mod) % Mod;
                sum2 = (sum2 + g[x]) % Mod;
                sum3 = (sum3 + (dis[x] * g[x] % Mod) * g[x] % Mod) % Mod;
                ret = (ret + g[x] * Query1(x)) % Mod;
                Modify1(x, g[x]);
            }
            else
            {
                x = -x;
                sum1 = (sum1 - dis[x] * g[x] % Mod) % Mod;
                sum2 = (sum2 - g[x]) % Mod;
                sum3 = (sum3 - (dis[x] * g[x] % Mod) * g[x] % Mod) % Mod;
                Modify1(x, Mod - g[x]);
                ret = (ret - g[x] * Query1(x)) % Mod;
            }
        }
        ans = (ans + (sum1 * sum2 % Mod) - sum3 - 2 * ret) % Mod;
    }
    ans = (ans + Mod) % Mod;
    printf("%lld\n", sum * ans % Mod);
    return 0;
}
