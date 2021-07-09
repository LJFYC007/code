/***************************************************************
	File name: P3769.cpp
	Author: ljfcnyali
	Create time: 2019年09月04日 星期三 12时37分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int long long
typedef long long LL;

const int maxn = 2000010;
const double alpha = 0.75;
const int INF = 10000000000000;

int n, tot, k, ans, Root, MAX;
stack<int> Rub;
struct point
{
    int x[4], val;
    bool operator < (const point &a) const { return x[k] < a.x[k]; }
} a[maxn], p[maxn], p1;
struct node
{
    int size, lson, rson, Max;
    point x, a, b;
} Tree[maxn];

inline int NewNode()
{
    if ( !Rub.empty() ) { int x = Rub.top(); Rub.pop(); return x; }
    return ++ tot;
}

inline void PushUp(int root)
{
    Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1;
    Tree[root].Max = Tree[root].x.val; 
    Tree[root].a = Tree[root].b = Tree[root].x;
    if ( ls(root) ) Tree[root].Max = max(Tree[root].Max, Tree[ls(root)].Max);
    if ( rs(root) ) Tree[root].Max = max(Tree[root].Max, Tree[rs(root)].Max);
    REP(i, 0, 2)
    {
        if ( ls(root) ) 
        {
            Tree[root].a.x[i] = min(Tree[root].a.x[i], Tree[ls(root)].a.x[i]);
            Tree[root].b.x[i] = max(Tree[root].b.x[i], Tree[ls(root)].b.x[i]);
        }
        if ( rs(root) ) 
        {
            Tree[root].a.x[i] = min(Tree[root].a.x[i], Tree[rs(root)].a.x[i]);
            Tree[root].b.x[i] = max(Tree[root].b.x[i], Tree[rs(root)].b.x[i]);
        }
    }
}

inline void Access(int root, int num)
{
    if ( ls(root) ) Access(ls(root), num);
    p[Tree[ls(root)].size + num + 1] = Tree[root].x; Rub.push(root);
    if ( rs(root) ) Access(rs(root), Tree[ls(root)].size + num + 1);
}

inline void ReBuild(int &root, int l, int r, int dim)
{
    if ( l > r ) { root = 0; return ; }
    int Mid = l + r >> 1; root = NewNode(); 
    k = dim; nth_element(p + l, p + Mid, p + r + 1);
    Tree[root].x = p[Mid];
    ReBuild(ls(root), l, Mid - 1, (dim + 1) % 3); 
    ReBuild(rs(root), Mid + 1, r, (dim + 1) % 3);
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
        root = NewNode(); ls(root) = rs(root) = 0; Tree[root].x = x;
        PushUp(root); return ;
    }
    if ( x.x[dim] <= Tree[root].x.x[dim] ) Insert(ls(root), x, (dim + 1) % 3);
    else Insert(rs(root), x, (dim + 1) % 3);
    PushUp(root); Check(root, dim);
}

inline bool in(point a, point b, point c, point d)
{
    REP(i, 0, 2)
        if ( !(a.x[i] <= c.x[i] && d.x[i] <= b.x[i]) ) return false;
    return true;
}

inline bool out(point a, point b, point c, point d)
{
    REP(i, 0, 2)
        if ( a.x[i] > d.x[i] || b.x[i] < c.x[i] ) return true;
    return false;
}

inline void Query(int root, point x, point y)
{
    if ( !root ) return ;
    if ( Tree[root].Max <= MAX ) return ;
    if ( out(x, y, Tree[root].a, Tree[root].b) ) return ;
    if ( in(x, y, Tree[root].a, Tree[root].b) ) { MAX = max(MAX, Tree[root].Max); return ; }
    if ( in(x, y, Tree[root].x, Tree[root].x) ) MAX = max(MAX, Tree[root].x.val);
    Query(ls(root), x, y); Query(rs(root), x, y);
}

inline bool cmp(point a, point b)
{
    return a.x[3] < b.x[3] || (a.x[3] == b.x[3] && (a.x[0] < b.x[0] || (a.x[0] == b.x[0] && (a.x[1] < b.x[1] || (a.x[1] == b.x[1] && a.x[2] < b.x[2])))));
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) REP(j, 0, 3) scanf("%lld", &a[i].x[j]);
    sort(a + 1, a + n + 1, cmp);
    p1.x[0] = p1.x[1] = p1.x[2] = -INF;
    REP(i, 1, n)
    {
        MAX = 0; Query(Root, p1, a[i]); ++ MAX;
        a[i].val = MAX;
        Insert(Root, a[i], 0);
        ans = max(ans, MAX);
    }
    printf("%lld\n", ans);
    return 0;
}
