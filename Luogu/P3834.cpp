/***************************************************************
    File name: SP3946.cpp
    Author: ljfcnyali
    Create time: 2019年06月30日 星期日 15时21分51秒
***************************************************************/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson Tree[root].l
#define rson Tree[root].r

const int maxn = 2000010;

struct node
{
    int l, r, cnt;
} Tree[maxn];
struct Node
{
    int val, x;
} a[maxn];

int n, m, cnt, h[maxn], Root[maxn], tot, p[maxn];

inline int cmp(Node a, Node b) 
{
    return a.val < b.val;
}

inline void Push_up(int root) { Tree[root].cnt = Tree[lson].cnt + Tree[rson].cnt; }

inline int Build(int l, int r)
{
    int root = ++ tot;
    lson = rson = Tree[root].cnt = 0;
    if ( l == r ) return root; 
    int Mid = l + r >> 1;
    Tree[root].l = Build(l, Mid);
    Tree[root].r = Build(Mid + 1, r);
    return root;
}

inline int Insert(int now, int l, int r, int x)
{
    int root = ++ tot;
    Tree[root] = Tree[now];
    if ( l == r ) { ++ Tree[root].cnt; return root; }
    int Mid = l + r >> 1;
    if ( x <= Mid ) lson = Insert(Tree[now].l, l, Mid, x);
    else rson = Insert(Tree[now].r, Mid + 1, r, x);
    Push_up(root);
    return root;
}

inline int Query(int p, int q, int l, int r, int k)
{
    if ( l == r ) return l;
    int Mid = l + r >> 1;
    int sum = Tree[Tree[q].l].cnt - Tree[Tree[p].l].cnt;
    if ( k <= sum ) return Query(Tree[p].l, Tree[q].l, l, Mid, k);
    else return Query(Tree[p].r, Tree[q].r, Mid + 1, r, k - sum);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%d%d", &n, &m) )
    {
        //cnt = tot = 0; mem(Root); mem(Tree);
        REP(i, 1, n) { scanf("%d", &a[i].val); a[i].x = i; }    
        sort(a + 1, a + n + 1, cmp);
        REP(i, 1, n) 
        {
            if ( a[i].val != a[i - 1].val || i == 1 ) ++ cnt;
            h[a[i].x] = cnt; p[cnt] = a[i].val;
        }
        Root[0] = Build(1, cnt);
        REP(i, 1, n) Root[i] = Insert(Root[i - 1], 1, cnt, h[i]);
        REP(i, 1, m)
        {
            int l, r, k; scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", p[Query(Root[l - 1], Root[r], 1, cnt, k)]);
        }
    }
    return 0;
}
