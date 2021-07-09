/***************************************************************
	File name: P5055.cpp
	Author: ljfcnyali
	Create time: 2019年08月31日 星期六 08时35分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int long long
typedef long long LL;

const int maxn = 20000010;

struct node
{
    int lson, rson, size, val, sum, lazy, rank;
} Tree[maxn];

int n, ans, tot, Root[maxn];

inline void NewNode(int val)
{
    Tree[++ tot].val = val; Tree[tot].sum = val;
    ls(tot) = rs(tot) = Tree[tot].lazy = 0;
    Tree[tot].size = 1;
    Tree[tot].rank = rand();
}

inline void PushUp(int root)
{
    Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1;
    Tree[root].sum = Tree[ls(root)].sum + Tree[rs(root)].sum + Tree[root].val;
}

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ; Tree[root].lazy ^= 1;
    if ( ls(root) ) { Tree[++ tot] = Tree[ls(root)]; ls(root) = tot; } 
    if ( rs(root) ) { Tree[++ tot] = Tree[rs(root)]; rs(root) = tot; } 
    swap(ls(root), rs(root));
    Tree[ls(root)].lazy ^= 1; Tree[rs(root)].lazy ^= 1;
}

inline void Merge(int &root, int a, int b)
{
    if ( !a || !b ) { root = a + b; return ; }
    PushDown(a); PushDown(b);
    if ( Tree[a].rank < Tree[b].rank ) { root = a; Merge(rs(a), rs(a), b); }
    else { root = b; Merge(ls(b), a, ls(b)); }
    PushUp(root);
}

inline void Split(int now, int &a, int &b, int val)
{
    if ( !now ) { a = b = 0; return ; }
    PushDown(now);
    int root = ++ tot; Tree[root] = Tree[now];
    if ( val <= Tree[ls(root)].size ) { b = root; Split(ls(b), a, ls(b), val); }
    else { a = root; Split(rs(a), rs(a), b, val - Tree[ls(root)].size - 1); }
    PushUp(root);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    srand(time(0));
    scanf("%lld", &n);
    REP(i, 1, n)
    {
        int v, opt, pos, val, l, r, a, b, c;
        scanf("%lld%lld", &v, &opt); Root[i] = Root[v];
        if ( opt == 1 ) 
        {
            scanf("%lld%lld", &pos, &val); pos ^= ans; val ^= ans;
            Split(Root[i], a, b, pos);
            NewNode(val);
            Merge(a, a, tot); Merge(Root[i], a, b);
        }
        if ( opt == 2 ) 
        {
            scanf("%lld", &pos); pos ^= ans;
            Split(Root[i], a, b, pos); Split(a, a, c, pos - 1);
            Merge(Root[i], a, b);
        }
        if ( opt == 3 ) 
        {
            scanf("%lld%lld", &l, &r); l ^= ans; r ^= ans;
            Split(Root[i], a, b, r); Split(a, a, c, l - 1);
            Tree[c].lazy ^= 1;
            Merge(a, a, c); Merge(Root[i], a, b);
        }
        if ( opt == 4 ) 
        {
            scanf("%lld%lld", &l, &r); l ^= ans; r ^= ans;
            Split(Root[i], a, b, r); Split(a, a, c, l - 1);
            ans = Tree[c].sum; printf("%lld\n", Tree[c].sum);
            Merge(a, a, c); Merge(Root[i], a, b);
        }
    }
    return 0;
}
