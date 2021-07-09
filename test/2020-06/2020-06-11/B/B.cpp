/***************************************************************
	File name: B.cpp
	Author: ljfcnyali-AKIOI
	Create time: 2020年06月11日 星期四 08时32分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 1e18;

int n, a[maxn], m, k[maxn], ans, tot;
struct node { int lson, rson, sum, lazy, val, size, rk; } Tree[maxn];

inline int NewNode(int x)
{
    int cur = ++ tot; 
    Tree[cur].val = Tree[cur].sum = x;
    Tree[cur].size = 1; Tree[cur].rk = rand();
    return cur;
}

inline void PushUp(int root) 
{ 
    Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1;
    Tree[root].sum = Tree[ls(root)].sum + Tree[rs(root)].sum + Tree[root].val;
}

inline void PushTag(int root, int val)
{
    Tree[root].sum += val * Tree[root].size;
    Tree[root].val += val; Tree[root].lazy += val;
}

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    if ( ls(root) ) PushTag(ls(root), Tree[root].lazy);
    if ( rs(root) ) PushTag(rs(root), Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Merge(int &root, int a, int b)
{
    if ( !a || !b ) { root = a + b; return ; }
    PushDown(a); PushDown(b); 
    if ( Tree[a].rk < Tree[b].rk ) { root = a; Merge(rs(root), rs(a), b); }
    else { root = b; Merge(ls(root), a, ls(b)); }
    PushUp(root);
}

inline void Split(int root, int &a, int &b, int val)
{
    if ( !root ) { a = b = 0; return ; }
    PushDown(root);
    if ( Tree[root].val <= val ) { a = root; Split(rs(a), rs(a), b, val); PushUp(a); }
    else { b = root; Split(ls(b), a, ls(b), val); PushUp(b); }
}

inline int Get(int root, int k)
{
    if ( k == 0 ) return -INF;
    while ( Tree[ls(root)].size + 1 != k ) 
    {
        PushDown(root);
        if ( k <= Tree[ls(root)].size ) root = ls(root);
        else { k -= Tree[ls(root)].size + 1; root = rs(root); }
    }
    return Tree[root].val;
}

inline void Split1(int root, int &a, int &b, int k)
{
    if ( !root ) { a = b = 0; return ; }
    PushDown(root);
    if ( k <= Tree[ls(root)].size ) { b = root; Split1(ls(b), a, ls(b), k); PushUp(b); }
    else { a = root; Split1(rs(a), rs(a), b, k - Tree[ls(root)].size - 1); PushUp(a); }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);
    scanf("%lld", &m); REP(i, 1, m) scanf("%lld", &k[i]);
    sort(k + 1, k + m + 1); reverse(k + 1, k + m + 1);
    sort(a + 1, a + n + 1); 
    int Root = 0; REP(i, 1, n) Merge(Root, Root, NewNode(a[i]));
    REP(i, 1, m)
    {
        int a, b, c, d, t = Get(Root, n - k[i]);
        Split(Root, a, b, t);
        if ( Tree[b].size == k[i] ) 
        {
            ans += Tree[b].sum;
            PushTag(b, -1);
            Merge(Root, a, b);
        }
        else
        {
            Split(a, a, c, t - 1); 
            k[i] -= Tree[b].size;
            Split1(c, c, d, Tree[c].size - k[i]);
            ans += Tree[b].sum + Tree[d].sum;
            PushTag(d, -1); PushTag(b, -1);
            Merge(Root, a, d); Merge(Root, Root, c); Merge(Root, Root, b);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
