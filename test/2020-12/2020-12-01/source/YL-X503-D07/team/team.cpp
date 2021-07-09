/***************************************************************
	File name: team.cpp
	Author: ljfcnyali
	Create time: 2020年12月01日 星期二 11时02分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define lson root << 1
#define rson root << 1 | 1
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, a[maxn], b[maxn];
struct Node { int Min, sum, val; } Tree[maxn << 2];
set<int> p[maxn];
struct node { int root, l, r; node ( int a = 0, int b = 0, int c = 0 ) { root = a; l = b; r = c; } } ;
vector<node> Fucku;

inline int Query(int root, int l, int r, int val)
{
    if ( Tree[root].Min >= val ) return val * (r - l + 1);
    if ( l == r ) return Tree[root].Min;
    int Mid = l + r >> 1;
    if ( Tree[rson].Min < val ) return Tree[root].val + Query(rson, Mid + 1, r, val);
    return Query(lson, l, Mid, val) + val * (r - Mid);
}

inline void Modify(int root, int l, int r, int pos)
{
    if ( l == r ) { Tree[root].sum = Tree[root].Min = b[pos]; return ; }
    int Mid = l + r >> 1; 
    if ( pos <= Mid ) Modify(lson, l, Mid, pos);
    else Modify(rson, Mid + 1, r, pos);
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
    Tree[root].val = Query(lson, l, Mid, Tree[rson].Min);
    Tree[root].sum = Tree[rson].sum + Tree[root].val;
}

inline void Get(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) { Fucku.push_back(node(root, l, r)); return ; }
    int Mid = l + r >> 1;
    if ( Mid < R ) Get(rson, Mid + 1, r, L, R);
    if ( L <= Mid ) Get(lson, l, Mid, L, R);
}

signed main()
{
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) { scanf("%lld", &a[i]); p[a[i]].insert(i); }
    REP(i, 1, n) p[i].insert(n + 1);
    REP(i, 1, n) { b[i] = *p[a[i]].upper_bound(i); Modify(1, 1, n, i); }
    REP(i, 1, m)
    {
        int op, x, y; scanf("%lld%lld%lld", &op, &x, &y);
        if ( op == 1 ) 
        {
            auto it = p[a[x]].lower_bound(x);
            if ( it != p[a[x]].begin() ) { -- it; b[*it] = *p[a[x]].upper_bound(x); Modify(1, 1, n, *it); }
            p[a[x]].erase(x); a[x] = y; p[a[x]].insert(x);
            it = p[a[x]].lower_bound(x);
            if ( it != p[a[x]].begin() ) { -- it; b[*it] = x; Modify(1, 1, n, *it); }
            b[x] = *p[a[x]].upper_bound(x); Modify(1, 1, n, x);
        }
        else
        {
            int ans = 0, Min = y + 1; Fucku.clear(); Get(1, 1, n, x, y);
            for ( auto it : Fucku ) { ans += Query(it.root, it.l, it.r, Min); Min = min(Min, Tree[it.root].Min); }
            ans -= (x + y) * (y - x + 1) / 2;
            printf("%lld\n", ans);
        }
    }
    return 0;
}
