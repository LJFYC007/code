/***************************************************************
	File name: P4148.cpp
	Author: ljfcnyali
	Create time: 2019年09月03日 星期二 21时37分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 500010;
const double alpha = 0.75;

int n, ans, Root, tot, k;
stack<int> Rub;

struct point
{
    int x[2], val;
    bool operator < (const point &p) const { return x[k] < p.x[k]; }
} p1, p[maxn];
struct node
{
    int size, sum, lson, rson, Maxx, Maxy, Minx, Miny;
    point p;
} Tree[maxn];

inline int NewNode()
{
    if ( !Rub.empty() ) { int x = Rub.top(); Rub.pop(); return x; }
    return ++ tot;
}

inline void PushUp(int root)
{
    Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1;
    Tree[root].sum = Tree[ls(root)].sum + Tree[rs(root)].sum + Tree[root].p.val;
    Tree[root].Maxx = Tree[root].Minx = Tree[root].p.x[0];
    Tree[root].Maxy = Tree[root].Miny = Tree[root].p.x[1];
    if ( ls(root) ) 
    {
        Tree[root].Maxx = max(Tree[root].Maxx, Tree[ls(root)].Maxx);
        Tree[root].Minx = min(Tree[root].Minx, Tree[ls(root)].Minx);
        Tree[root].Maxy = max(Tree[root].Maxy, Tree[ls(root)].Maxy);
        Tree[root].Miny = min(Tree[root].Miny, Tree[ls(root)].Miny);
    }
    if ( rs(root) ) 
    {
        Tree[root].Maxx = max(Tree[root].Maxx, Tree[rs(root)].Maxx);
        Tree[root].Minx = min(Tree[root].Minx, Tree[rs(root)].Minx);
        Tree[root].Maxy = max(Tree[root].Maxy, Tree[rs(root)].Maxy);
        Tree[root].Miny = min(Tree[root].Miny, Tree[rs(root)].Miny);
    }
}

inline void Access(int root, int num)
{
    if ( ls(root) ) Access(ls(root), num);
    p[Tree[ls(root)].size + num + 1] = Tree[root].p; Rub.push(root);
    if ( rs(root) ) Access(rs(root), Tree[ls(root)].size + num + 1);
}

inline void ReBuild(int &root, int l, int r, int dim)
{
    if ( l > r ) { root = 0; return ; }
    int Mid = l + r >> 1; root = NewNode(); 
    k = dim; nth_element(p + l, p + Mid, p + r + 1);
    Tree[root].p = p[Mid];
    ReBuild(ls(root), l, Mid - 1, dim ^ 1);
    ReBuild(rs(root), Mid + 1, r, dim ^ 1);
    PushUp(root);
}

inline void Check(int &root, int dim)
{
    if ( Tree[root].size * alpha <= Tree[ls(root)].size || Tree[root].size * alpha <= Tree[rs(root)].size ) 
    {
        Access(root, 0);
        ReBuild(root, 1, Tree[root].size, dim);
    }
}

inline void Insert(int &root, point x, int dim)
{
    if ( !root ) 
    {
        root = NewNode(); ls(root) = rs(root) = 0; Tree[root].p = x; 
        PushUp(root); return ;
    }
    if ( x.x[dim] <= Tree[root].p.x[dim] ) Insert(ls(root), x, dim ^ 1);
    else Insert(rs(root), x, dim ^ 1);
    PushUp(root); Check(root, dim);
}

inline bool in(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    return x3 >= x1 && x4 <= x2 && y3 >= y1 && y4 <= y2;
}

inline bool out(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    return x1 > x4 || x2 < x3 || y1 > y4 || y2 < y3;
}

inline int Query(int root, int x1, int y1, int x2, int y2)
{
    if ( !Tree[root].size ) return 0;
    if ( in(x1, y1, x2, y2, Tree[root].Minx, Tree[root].Miny, Tree[root].Maxx, Tree[root].Maxy) ) return Tree[root].sum;
    if ( out(x1, y1, x2, y2, Tree[root].Minx, Tree[root].Miny, Tree[root].Maxx, Tree[root].Maxy) ) return 0;
    int sum = 0;
    if ( in(x1, y1, x2, y2, Tree[root].p.x[0], Tree[root].p.x[1], Tree[root].p.x[0], Tree[root].p.x[1]) ) sum += Tree[root].p.val;
    if ( ls(root) ) sum += Query(ls(root), x1, y1, x2, y2);
    if ( rs(Root) ) sum += Query(rs(root), x1, y1, x2, y2);
    return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    int opt;
    while ( ~scanf("%d", &opt) ) 
    {
        if ( opt == 3 ) break ; 
        if ( opt == 1 ) 
        {
            int x, y, val; scanf("%d%d%d", &x, &y, &val);
            x ^= ans; y ^= ans; val ^= ans;
            p1.x[0] = x; p1.x[1] = y; p1.val = val;
            Insert(Root, p1, 0);
        }
        if ( opt == 2 ) 
        {
            int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            x1 ^= ans; x2 ^= ans; y1 ^= ans; y2 ^= ans;
            ans = Query(Root, x1, y1, x2, y2);
            printf("%d\n", ans);
        }
    }
    return 0;
}
