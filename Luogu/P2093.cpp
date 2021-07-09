/***************************************************************
	File name: P2093.cpp
	Author: ljfcnyali
	Create time: 2020年06月18日 星期四 19时52分53秒
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

const int maxn = 4e5 + 10;
const int INF = 1e9;

int n, m, k, Dim;
struct point { int x, y, id; point(int a = 0, int b = 0, int c = 0 ) { x = a; y = b; id = c; } } a[maxn], p;
struct node { int Minx, Maxx, Miny, Maxy; point x; } Tree[maxn];
inline double Dis(point a, point b) { return sqrt((double)((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y))); }
bool operator < (point a, point b) { return Dis(a, p) > Dis(b, p) || (Dis(a, p) == Dis(b, p) && a.id < b.id); }
priority_queue<point> Q;

inline double Get(int root)
{
    double ans = 0;
    ans = max(ans, Dis(point(Tree[root].Minx, Tree[root].Miny), p));
    ans = max(ans, Dis(point(Tree[root].Maxx, Tree[root].Miny), p));
    ans = max(ans, Dis(point(Tree[root].Minx, Tree[root].Maxy), p));
    ans = max(ans, Dis(point(Tree[root].Maxx, Tree[root].Maxy), p));
    return ans;
}

inline void PushUp(int root)
{
    Tree[root].Minx = min(Tree[root].x.x, min(Tree[lson].Minx, Tree[rson].Minx));
    Tree[root].Maxx = max(Tree[root].x.x, max(Tree[lson].Maxx, Tree[rson].Maxx));
    Tree[root].Miny = min(Tree[root].x.y, min(Tree[lson].Miny, Tree[rson].Miny));
    Tree[root].Maxy = max(Tree[root].x.y, max(Tree[lson].Maxy, Tree[rson].Maxy));
}

inline void Build(int root, int l, int r, int dim)
{
    if ( l > r ) return ;
    if ( l == r ) 
    { 
        Tree[root].x = a[l]; 
        Tree[root].Maxx = Tree[root].Minx = a[l].x;
        Tree[root].Maxy = Tree[root].Miny = a[l].y;
        return ;
    }
    int Mid = l + r >> 1; Dim = dim; 
    nth_element(a + l, a + Mid, a + r + 1, [](const point &a, const point &b){ return Dim == 0 ? a.x < b.x : a.y < b.y; });
    Tree[root].x = a[Mid];
    Build(lson, l, Mid - 1, dim ^ 1);
    Build(rson, Mid + 1, r, dim ^ 1);
    PushUp(root);
}

inline void Query(int root, int l, int r)
{
    if ( l > r ) return ;
    if ( Tree[root].x < Q.top() ) { Q.pop(); Q.push(Tree[root].x); }
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    double ansx = Get(lson), ansy = Get(rson);
    if ( ansx >= ansy )
    {
        if ( ansx >= Dis(Q.top(), p) ) Query(lson, l, Mid - 1);
        if ( ansy >= Dis(Q.top(), p) ) Query(rson, Mid + 1, r);
    }
    else
    {
        if ( ansy >= Dis(Q.top(), p) ) Query(rson, Mid + 1, r);
        if ( ansx >= Dis(Q.top(), p) ) Query(lson, l, Mid - 1);
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld%lld", &a[i].x, &a[i].y); a[i].id = i; }
    REP(i, 1, n * 4)
    {
        Tree[i].Minx = Tree[i].Miny = INF;
        Tree[i].Maxx = Tree[i].Maxy = -INF;
    }
    Build(1, 1, n, 0);
    scanf("%lld", &m);
    while ( m -- ) 
    {
        scanf("%lld%lld%lld", &p.x, &p.y, &k);
        p.id = n + 1;
        while ( !Q.empty() ) Q.pop();
        REP(i, 1, k) Q.push(p);
        Query(1, 1, n);
        printf("%lld\n", Q.top().id);
    }
    return 0;
}
