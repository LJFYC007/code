/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2020年01月14日 星期二 21时06分47秒
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

int n, m, k, last[maxn], ans[maxn], f[maxn], size[maxn];
struct Node { int u, v; } a[maxn];
struct NODE { int A, B, sizeA, sizeB; } p1, p2;
struct node { vector<int> p; vector<NODE> a; } Tree[maxn << 2];

inline int find(int x) { return x == f[x] ? x : find(f[x]); }

inline void Modify(int root, int l, int r, int L, int R, int x)
{
    // cerr << root << " " << l  << " " << r << " " << L << " " << R << endl;
    if ( L <= l && r <= R ) { Tree[root].p.push_back(x); return ; }
    int Mid = l + r >> 1;
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, x);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, x);
}

inline void Solve(int root, int l, int r)
{
    for ( auto i : Tree[root].p )    
    {
        int fx = find(a[i].u), fy = find(a[i].v);
        if ( fx == fy ) continue ;
        if ( size[fx] > size[fy] ) swap(fx, fy); 
        p1.A = fx; p1.B = fy; p1.sizeA = size[fx]; p1.sizeB = size[fy];
        Tree[root].a.push_back(p1);
        f[fx] = fy; size[fy] += size[fx];
    }
    if ( l == r ) 
    {
        int x = find(1);
        if ( size[x] == n ) ans[l] = 1;
        else ans[l] = -1;
    }
    else
    {
        int Mid = l + r >> 1;
        Solve(lson, l, Mid); Solve(rson, Mid + 1, r);
    }
    for ( int i = Tree[root].a.size() - 1; i >= 0; -- i )
    {
        p1 = Tree[root].a[i];
        f[p1.A] = p1.A; size[p1.B] = p1.sizeB;
    }
}

int main()
{
    freopen("disconnected.in", "r", stdin);
    freopen("disconnected.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { f[i] = i; size[i] = 1; }
    REP(i, 1, m) scanf("%d%d", &a[i].u, &a[i].v);
    scanf("%d", &k);
    REP(i, 1, k)  
    {
        int c; scanf("%d", &c);
        REP(j, 1, c) 
        {
            int x; scanf("%d", &x); 
            if ( last[x] + 1 <= i - 1 ) Modify(1, 1, k, last[x] + 1, i - 1, x); 
            last[x] = i; 
        }
    } 
    REP(i, 1, m) if ( last[i] + 1 <= k ) Modify(1, 1, k, last[i] + 1, k, i);
    Solve(1, 1, k);  
    REP(i, 1, k) if ( ans[i] == 1 ) puts("Connected"); else puts("Disconnected");
    return 0;
}
