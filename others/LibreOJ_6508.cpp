/***************************************************************
	File name: LibreOJ_6508.cpp
	Author: ljfcnyali
	Create time: 2020年11月12日 星期四 15时06分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a, b, c, m, q, tot, Root;
struct node { int lson, rson, val; } Tree[maxn << 7];
char s[maxn];

inline void PushDown(int root)
{
    if ( !Tree[root].val ) return ;
    if ( !ls(root) ) ls(root) = ++ tot; Tree[ls(root)].val += Tree[root].val;
    if ( !rs(root) ) rs(root) = ++ tot; Tree[rs(root)].val += Tree[root].val;
    Tree[root].val = 0;
}

inline void Modify(int &root, int l, int r, int L, int R, int val)
{
    if ( !root ) root = ++ tot;
    if ( L <= l && r <= R ) { Tree[root].val += val; return ; } 
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(ls(root), l, Mid, L, R, val);
    if ( Mid < R ) Modify(rs(root), Mid + 1, r, L, R, val);
}

inline int Query(int root, int l, int r, int pos)
{
    if ( l == r ) return Tree[root].val;
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) return Query(ls(root), l, Mid, pos);
    return Query(rs(root), Mid + 1, r, pos);
}

inline void Solve(int i, int val)
{
    int l = -a * i, r = c - a * i - 1;
    l = (l % n + n) % n; r = (r % n + n) % n;
    if ( s[i] == '0' ) { val = -val; Modify(Root, 0, n - 1, 0, n - 1, -val); }
    if ( l <= r ) Modify(Root, 0, n - 1, l, r, val);
    else { Modify(Root, 0, n - 1, 0, r, val); Modify(Root, 0, n - 1, l, n - 1, val); }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld%lld%lld", &n, &a, &b, &c, &m);
    scanf("%s", s); scanf("%lld", &q);
    REP(i, 0, m - 1) Solve(i, 1);
    while ( q -- ) 
    {
        int op, pos; scanf("%lld%lld", &op, &pos);
        if ( op == 1 ) printf("%lld\n", Query(Root, 0, n - 1, (a * pos + b) % n));
        else 
        {
            Solve(pos, -1);
            s[pos] = s[pos] == '1' ? '0' : '1';
            Solve(pos, 1);
        }
    }
    return 0;
}
