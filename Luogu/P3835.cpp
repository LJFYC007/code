/***************************************************************
	File name: P3835.cpp
	Author: ljfcnyali
	Create time: 2019年08月30日 星期五 21时10分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r
typedef long long LL;

const int maxn = 20000010;

struct node
{
    int size, val, rank, l, r;
} Tree[maxn];

int n, Root[maxn], tot;

inline void NewNode(int val)
{
    Tree[++ tot].val = val;
    ls(tot) = rs(tot) = 0;
    Tree[tot].size = 1;
    Tree[tot].rank = rand();
}

inline void PushUp(int root) { Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1; }

inline void Merge(int &root, int a, int b)
{
    if ( !a || !b ) { root = a + b; return ; }
    if ( Tree[a].rank < Tree[b].rank ) { root = a; Merge(rs(a), rs(a), b); }
    else { root = b; Merge(ls(b), a, ls(b)); }
    PushUp(root);
}

inline void Split(int now, int &a, int &b, int val)
{
    if ( !now ) { a = b = 0; return ; }
    int root = ++ tot; Tree[root] = Tree[now];
    if ( Tree[root].val <= val ) { a = root; Split(rs(a), rs(a), b, val); }
    else { b = root; Split(ls(b), a, ls(b), val); }
    PushUp(root);
}

inline int GetRank(int root, int k)
{
    while ( Tree[ls(root)].size + 1 != k ) 
    {
        if ( Tree[ls(root)].size >= k ) root = ls(root);
        else { k -= Tree[ls(root)].size + 1; root = rs(root); }
    }
    return Tree[root].val;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    srand(time(0));
    scanf("%d", &n);
    REP(i, 1, n)
    {
        int now, opt, x, a, b, c; scanf("%d%d%d", &now, &opt, &x);
        Root[i] = Root[now];
        if ( opt == 1 ) 
        {
            Split(Root[i], a, b, x);
            NewNode(x);
            Merge(a, a, tot);
            Merge(Root[i], a, b);
        }
        if ( opt == 2 ) 
        {
            Split(Root[i], a, b, x);
            Split(a, a, c, x - 1);
            Merge(c, ls(c), rs(c));
            Merge(a, a, c);
            Merge(Root[i], a, b);
        }
        if ( opt == 3 ) 
        {
            Split(Root[i], a, b, x);
            Split(a, a, c, x - 1);
            printf("%d\n", Tree[a].size + 1);
            Merge(a, a, c);
            Merge(Root[i], a, b);
        }
        if ( opt == 4 ) printf("%d\n", GetRank(Root[i], x));
        if ( opt == 5 ) 
        {
            Split(Root[i], a, b, x - 1);
            if ( !Tree[a].size ) puts("-2147483647");
            else printf("%d\n", GetRank(a, Tree[a].size));
            Merge(Root[i], a, b);
        }
        if ( opt == 6 )
        {
            Split(Root[i], a, b, x);
            if ( !Tree[b].size ) puts("2147483647");
            else printf("%d\n", GetRank(b, 1));
            Merge(Root[i], a, b);
        }
    }
    return 0;
}
