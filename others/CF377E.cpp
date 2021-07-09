/***************************************************************
	File name: CF377E.cpp
	Author: ljfcnyali
	Create time: 2020年07月19日 星期日 20时52分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define x first
#define y second
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e18;
const int M = 2e16;

int n, s, tot = 1, N = M; 
pii a[maxn];
struct node { int lson, rson; pii x; bool flag; } Tree[maxn << 5];

inline int f(pii x, int pos) { return x.x * pos + x.y; }

inline void Modify(int &root, int l, int r, pii x)
{
    if ( !root ) root = ++ tot;
    if ( !Tree[root].flag ) { Tree[root].flag = true; Tree[root].x = x; return ; }
    if ( l == r ) { if ( f(Tree[root].x, l) < f(x, l) ) Tree[root].x = x; return ; }
    int Mid = l + r >> 1, val = f(Tree[root].x, Mid);
    if ( f(x, Mid) > val ) swap(x, Tree[root].x);
    if ( Tree[root].x.x < x.x ) Modify(rs(root), Mid + 1, r, x);
    else Modify(ls(root), l, Mid, x);
}

inline int Query(int root, int l, int r, int x)
{
    if ( !root ) return -INF;
    if ( l == r ) return Tree[root].flag ? f(Tree[root].x, x) : -INF;
    int Mid = l + r >> 1, ret = Tree[root].flag ? f(Tree[root].x, x) : -INF;
    if ( x <= Mid ) ret = max(ret, Query(ls(root), l, Mid, x));
    else ret = max(ret, Query(rs(root), Mid + 1, r, x));
    return ret;
}

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    read(n); read(s);
    REP(i, 1, n) { read(a[i].y); read(a[i].x); } 
    sort(a + 1, a + n + 1); 
    REP(i, 1, n) N = min(N, M / a[i].y);
    int Root = 1; Modify(Root, 0, N, pii(a[1].y, 0));
    int last = 0;
    REP(i, 2, n)
    {
        int l = last, r = N; pii x;
        while ( l <= r ) 
        {
            int Mid = l + r >> 1, val = Query(Root, 0, N, Mid);
            if ( val >= a[i].x ) { x = pii(Mid, val); r = Mid - 1; }
            else l = Mid + 1;
        }
        last = x.x;
        Modify(Root, 0, N, pii(a[i].y, x.y - a[i].x - a[i].y * x.x));
    }
    
    int l = 0, r = N, ans;
    while ( l <= r ) 
    {
        int Mid = l + r >> 1, val = Query(Root, 0, N, Mid);
        if ( val >= s ) { ans = Mid; r = Mid - 1; }
        else l = Mid + 1;
    }
    printf("%lld\n", (LL)ans);
    return 0;
}
