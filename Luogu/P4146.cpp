// luogu-judger-enable-o2
/***************************************************************
    File name: P4146.cpp
    Author: ljfcnyali
    Create time: 2019年06月27日 星期四 18时44分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson

const int maxn = 50010;

struct node
{
    int lson, rson, val, rank, size, sum, Max, lazy;
} Tree[maxn];

inline void Push_down(int root)
{
    if ( Tree[root].lazy ) 
    {
        swap(ls(root), rs(root));
        if ( ls(root) ) Tree[ls(root)].lazy ^= 1;
        if ( rs(root) ) Tree[rs(root)].lazy ^= 1;
        Tree[root].lazy = 0;
    }
    if ( ls(root) ) 
    { 
        Tree[ls(root)].sum += Tree[root].sum; 
        Tree[ls(root)].Max += Tree[root].sum; 
        Tree[ls(root)].val += Tree[root].sum;
    }
    if ( rs(root) ) 
    { 
        Tree[rs(root)].sum += Tree[root].sum; 
        Tree[rs(root)].Max += Tree[root].sum; 
        Tree[rs(root)].val += Tree[root].sum;
    }
    Tree[root].sum = 0;
}

inline void Push_up(int root)
{
    Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1;
    Tree[root].Max = Tree[root].val;
    if ( ls(root) )
        Tree[root].Max = max(Tree[root].Max, Tree[ls(root)].Max);
    if ( rs(root) )
        Tree[root].Max = max(Tree[root].Max, Tree[rs(root)].Max);
}

inline void Split(int root, int &a, int &b, int val)
{
    if ( !root ) { a = b = 0; return ; }
    Push_down(root);
    if ( Tree[ls(root)].size + 1 <= val ) 
    {
        a = root;
        Split(rs(a), rs(a), b, val - Tree[ls(root)].size - 1);
    }
    else
    {
        b = root;
        Split(ls(b), a, ls(b), val);
    }
    Push_up(root);
}

inline void Merge(int &root, int a, int b)
{
    if ( !a || !b ) { root = a + b; return ; }
    Push_down(root);
    if ( Tree[a].rank < Tree[b].rank ) 
    {
        Push_down(a);
        root = a;
        Merge(rs(a), rs(a), b);
    }
    else
    {
        Push_down(b);
        root = b;
        Merge(ls(b), a, ls(b));
    }
    Push_up(root);
}

inline void New_Node(int x)
{
    ls(x) = rs(x) = Tree[x].val = Tree[x].sum = Tree[x].Max = Tree[x].lazy = 0;
    Tree[x].size = 1;
    Tree[x].rank = rand();
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, root = 0, m;    
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { New_Node(i); Merge(root, root, i); }
    REP(i, 1, m)
    {
        int opt, l, r; scanf("%d%d%d", &opt, &l, &r);
        if ( opt == 1 ) 
        {
            int val, a, b, c; scanf("%d", &val);
            Split(root, a, b, r);
            Split(a, a, c, l - 1);
            Tree[c].sum += val;
            Tree[c].Max += val;
            Tree[c].val += val;
            Merge(a, a, c);
            Merge(root, a, b);
        }
        if ( opt == 2 ) 
        {
            int a, b, c;
            Split(root, a, b, r);
            Split(a, a, c, l - 1);
            Tree[c].lazy ^= 1;
            Merge(a, a, c);
            Merge(root, a, b);
        }
        if ( opt == 3 ) 
        {
            int a, b, c;
            Split(root, a, b, r);
            Split(a, a, c, l - 1);
            printf("%d\n", Tree[c].Max);
            Merge(a, a, c);
            Merge(root, a, b);
        }
    }
    return 0;
}
