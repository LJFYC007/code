#include "average.h"
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<LL, LL>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define x first 
#define y second
typedef long long LL;

const int maxn = 2e5 + 10;
const double N = 2e14;

LL sum;
int n = maxn - 10, m, tot, Root[maxn * 4];
struct node { pii line; int lson, rson; bool flag; } Tree[maxn * 80];

inline double f(pii line, double x) { return line.x * x + line.y; }

inline double g(pii line, double x, double y) { return (x + line.y) / (y - line.x); }

inline void Modify1(int &root, double l, double r, pii x, int dep)
{
    if ( dep > 70 ) return ; if ( !root ) root = ++ tot;
    if ( !Tree[root].flag ) { Tree[root].flag = true; Tree[root].line = x; return ; }
    double Mid = (l + r) / 2.0;
    if ( f(x, Mid) > f(Tree[root].line, Mid) ) swap(Tree[root].line, x);
    if ( x.x < Tree[root].line.x ) Modify1(ls(root), l, Mid, x, dep + 1);
    else Modify1(rs(root), Mid, r, x, dep + 1);
}

inline double Query1(int root, double l, double r, double x, double y, int dep)
{
    if ( dep > 70 ) return l;
    if ( !Tree[root].flag || !root ) return 0;
    double Mid = (l + r) / 2.0, val = g(Tree[root].line, x, -y);
    if ( val < Mid ) return max(val, Query1(ls(root), l, Mid, x, y, dep + 1));
    return max(val, Query1(rs(root), Mid, r, x, y, dep + 1));
}

inline void Modify2(int root, int l, int r, int pos, pii x)
{
    Modify1(Root[root], 0, N, x, 0);
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify2(root << 1, l, Mid, pos, x);
    else Modify2(root << 1 | 1, Mid + 1, r, pos, x);
}

inline double Query2(int root, int l, int r, int L, int R, pii x)
{
    if ( L <= l && r <= R ) return Query1(Root[root], 0, N, x.x, x.y, 0);
    int Mid = l + r >> 1; double ans = 0;
    if ( L <= Mid ) ans = max(ans, Query2(root << 1, l, Mid, L, R, x));
    if ( Mid < R ) ans = max(ans, Query2(root << 1 | 1, Mid + 1, r, L, R, x));
    return ans;
}

void init()  { }

void addMonth(int K) 
{
    pii x = pii(-n - 1 + m, -sum); 
    sum += K; Modify2(1, 0, n, m, x); ++ m;
}

double maximumAverage(int L, int R) 
{
    return Query2(1, 0, n, L, R, pii(sum, n + 1 - m));
}
