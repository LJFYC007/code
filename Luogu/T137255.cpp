/***************************************************************
	File name: T137255.cpp
	Author: ljfcnyali
	Create time: 2020年07月07日 星期二 14时43分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, m, a[maxn];
struct node { int lazy1, lazy2, val; } Tree[maxn << 2];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void Build(int root, int l, int r)
{
    Tree[root].lazy1 = Tree[root].lazy2 = 1;
    if ( l == r ) { Tree[root].val = a[l]; return ; }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
}

inline void Modify1(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) 
    {
        PushTag1(root, val);
        return ;
    }
}

inline int Query(int root, int l, int r, int pos)
{
    if ( l == r ) return Tree[root].val;
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) return Query(lson, l, Mid, pos);
    return Query(rson, Mid + 1, r, pos);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i]);
    Build(1, 1, n);
    while ( m -- ) 
    {
        int op; scanf("%lld", &op); 
        if ( op == 1 ) 
        {
            int l, r, x; scanf("%lld%lld%lld", &l, &r, &x);
            Modify1(1, 1, n, l, r, x);
        }
        else if ( op == 2 ) 
        {
            int l, r, x; scanf("%lld%lld%lld", &l, &r, &x);
            Modify2(1, 1, n, l, r, Query(1, 1, n, x));
        }
        else
        {
            int x; scanf("%lld", &x);
            printf("%lld\n", (Query(1, 1, n, x) + Mod) % Mod);
        }
    }
    return 0;
}
