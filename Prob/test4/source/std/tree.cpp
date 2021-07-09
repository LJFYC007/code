/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2019年10月09日 星期三 08时08分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 800010;
const int Mod = 1e9 + 7;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, ans;
int a[maxn], dis[maxn], f[maxn], top[maxn], son[maxn], size[maxn];
int sum1, sum2, p[maxn], id[maxn], cnt, num1, num2;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

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

struct TREE
{
#define lson (root << 1)
#define rson (root << 1 | 1)
    struct node
    {
        int sum, lazy, len;
    } Tree[maxn << 2];

    inline void PushUp(int root) { Tree[root].sum = (Tree[lson].sum + Tree[rson].sum) % Mod; }

    inline void PushDown(int root)
    {
        if ( !Tree[root].lazy ) return ;
        int x = Tree[root].lazy; Tree[root].lazy = 0;
        Tree[lson].sum = (Tree[lson].sum + Tree[lson].len * x) % Mod;
        Tree[rson].sum = (Tree[rson].sum + Tree[rson].len * x) % Mod;
        Tree[lson].lazy = (Tree[lson].lazy + x) % Mod;
        Tree[rson].lazy = (Tree[rson].lazy + x) % Mod;
    }

    inline void Build(int root, int l, int r)
    {
        Tree[root].len = r - l + 1;
        if ( l == r ) return ;
        int Mid = l + r >> 1;
        Build(lson, l, Mid); Build(rson, Mid + 1, r);
    }

    inline void Modify(int root, int l, int r, int L, int R, int val)
    {
        if ( L <= l && r <= R ) 
        { 
            Tree[root].sum = (Tree[root].sum + Tree[root].len * val) % Mod; 
            Tree[root].lazy = (Tree[root].lazy + val) % Mod;
            return ; 
        }
        PushDown(root);
        int Mid = l + r >> 1;
        if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
        if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
        PushUp(root);
    }

    inline int Query(int root, int l, int r, int L, int R)
    {
        if ( L > R ) return 0;
        if ( L <= l && r <= R ) return Tree[root].sum;
        PushDown(root);
        int Mid = l + r >> 1, sum = 0;
        if ( L <= Mid ) sum += Query(lson, l, Mid, L, R);
        if ( Mid < R ) sum += Query(rson, Mid + 1, r, L, R);
        return sum % Mod;
    }

    inline void Update(int x, int val)
    {
        while ( top[x] != 1 ) 
        {
            Modify(1, 1, n, id[top[x]], id[x], val);
            x = f[top[x]];
        }
        Modify(1, 1, n, id[1], id[x], val);
    }

    inline int Query1(int x)
    {
        int sum = 0;
        while ( top[x] != 1 ) 
        {
            sum = (sum + Query(1, 1, n, id[top[x]], id[x])) % Mod;
            x = f[top[x]];
        }
        sum = (sum + Query(1, 1, n, id[1], id[x])) % Mod;
        return sum;
    }
} Black, White;

signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    n = 2 * n;
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, n) scanf("%lld", &a[i]);
    dis[1] = 1; DFS1(1, 0); DFS2(1, 1);
    Black.Build(1, 1, n); White.Build(1, 1, n);
    REP(i, 1, n)
    {
        if ( a[i] ) 
        {
            ++ num2; sum2 = (sum2 + dis[i]) % Mod;
            Black.Update(i, 1);
            continue ;
        }
        ++ num1; sum1 = (sum1 + dis[i]) % Mod;
        White.Update(i, 1);
    }
    REP(i, 1, n) 
        if ( a[i] ) ans = (ans + sum2 + num2 * dis[i] - 2 * Black.Query1(i)) % Mod;
        else ans = (ans + sum1 + num1 * dis[i] - 2 * White.Query1(i)) % Mod;
    ans = (ans * 500000004ll) % Mod; printf("%lld\n", ans);
    REP(i, 1, m)
    {
        int x; scanf("%lld", &x); 
        if ( a[x] ) 
        { 
            ans = (ans - sum2 - num2 * dis[x] + 2 * Black.Query1(x)) % Mod; 
            sum2 -= dis[x]; -- num2; 
            Black.Update(x, -1); White.Update(x, 1);
        }
        else 
        { 
            ans = (ans - sum1 - num1 * dis[x] + 2 * White.Query1(x)) % Mod; 
            sum1 -= dis[x]; -- num1; 
            White.Update(x, -1); Black.Update(x, 1);
        }
        a[x] ^= 1;
        if ( a[x] ) { ++ num2; sum2 += dis[x]; ans = (ans + sum2 + num2 * dis[x] - 2 * Black.Query1(x)) % Mod; }
        else { ++ num1; sum1 += dis[x]; ans = (ans + sum1 + num1 * dis[x] - 2 * White.Query1(x)) % Mod; }
        sum1 %= Mod; sum2 %= Mod;
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
