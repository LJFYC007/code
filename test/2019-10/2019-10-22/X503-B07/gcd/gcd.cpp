/***************************************************************
	File name: gcd.cpp
	Author: ljfcnyali
	Create time: 2019年10月22日 星期二 08时49分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( register int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define lson root << 1
#define rson root << 1 | 1
#define max maxx
typedef long long LL;

const int maxn = 80010;

inline LL maxx(LL a, LL b) { return a > b ? a : b; }

int n, m, a[maxn], p[maxn][17], LG[maxn];
LL sum[maxn], ans[maxn], c[maxn];
struct Line { int k; LL b; } p1;
struct TREE { Line x; bool flag; } Tree[maxn << 2];
struct node { int x, y; } p2;
vector<node> q[maxn];

inline void add(int pos, LL val)
{
    for ( int i = pos; i <= n; i += (i & -i) ) c[i] = max(c[i], val);
}

inline LL Get(int pos)
{
    LL sum = 0;
    for ( int i = pos; i > 0; i -= (i & -i) ) sum = max(sum, c[i]);
    return sum;
}

inline LL f(Line x, int pos) { return sum[pos] * x.k + x.b; }

inline void Modify(int root, int l, int r, Line x)
{
    if ( !Tree[root].flag ) { Tree[root].flag = true; Tree[root].x = x; return ; }
    if ( l == r )
    {
        if ( f(Tree[root].x, l) < f(x, l) ) Tree[root].x = x;
        return ;
    }
    int Mid = l + r >> 1;
    if ( x.k > Tree[root].x.k )
    {
        if ( f(x, Mid) > f(Tree[root].x, Mid) )
        {
            Modify(lson, l, Mid, Tree[root].x);
            Tree[root].x = x;
        }
        else Modify(rson, Mid + 1, r, x);
    }
    else 
    {
        if ( f(x, Mid) > f(Tree[root].x, Mid) )
        {
            Modify(rson, Mid + 1, r, Tree[root].x);
            Tree[root].x = x;
        }
        else Modify(lson, l, Mid, x);
    }
}

inline void Update(int root, int l, int r, int L, int R, Line x)
{
    if ( L <= l && r <= R ) { Modify(root, l, r, x); return ; }
    int Mid = l + r >> 1;
    if ( L <= Mid ) Update(lson, l, Mid, L, R, x);
    if ( Mid < R ) Update(rson, Mid + 1, r, L, R, x);
}

inline LL Query(int root, int l, int r, int pos)
{
    if ( l == r ) 
    {
        if ( Tree[root].flag ) return f(Tree[root].x, pos);
        return 0;
    }
    int Mid = l + r >> 1; LL ans = 0;
    if ( Tree[root].flag ) ans = f(Tree[root].x, pos);
    if ( pos <= Mid ) ans = max(ans, Query(lson, l, Mid, pos));
    else ans = max(ans, Query(rson, Mid + 1, r, pos));
    return ans;
}

inline int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

inline int calc(int L, int R)
{
    int x = LG[R - L + 1];
    return gcd(p[L][x], p[R - (1 << x)][x]);
}

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
    freopen("gcd.in", "r", stdin);
    freopen("gcd.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) 
    {
        read(a[i]); sum[i] = sum[i - 1] + a[i];
        if ( i != 1 ) 
        {
            LG[i] = LG[i >> 1] + 1;
            p[i - 1][0] = gcd(a[i - 1], a[i]);
        }
    }
    REP(i, 1, m)
    {
        int l; read(l); read(p2.x);
        p2.y = i; q[l].emplace_back(p2);
    }
    REP(j, 1, LG[n]) REP(i, 1, n) p[i][j] = gcd(p[i][j - 1], p[i + (1 << j - 1)][j - 1]);
    for ( register int i = n; i >= 1; -- i )
    {
        int x = a[i];
        for ( register int t = i, pos; t <= n; t = pos + 1)
        {
            int L = t, R = n; pos = t;
            while ( L <= R ) 
            {
                int Mid = L + R >> 1;
                if ( calc(i, Mid) == x ) { pos = Mid; L = Mid + 1; }
                else R = Mid - 1;
            }
            p1.k = x; p1.b = -sum[i - 1] * x;
            Update(1, 1, n, t, pos, p1);
            add(pos, (sum[pos] - sum[i - 1]) * x);
            x = gcd(x, a[pos + 1]);
        }
        REP(j, 0, q[i].size() - 1)
            ans[q[i][j].y] = max(Get(q[i][j].x), Query(1, 1, n, q[i][j].x));
    }
    REP(i, 1, m) printf("%lld\n", ans[i]); puts("");
    return 0;
}
