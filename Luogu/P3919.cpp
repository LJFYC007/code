/***************************************************************
	File name: P3919.cpp
	Author: ljfcnyali
	Create time: 2019年06月30日 星期日 16时21分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 40000010;

struct node
{
    int lson, rson, val;
} Tree[maxn];

int n, m, Root[maxn], tot, cnt, a[maxn];

inline int Build(int l, int r)
{
    int root = ++ tot;
    if ( l == r ) { Tree[root].val = a[l]; return root; }
    int Mid = l + r >> 1;
    Tree[root].lson = Build(l, Mid);
    Tree[root].rson = Build(Mid + 1, r);
    return root;
}

inline int Update(int now, int l, int r, int x, int val)
{
    int root = ++ tot;
    Tree[root] = Tree[now];
    if ( l == r ) { Tree[root].val = val; return root; } 
    int Mid = l + r >> 1;
    if ( x <= Mid ) Tree[root].lson = Update(Tree[now].lson, l, Mid, x, val);
    else Tree[root].rson = Update(Tree[now].rson, Mid + 1, r, x, val);
    return root;
}

inline int Query(int root, int l, int r, int x)
{
    if ( l == r ) return Tree[root].val;
    int Mid = l + r >> 1;
    if ( x <= Mid ) return Query(Tree[root].lson, l, Mid, x);
    else return Query(Tree[root].rson, Mid + 1, r, x);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    Root[0] = Build(1, n);
    REP(i, 1, m)
    {
        int v, opt, x;
        scanf("%d%d%d", &v, &opt, &x);
        if ( opt == 1 )
        {
            int val; scanf("%d", &val);
            Root[++ cnt] = Update(Root[v], 1, n, x, val);
        }
        else { printf("%d\n", Query(Root[v], 1, n, x)); Root[++ cnt] = Root[v]; }
    }
    return 0;
}
