/***************************************************************
	File name: H.cpp
	Author: ljfcnyali
	Create time: 2020年10月14日 星期三 21时58分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 2e5 + 10;
const double eps = 1e-12;
const double INF = 1e18;

int n, L, Root, tot;
double ans;
struct node 
{ 
    int l, r; double v; 
    node(int a = 0, int b = 0, double c = 0) { l = a; r = b; v = c; }
    bool operator < (const node &a) const { return v < a.v; }
} a[maxn * 2];
vector<node> p;
struct Node { int lson, rson; double lazy, Min; } Tree[maxn * 50];

inline void PushTag(int &root, double val) 
{ 
    if ( !root ) root = ++ tot;
    Tree[root].lazy += val; Tree[root].Min += val;
}

inline void PushDown(int root)
{
    if ( Tree[root].lazy > -eps && Tree[root].lazy < eps ) return ;
    PushTag(ls(root), Tree[root].lazy);
    PushTag(rs(root), Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Modify(int &root, int l, int r, int L, int R, double val)
{
    if ( !root ) root = ++ tot;
    if ( L <= l && r <= R ) { PushTag(root, val); return ; } 
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(ls(root), l, Mid, L, R, val);
    if ( Mid < R ) Modify(rs(root), Mid + 1, r, L, R, val);
    Tree[root].Min = min(Tree[ls(root)].Min, Tree[rs(root)].Min);
}

inline double Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].Min;
    int Mid = l + r >> 1; double ret = INF; PushDown(root);
    if ( L <= Mid ) ret = min(ret, Query(ls(root), l, Mid, L, R));
    if ( Mid < R ) ret = min(ret, Query(rs(root), Mid + 1, r, L, R));
    return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &L);
    REP(i, 1, n) 
    {
        scanf("%d%d%lf", &a[i].l, &a[i].r, &a[i].v); a[i].v += 1;
        p.push_back(a[i]);
        if ( a[i].l > a[i - 1].r ) p.push_back(node(a[i - 1].r, a[i].l, 1));
    }
    if ( a[n].r < L ) p.push_back(node(a[n].r, L, 1)); 
    sort(p.begin(), p.end());
    for ( auto it : p ) 
    {
        if ( it.v < 1 + eps ) { ans += it.r - it.l; continue ; }
        double slope = (it.r - it.l) / (it.v - 1);
        ans += (it.r - it.l + slope) / it.v;
        Modify(Root, 0, L, it.r, L, slope);
    }
    // cout << ans << endl;
    for ( auto it : p ) 
    {
        double slope = 0;
        if ( it.v > 1 + eps ) slope = (it.r - it.l) / (it.v - 1);
        double Minslope = (it.r - it.l) / (-1 - it.v);
        double Min = Query(Root, 0, L, it.r, L);
        double x = slope - Minslope;
        if ( x <= Min ) { ans -= x / it.v; Modify(Root, 0, L, it.r, L, -x); }
        else { ans -= Min / it.v; Modify(Root, 0, L, it.r, L, -Min); }
        // cout << ans << endl;
    }
    printf("%.9lf\n", ans);
    return 0;
}
