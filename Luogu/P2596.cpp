/***************************************************************
	File name: P2596.cpp
	Author: ljfcnyali
	Create time: 2019年07月30日 星期二 10时30分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 1000010;

struct node
{
    int size, fa, lson, rson, rank, val;
} Tree[maxn];

int n, m, cnt, id[maxn];

inline void New_Node(int val)
{
    Tree[++ cnt].val = val;
    Tree[cnt].size = 1; 
    Tree[cnt].rank = rand();
}

inline void Push_up(int root) { Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1; }

inline void Merge(int &root, int a, int b)
{
    if ( !a || !b ) { root = a + b; return ; }
    if ( Tree[a].rank < Tree[b].rank ) { root = a; Merge(rs(a), rs(a), b); Tree[rs(a)].fa = a; }
    else { root = b; Merge(ls(b), a, ls(b)); Tree[ls(b)].fa = b; }
    Push_up(root);
}

inline void Split(int root, int &a, int &b, int val, int fa, int fb)
{
    if ( !root ) { a = b = 0; return ; }
    if ( val <= Tree[ls(root)].size ) 
    {
        b = root; Tree[b].fa = fb;
        Split(ls(b), a, ls(b), val, fa, root); 
    }
    else
    {
        a = root; Tree[a].fa = fa;
        Split(rs(a), rs(a), b, val - Tree[ls(a)].size - 1, root, fb);
    }
    Push_up(root);
}

int Root, a, b, c, d;

inline int find(int x)
{
    int s = Tree[ls(x)].size + 1;
    while ( x != Root ) 
    {
        if ( rs(Tree[x].fa) == x ) s += Tree[ls(Tree[x].fa)].size + 1;
        x = Tree[x].fa;
    }
    return s;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { int x; scanf("%d", &x); New_Node(x); Merge(Root, Root, cnt); id[x] = i; }
    REP(i, 1, m)
    {
        char s[100]; scanf("%s", s);
        if ( s[0] == 'T' ) 
        { 
            int x, k; scanf("%d", &x); k = find(id[x]);
            Split(Root, a, b, k, 0, 0);
            Split(a, a, c, k - 1, 0, 0);
            Merge(a, a, b); Merge(Root, c, a);
        }
        else if ( s[0] == 'B' ) 
        {
            int x, k; scanf("%d", &x); k = find(id[x]);
            Split(Root, a, b, k, 0, 0);
            Split(a, a, c, k - 1, 0, 0);
            Merge(b, b, c); Merge(Root, a, b);
        }
        else if ( s[0] == 'I' ) 
        {
            int x, t, k; scanf("%d%d", &x, &t); k = find(id[x]);
            if ( !t ) continue ;
            if ( t < 0 )
            {
                Split(Root, a, b, k, 0, 0);
                Split(a, a, c, k - 1, 0, 0);
                Split(a, a, d, k - 2, 0, 0);
                Merge(a, a, c); Merge(a, a, d); Merge(Root, a, b);
            }    
            else
            {
                Split(Root, a, b, k, 0, 0);
                Split(a, a, c, k - 1, 0, 0);
                Split(b, b, d, 1, 0, 0);
                Merge(a, a, b); Merge(a, a, c); Merge(Root, a, d);
            }
        }
        else if ( s[0] == 'A' ) { int x; scanf("%d", &x); printf("%d\n", find(id[x]) - 1); }
        else
        {
            int x; scanf("%d", &x);
            Split(Root, a, b, x, 0, 0);
            x = a;
            while ( rs(x) ) x = rs(x);
            printf("%d\n", Tree[x].val);
            Merge(Root, a, b);
        }
    }
    return 0;
}
