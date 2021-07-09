/***************************************************************
	File name: minmax.cpp
	Author: ljfcnyali
	Create time: 2020年10月08日 星期四 16时39分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 2e5 + 10;

int n, k; LL ans;
struct node { int u, v, w; } Edge[maxn];
struct HaHa 
{
    struct Node { vector<int> a; int sum; } Tree[maxn << 2];
    int f[maxn], size[maxn];

    inline int find(int x) { return x == f[x] ? x : find(f[x]); }

    inline void Modify(int root, int l, int r, int L, int R, int x)
    {
        L = max(L, 1); if ( L > R ) return ;
        if ( L <= l && r <= R ) { Tree[root].a.push_back(x); return ; }
        int Mid = l + r >> 1;
        if ( L <= Mid ) Modify(lson, l, Mid, L, R, x);
        if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, x);
    }

    inline void add(int root, int l, int r, int pos, int val)
    {
        if ( l == r ) { Tree[root].sum += val; return ; }
        int Mid = l + r >> 1;
        if ( pos <= Mid ) add(lson, l, Mid, pos, val);
        else add(rson, Mid + 1, r, pos, val);
    }
    struct NODE
    {
        int id, f, size; 
        NODE ( int a = 0, int b = 0, int c = 0 ) { id = a; f = b; size = c; }
    } ;

    inline void Query(int root, int l, int r, LL sum)
    {
        vector<NODE> p; p.clear();
        for ( auto it : Tree[root].a ) 
        {
            int fx = find(Edge[it].u), fy = find(Edge[it].v);
            if ( fx == fy ) continue ;
            if ( size[fx] > size[fy] ) swap(fx, fy);
            p.push_back(NODE(fx, f[fx], size[fx]));
            p.push_back(NODE(fy, f[fy], size[fy]));
            sum += 1ll * size[fx] * size[fy];
            f[fx] = fy; size[fy] += size[fx];
        }
        if ( l == r ) ans += Tree[root].sum * sum; 
        else { int Mid = l + r >> 1; Query(lson, l, Mid, sum); Query(rson, Mid + 1, r, sum); }
        for ( int i = (int)p.size() - 1; i >= 0; -- i ) 
        {
            f[p[i].id] = p[i].f;
            size[p[i].id] = p[i].size;
        }
    }

    inline void Solve()
    {
        REP(i, 1, n) { f[i] = i; size[i] = 1; }
        Query(1, 1, n, 0);
    }
} A, B, C;

inline void Solve(int k)
{
    REP(i, 1, n - 1) 
    {
        A.Modify(1, 1, n, Edge[i].w - k, Edge[i].w, i);
        B.Modify(1, 1, n, Edge[i].w - k + 1, Edge[i].w, i);
        C.Modify(1, 1, n, Edge[i].w - k + 2, Edge[i].w, i);
    }
    REP(i, 1, n - k)
    {
        A.add(1, 1, n, i, 1);
        B.add(1, 1, n, i, -1); B.add(1, 1, n, i + 1, -1);
        C.add(1, 1, n, i + 1, 1);
    }
    A.Solve(); B.Solve(); C.Solve();
}

int main()
{
    freopen("minmax.in", "r", stdin);
    freopen("minmax.out", "w", stdout);
    scanf("%d%d", &n, &k);
    REP(i, 1, n - 1) scanf("%d%d%d", &Edge[i].u, &Edge[i].v, &Edge[i].w);
    Solve(k);
    printf("%lld\n", ans);
    return 0;
}
