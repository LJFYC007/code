#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long

const int maxn = 3e5 + 10;
const int INF = 1e18;

int n, q, c, a[maxn], b[maxn], d[maxn], num, www;
struct Matrix { int a[2][2]; } now, f[maxn];
Matrix operator *(Matrix a, Matrix b)
{
    Matrix c; 
    REP(i, 0, 1) REP(j, 0, 1)
    {
        c.a[i][j] = -INF;
        REP(k, 0, 1) c.a[i][j] = max(c.a[i][j], a.a[i][k] + b.a[k][j]);
    }
    return c;
}
struct node { Matrix sum; int ret; } Tree[maxn << 2];

inline int lowbit(int x) { return x & -x; }
inline void modify(int *b, int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) b[i] += val; } 
inline int query(int *b, int pos) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += b[i]; return ret; } 

#define lson root << 1
#define rson root << 1 | 1
inline void Modify(int root, int l, int r, int pos, Matrix val)
{
    if ( l == r ) { Tree[root].sum = val; Tree[root].ret = a[l]; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);
    Tree[root].sum = Tree[lson].sum * Tree[rson].sum;
    Tree[root].ret = Tree[lson].ret + Tree[rson].ret;
}
inline int Query(int root, int l, int r)
{
    if ( l == r ) return l;
    int Mid = l + r >> 1;
    if ( (now * Tree[lson].sum).a[0][0] < www - Tree[lson].ret ) 
    { 
        now = now * Tree[lson].sum; 
        www -= Tree[lson].ret;
        return Query(rson, Mid + 1, r); 
    }
    return Query(lson, l, Mid);
}

inline int Check(int i, int o, int sum)
{
    int x = min(a[o] - i * c, sum);
    return sum - x + (a[o] - x) / c;
}

inline int Get(int o, int sum)
{
    int val = query(b, n - (o + 1) + 1);
    int l = 0, r = a[o] / c, pos = 0;
    while ( l <= r ) 
    {
        int Mid = l + r >> 1;
        if ( Check(Mid, o, sum) <= val ) { pos = Mid; l = Mid + 1; }
        else r = Mid - 1;
    }

    int ret = INF;
    REP(i, max(0ll, pos - 2), min(a[o] / c, pos + 2)) 
    {
        int x = min(a[o] - i * c, sum);
        ret = min(ret, a[o] - x + max(0ll, val - (sum - x + (a[o] - x) / c)));
    }
    return ret;
}

inline void Solve()
{
    mem(now.a); www = num; int ret = 0, pos = Query(1, 1, n); 
    printf("%lld\n", query(d, pos - 1) + now.a[0][0] + Get(pos, now.a[0][0]));
}

inline void INIT(int i)
{
    f[i].a[0][0] = (a[i] / c) - (a[i] % c); f[i].a[1][0] = a[i] / c;
    f[i].a[0][1] = -INF; f[i].a[1][1] = 0; Modify(1, 1, n, i, f[i]);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &q, &c);
    REP(i, 1, n) { scanf("%lld", &a[i]); modify(b, n - i + 1, a[i]); modify(d, i, a[i] - a[i] / c); num += a[i]; }
    REP(i, 1, n) INIT(i); Solve();

    while ( q -- ) 
    {
        int x, y; scanf("%lld%lld", &x, &y); 
        modify(b, n - x + 1, -a[x] + y); 
        modify(d, x, y - y / c - (a[x] - a[x] / c));
        num = num - a[x] + y; a[x] = y; 
        INIT(x); Solve();
    }
    return 0;
}