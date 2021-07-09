/***************************************************************
	File name: P3369.cpp
	Author: ljfcnyali
	Create time: 2019年11月14日 星期四 11时48分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 1e6 + 10;

int tot, n;
struct node { int lson, rson, val, rnd, size; } Tree[maxn];

inline void PushUp(int root) { Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1; }

inline void Split(int root, int &a, int &b, int val)
{
    if ( !root ) { a = b = 0; return ; }
    if ( Tree[root].val <= val ) { a = root; Split(rs(a), rs(a), b, val); }
    else { b = root; Split(ls(b), a, ls(b), val); }
    PushUp(root);
}

inline void Merge(int &root, int a, int b)
{
    if ( !a || !b ) { root = a + b; return ; }
    if ( Tree[a].rnd < Tree[b].rnd ) { root = a; Merge(rs(root), rs(root), b); }
    else { root = b; Merge(ls(root), a, ls(root)); }
    PushUp(root);
}

inline int Kth(int root, int x)
{
    while ( Tree[ls(root)].size + 1 != x ) 
    {
        if ( Tree[ls(root)].size + 1 <= x ) { x -= Tree[ls(root)].size + 1; root = rs(root); }
        else root = ls(root);
    }
    return Tree[root].val;
}

inline void NewNode(int val) { ++ tot; ls(tot) = rs(tot) = 0; Tree[tot].val = val; Tree[tot].size = 1; Tree[tot].rnd = rand(); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    int Root = 0, a, b, c;
    REP(i, 1, n)
    {
        int opt, x; scanf("%d%d", &opt, &x);
        if ( opt == 1 ) { NewNode(x); Split(Root, a, b, x); Merge(a, a, tot); Merge(Root, a, b); }
        if ( opt == 2 ) { Split(Root, a, b, x - 1); Split(b, b, c, x); Merge(b, ls(b), rs(b)); Merge(b, b, c); Merge(Root, a, b); }
        if ( opt == 3 ) { Split(Root, a, b, x - 1); printf("%d\n", Tree[a].size + 1); Merge(Root, a, b); }
        if ( opt == 4 ) printf("%d\n", Kth(Root, x));
        if ( opt == 5 ) { Split(Root, a, b, x - 1); printf("%d\n", Kth(a, Tree[a].size)); Merge(Root, a, b); } 
        if ( opt == 6 ) { Split(Root, a, b, x); printf("%d\n", Kth(b, 1)); Merge(Root, a, b); } 
    }
    return 0;
}
