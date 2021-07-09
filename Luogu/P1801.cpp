/***************************************************************
	File name: P1801.cpp
	Author: ljfcnyali
	Create time: 2019年07月30日 星期二 21时38分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 2000010;

struct node
{
    int size, val, rank, lson, rson;
} Tree[maxn];

int n, m, cnt, A[maxn], B[maxn], x;

inline void Push_up(int root) { Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1; }

inline void Merge(int &root, int a, int b)
{
    if ( !a || !b ) { root = a + b; return ; }
    if ( Tree[a].rank < Tree[b].rank ) { root = a; Merge(rs(a), rs(a), b); }
    else { root = b; Merge(ls(b), a, ls(b)); }
    Push_up(root);
}

inline void Split(int root, int &a, int &b, int val)
{
    if ( !root ) { a = b = 0; return ; }
    if ( Tree[root].val <= val ) { a = root; Split(rs(a), rs(a), b, val); }
    else { b = root; Split(ls(b), a, ls(b), val); }
    Push_up(root);
}

inline void New_Node(int val)
{
    Tree[++ cnt].val = val; Tree[cnt].size = 1;
    Tree[cnt].rank = rand();
}

inline int find(int root, int k)
{
    while ( Tree[ls(root)].size + 1 != k ) 
    {
        if ( k <= Tree[ls(root)].size ) root = ls(root);
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
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &A[i]);
    REP(i, 1, m) scanf("%d", &B[i]);
    int now = 1, Root = 0, a, b, c;
    REP(i, 1, n)
    {
        New_Node(A[i]); 
        Split(Root, a, b, A[i]);
        Merge(a, a, cnt); Merge(Root, a, b);
        while ( B[now] == i && now <= m ) { printf("%d\n", find(Root, ++ x)); ++ now; }
    }
    return 0;
}
