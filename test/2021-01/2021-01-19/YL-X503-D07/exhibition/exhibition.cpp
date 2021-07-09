/***************************************************************
	File name: exhibition.cpp
	Author: ljfcnyali
	Create time: 2021年01月19日 星期二 09时57分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const int N = 1e9;

int n, f[maxn], num, Root, tot;
pii dis[maxn];
struct node { int l, r, id; } a[maxn];
struct Node { int lson, rson; pii Min, Minn; } Tree[maxn << 5];
bool flag = true;
LL ans;

pii operator +(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii operator -(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
inline pii min(pii a, pii b) { return a.x < b.x ? a : b; }
inline void chkmin(pii &a, pii b) { a = min(a, b); }
inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

inline void Merge(pii a, pii b, pii c, pii d, pii &x, pii &y)
{
    x = min(a, c); y = pii(INF, 0);
    if ( a.y != x.y ) chkmin(y, a); if ( b.y != x.y ) chkmin(y, b);
    if ( c.y != x.y ) chkmin(y, c); if ( d.y != x.y ) chkmin(y, d);
}

inline void PushUp(int root) { Merge(Tree[ls(root)].Min, Tree[ls(root)].Minn, Tree[rs(root)].Min, Tree[rs(root)].Minn, Tree[root].Min, Tree[root].Minn); }

inline void Modify(int &root, int l, int r, int pos, pii val)
{
    if ( !root ) { root = ++ tot; Tree[root].Min = Tree[root].Minn = pii(INF, 0); ls(root) = rs(root) = 0; }
    if ( l == r ) { Merge(Tree[root].Min, Tree[root].Minn, val, pii(INF, 0), Tree[root].Min, Tree[root].Minn); return ; } 
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, val);
    else Modify(rs(root), Mid + 1, r, pos, val);
    PushUp(root);
}

inline pii Query(int root, int l, int r, int L, int R, int t)
{
    if ( !root ) return pii(INF, 0);
    if ( L <= l && r <= R ) return Tree[root].Min.y != t ? Tree[root].Min : Tree[root].Minn; 
    int Mid = l + r >> 1; pii ret = pii(INF, 0);
    if ( L <= Mid ) chkmin(ret, Query(ls(root), l, Mid, L, R, t));
    if ( Mid < R ) chkmin(ret, Query(rs(root), Mid + 1, r, L, R, t));
    return ret;
}

signed main()
{
    freopen("exhibition.in", "r", stdin);
    freopen("exhibition.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d%d", &a[i].l, &a[i].r); -- a[i].r; a[i].id = f[i] = i; } 
    Tree[0].Min = Tree[0].Minn = pii(INF, 0);
    sort(a + 1, a + n + 1, [](node &a, node &b) { return a.l < b.l; }); 
    while ( flag ) 
    {
        REP(i, 1, n) dis[i] = pii(INF, 0);        

        Root = tot = 0;
        REP(i, 1, n) 
        {
            pii t = Query(Root, 1, N, a[i].l, N, find(a[i].id));
            if ( t.x != INF ) chkmin(dis[find(a[i].id)], t - pii(a[i].l - 1, 0));
            t = Query(Root, 1, N, a[i].r, N, find(a[i].id));
            if ( t.x != INF ) chkmin(dis[find(a[i].id)], pii(a[i].r - a[i].l + 1, t.y));
            Modify(Root, 1, N, a[i].r, pii(a[i].r, find(a[i].id)));
        }

        Root = tot = 0;
        for ( int i = n; i >= 1; -- i ) 
        {
            pii t = Query(Root, 1, N, 1, a[i].r, find(a[i].id));
            if ( t.x != INF ) chkmin(dis[find(a[i].id)], pii(a[i].r, 0) + t);
            Modify(Root, 1, N, a[i].l, pii(-a[i].l + 1, find(a[i].id)));
        }

        Root = tot = 0;
        for ( int i = n; i >= 1; -- i ) 
        {
            pii t = Query(Root, 1, N, 1, a[i].r, find(a[i].id));
            if ( t.x != INF ) chkmin(dis[find(a[i].id)], t);
            Modify(Root, 1, N, a[i].r, pii(a[i].r - a[i].l + 1, find(a[i].id)));
        }

        flag = false;
        REP(i, 1, n) if ( find(i) == i && dis[i].x != INF && find(i) != find(dis[i].y) ) { ans += dis[i].x; f[i] = dis[i].y; ++ num; flag = true; }
    }
    if ( num != n - 1 ) puts("-1");
    else printf("%lld\n", ans);
    return 0;
}
