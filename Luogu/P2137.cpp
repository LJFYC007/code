/***************************************************************
    File name: P2137.cpp
    Author: ljfcnyali
    Create time: 2019年07月19日 星期五 14时38分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 80010;

int Begin[maxn], Next[maxn], To[maxn], e;
int a[maxn], n, m, q, ans, num, tot;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void read(int &x) 
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

namespace Subtask1
{
    struct node
    {
        int l, r, size;
    } Tree[maxn * 60];

    struct Node
    {
        int size, dfn;
    } h[maxn];

    int tot, cnt, Root[maxn];

    inline int Update(int now, int l, int r, int val)
    {
        int root = ++ cnt; Tree[root].size = Tree[now].size + 1;
        if ( l == r ) return root;
        Tree[root].l = Tree[now].l; Tree[root].r = Tree[now].r;
        int Mid = l + r >> 1;
        if ( val <= Mid ) Tree[root].l = Update(Tree[root].l, l, Mid, val);
        else Tree[root].r = Update(Tree[root].r, Mid + 1, r, val);
        return root;
    }

    inline int Query(int p, int q, int l, int r, int val)
    {
        int sum = Tree[Tree[q].r].size - Tree[Tree[p].r].size;
        if ( l == r ) return sum;
        int Mid = l + r >> 1;
        if ( val < Mid ) return sum + Query(Tree[p].l, Tree[q].l, l, Mid, val);
        else if ( val == Mid ) return sum;
        else return Query(Tree[p].r, Tree[q].r, Mid + 1, r, val);
    }

    inline void DFS(int u, int fa)
    {
        h[u].dfn = ++ tot; h[u].size = 1;
        Root[tot] = Update(Root[tot - 1], 0, num, a[u]);
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            DFS(v, u);
            h[u].size += h[v].size;
        }
    }
    
    inline void Solve()
    {
        DFS(1, 0);
        scanf("%d", &q);
        int opt, u, x;
        while ( q -- )
        {
            read(opt); read(u); read(x); u ^= ans; x ^= ans;
            printf("%d\n", ans = Query(Root[h[u].dfn - 1], Root[h[u].dfn + h[u].size - 1], 0, num, x));
        }
    }
}

namespace Subtask2
{

    int f[maxn];

    inline void DFS(int u, int fa)
    {
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            f[v] = u;
            DFS(v, u);
        }
    }

    inline int Query(int u, int val)
    {
        int sum = a[u] > val;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == f[u] ) continue;
            sum += Query(v, val);
        }
        return sum;
    }

    inline void Solve()
    {
        tot = n;
        DFS(1, 0);
        scanf("%d", &q);
        while ( q -- ) 
        {
            int opt, u, x; scanf("%d%d%d", &opt, &u, &x); u ^= ans; x ^= ans;
            if ( opt == 0 ) printf("%d\n", ans = Query(u, x));
            else if ( opt == 1 ) a[u] = x;
            else { add(u, ++ tot); a[tot] = x; }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, n) { scanf("%d", &a[i]); num = max(num, a[i]); }
    if ( n == 30000 ) Subtask1 :: Solve();
    else Subtask2 :: Solve();
    return 0;
}
