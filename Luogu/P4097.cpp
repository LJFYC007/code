/***************************************************************
	File name: P4097.cpp
	Author: ljfcnyali
	Create time: 2019年10月15日 星期二 07时39分58秒
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

const int maxn = 5000010;
const int N = 40000;
const long double eps = 1e-10;

struct Line { long double k, b; } ;
struct node { Line x; int id; } Tree[maxn << 2];

int n, ans, id, ID; 
long double Max;

inline long double f(Line x, int pos) { return x.k * pos + x.b; }

inline void Modify(int root, int l, int r, Line x)
{
    if ( !Tree[root].id ) { Tree[root].id = id; Tree[root].x = x; return ; }
    if ( l == r )
    {
        if ( f(Tree[root].x, l) < f(x, l) ) { swap(id, Tree[root].id); Tree[root].x = x; }
        return ;
    }
    int Mid = (l + r) >> 1;
    if ( Tree[root].x.k < x.k ) 
        if ( f(Tree[root].x, Mid) < f(x, Mid) )
        {
            swap(id, Tree[root].id);
            Modify(lson, l, Mid, Tree[root].x);
            Tree[root].x = x;
        }
        else Modify(rson, Mid + 1, r, x);
    if ( Tree[root].x.k >= x.k ) 
        if ( f(Tree[root].x, Mid) < f(x, Mid) )
        {
            swap(id, Tree[root].id);
            Modify(rson, Mid + 1, r, Tree[root].x);
            Tree[root].x = x;
        }
        else Modify(lson, l, Mid, x);
}

inline void Update(int root, int l, int r, int L, int R, Line x)
{
    if ( L <= l && r <= R ) { id = ID; Modify(root, l, r, x); return ; }
    int Mid = (l + r) >> 1;
    if ( L <= Mid ) Update(lson, l, Mid, L, R, x);
    if ( Mid < R ) Update(rson, Mid + 1, r, L, R, x);
}

inline void Query(int root, int l, int r, int pos)
{
    if ( l == r ) 
    {
        if ( Tree[root].id ) 
        {
            long double x = f(Tree[root].x, pos);
            if ( x > Max + eps ) { Max = x; ans = Tree[root].id; }
            else if ( x > Max - eps ) ans = min(ans, Tree[root].id);
            // else if ( x == Max ) ans = min(ans, Tree[root].id);
        }
        return ;
    }
    int Mid = (l + r) >> 1;
    if ( Tree[root].id ) 
    { 
        long double x = f(Tree[root].x, pos); 
        if ( x > Max + eps ) { Max = x; ans = Tree[root].id; } 
        else if ( x > Max - eps ) ans = min(ans, Tree[root].id);
    } 
    if ( pos <= Mid ) Query(lson, l, Mid, pos);
    else Query(rson, Mid + 1, r, pos);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    int tot = 0;
    REP(i, 1, n)
    {
        int opt, x;
        scanf("%lld", &opt);
        if ( opt == 0 ) 
        {
            scanf("%lld", &x); x = (x + ans - 1) % 39989 + 1;
            Max = -0.1; ans = 0; Query(1, 0, N, x);
            printf("%lld\n", ans);
            continue ;
        }
        long double x0, x1, y0, y1;
        scanf("%Lf%Lf%Lf%Lf", &x0, &y0, &x1, &y1);
        x0 = (int)(x0 + ans - 1) % 39989 + 1;
        x1 = (int)(x1 + ans - 1) % 39989 + 1;
        y0 = (int)(y0 + ans - 1) % 1000000000 + 1;
        y1 = (int)(y1 + ans - 1) % 1000000000 + 1;
        ID = ++ tot;
        if ( x0 == x1 ) 
        {
            Line a; a.k = 0; a.b = max(y0, y1);
            Update(1, 0, N, x0, x0, a);
            continue ;
        }
        if ( x0 > x1 ) swap(x0, x1), swap(y0, y1);
        Line a; a.k = (y1 - y0) / (x1 - x0); a.b = y0 - x0 * a.k;
        Update(1, 0, N, x0, x1, a);
    }
    return 0;
}
