/***************************************************************
	File name: FHQ-Treap.cpp
	Author: ljfcnyali
	Create time: 2019年06月27日 星期四 15时25分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson

const int maxn = 1000010;

int cnt;

struct node
{
    int val, lson, rson, size, rank;
} Tree[maxn];

inline void Update(int root)
{
    Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1;
}

inline void Split(int root, int &a, int &b, int val)
{
    if ( !root ) { a = b = 0; return ; }
    if ( Tree[root].val <= val ) 
    {
        a = root;
        Split(rs(a), rs(a), b, val);
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
    if ( !a || ! b ) { root = a + b; return ; }
    if ( Tree[a].rank < Tree[b].rank ) 
    {
        root = a;
        Merge(rs(a), rs(a), b);
    }
    else
    {
        root = b;
        Merge(ls(b), a, ls(b));
    }
    Update(root);
}

inline void New_Node(int val)
{
    Tree[++ cnt].size = 1;
    ls(cnt) = rs(cnt) = 0;
    Tree[cnt].rank = rand();
    Tree[cnt].val = val;
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
    int n, root = 0;
    scanf("%d", &n);
    REP(i, 1, n)
    {
        int opt, x; scanf("%d%d", &opt, &x);
        if ( opt == 1 ) 
        {
            int a, b;
            Split(root, a, b, x);
            New_Node(x);
            Merge(a, a, cnt);
            Merge(root, a, b);
        }
        if ( opt == 2 ) 
        {
            int a, b, c;
            Split(root, a, b, x);
            Split(a, a, c, x - 1);
            Merge(c, ls(c), rs(c));
            Merge(a, a, c);
            Merge(root, a, b);
        }
        if ( opt == 3 )
        {
            int a, b;
            Split(root, a, b, x - 1);
            printf("%d\n", Tree[a].size + 1);
            Merge(root, a, b);
        }
        if ( opt == 4 ) printf("%d\n", GetRank(root, x));
        if ( opt == 5 ) 
        {
            int a, b;
            Split(root, a, b, x - 1);
            printf("%d\n", GetRank(a, Tree[a].size));
            Merge(root, a, b);
        }
        if ( opt == 6 ) 
        {
            int a, b;
            Split(root, a, b, x);
            printf("%d\n", GetRank(b, 1));
            Merge(root, a, b);
        }
    }
    return 0;
}
