/***************************************************************
	File name: P3391.cpp
	Author: ljfcnyali
	Create time: 2019年06月27日 星期四 16时31分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson

const int maxn = 1000010;

struct node
{
    int lson, rson, rank, val, size, lazy;
} Tree[maxn];

inline void Update(int root) { Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1; }

inline void Push_down(int root)
{
    if ( !Tree[root].lazy ) return ;
    swap(ls(root), rs(root));
    Tree[ls(root)].lazy ^= 1;
    Tree[rs(root)].lazy ^= 1;
    Tree[root].lazy = 0;
}

inline void New_Node(int x)
{
    ls(x) = rs(x) = Tree[x].lazy = 0; 
    Tree[x].rank = rand();
    Tree[x].val = x;
    Tree[x].size = 1;
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
    Update(root);
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
    Update(root);
}

inline void print(int root)
{
    Push_down(root);
    if ( ls(root) ) print(ls(root));
    printf("%d ", Tree[root].val);
    if ( rs(root) ) print(rs(root));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, root = 0, m;
    scanf("%d%d", &n, &m);
    REP(i, 1, n)
    {
        New_Node(i);
        Merge(root, root, i);
    }
    REP(i, 1, m)
    {
        int l, r, a, b, c; 
        scanf("%d%d", &l, &r);
        Split(root, a, b, r);
        Split(a, a, c, l - 1);
        Tree[c].lazy ^= 1;
        Merge(a, a, c);
        Merge(root, a, b);
    }
    print(root);
    return 0;
}
