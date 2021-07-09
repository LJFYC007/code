/***************************************************************
	File name: horsehunter.cpp
	Author: ljfcnyali
	Create time: 2020年12月31日 星期四 09时10分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 2e6 + 10;

int n, m, q, a[maxn];
struct node { int lval1, lval2, rval1, rval2; LL ans; } Tree[maxn << 2];

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

inline void Modify(int root, int l, int r, int pos, int val)
{
    if ( l == r ) { Tree[root].lval1 = Tree[root].rval2 = Tree[root].lval2 = Tree[root].rval1 = val; return ; } 
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);

    Tree[root].lval1 = Tree[lson].lval1; Tree[root].rval2 = Tree[rson].rval2;
    Tree[root].ans = Tree[lson].ans + Tree[rson].ans;
    if ( l + 1 == r ) { Tree[root].lval2 = Tree[root].rval2; Tree[root].rval1 = Tree[root].lval1; }
    else if ( l + 3 == r ) 
    {
        LL t = min(Tree[lson].lval2, Tree[rson].rval1);
        Tree[root].lval2 = Tree[lson].lval2 - t; Tree[root].rval1 = Tree[rson].rval1 - t;
        Tree[root].ans += t * (Mid ^ Mid + 1);
    }
    else 
    { 
        Tree[root].lval2 = Tree[lson].lval2; Tree[root].rval1 = Tree[rson].rval1; 
        LL t = min(Tree[lson].rval2, Tree[rson].lval1);
        Tree[root].ans += t * (Mid ^ Mid + 1) + min(Tree[lson].rval2 - t, (LL)Tree[lson].rval1) + min((LL)Tree[rson].lval2, Tree[rson].lval1 - t);
    }
}

inline LL Solve()
{
    LL ret = Tree[1].ans;
    ret += min(Tree[1].lval1, Tree[1].lval2);
    ret += min(Tree[1].rval1, Tree[1].rval2) * (LL)(n - 1 ^ n - 2);
    return ret;
}

signed main()
{
    freopen("horsehunter.in", "r", stdin);
    freopen("horsehunter.out", "w", stdout);
    scanf("%lld%lld", &m, &q); n = 1; while ( n <= m ) n <<= 1; 
    REP(i, 1, m) { read(a[i]); Modify(1, 0, n - 1, i, a[i]); }
    printf("%lld\n", Solve());
    while ( q -- ) { int x, y; read(x); read(y); Modify(1, 0, n - 1, x, y); printf("%lld\n", Solve()); }
    return 0;
}
