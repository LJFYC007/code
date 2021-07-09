/***************************************************************
	File name: P1486.cpp
	Author: ljfcnyali
	Create time: 2019年06月27日 星期四 19时33分13秒
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
    int lson, rson, val, size, rank;
} Tree[maxn];

int Delta, n, Min, cnt, ans;

inline void Push_up(int root) { Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1; }

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
    Push_up(root);
}

inline void Merge(int &root, int a, int b)
{
    if ( !a || !b ) { root = a + b; return ; }
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
    Push_up(root);
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

inline void New_Node(int x)
{
    Tree[++ cnt].val = x;
    ls(cnt) = rs(cnt) = 0;
    Tree[cnt].size = 1;
    Tree[cnt].rank = rand();
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int root = 0;
    scanf("%d%d", &n, &Min);
    REP(i, 1, n)
    {
//        getchar(); 
        getchar(); char c = getchar();
        int x; scanf("%d", &x);
        if ( c == 'I' ) 
        {
            if ( x < Min ) { continue ; }
            x -= Delta;
            int a, b;
            Split(root, a, b, x);
            New_Node(x);
            Merge(a, a, cnt);
            Merge(root, a, b);
        }
        else if ( c == 'A' ) Delta += x;
        else if ( c == 'S' ) 
        {
            Delta -= x;
            int a, b, c;
            Split(root, a, b, Min - Delta);
            Split(a, a, c, Min - Delta - 1);
            ans += Tree[a].size;
            Merge(root, c, b);
        }
        else 
        {
            if ( Tree[root].size < x ) { printf("-1\n"); continue ; }
           /* printf("%d ", Delta);
            printf("%d %d %d ", Tree[root].val, Tree[rs(root)].val, Tree[rs(rs(root))].val);
            printf("%d ", GetRank(root, Tree[root].size - x + 1));*/
            printf("%d\n", GetRank(root, Tree[root].size - x + 1) + Delta);
        }
    }
    printf("%d\n", ans);
    return 0;
}
