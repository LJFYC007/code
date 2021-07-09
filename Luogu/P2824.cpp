/***************************************************************
	File name: P2824.cpp
	Author: ljfcnyali
	Create time: 2019年06月17日 星期一 15时38分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1 
#define rson root << 1 | 1

const int maxn = 400010;

struct node
{
    int l, r, lazy, size, len;
} Tree[maxn];

struct Node
{
    int l, r, opt;
} p[maxn];

int n, m, a[maxn], q, ans, b[maxn], c[maxn];

inline void Push_up(int root)
{
    Tree[root].size = Tree[lson].size + Tree[rson].size;
}

inline void Push_down(int root)
{
    if ( Tree[root].lazy == -1 ) return ;
    Tree[lson].lazy = Tree[rson].lazy = Tree[root].lazy;
    Tree[lson].size = Tree[lson].len * Tree[root].lazy;
    Tree[rson].size = Tree[rson].len * Tree[root].lazy;
    Tree[root].lazy = -1;
}

inline void Build(int root, int l, int r)
{
    Tree[root].lazy = -1; 
    Tree[root].len = r - l + 1;
    Tree[root].l = l; Tree[root].r = r;
    if ( l == r ) 
    {
        Tree[root].size = c[l];
        return ;
    }
    int Mid = l + r >> 1;
    Build(lson, l, Mid);
    Build(rson, Mid + 1, r);
    Push_up(root);
}

inline int Query(int root, int l, int r)
{
    if ( l <= Tree[root].l && Tree[root].r <= r ) return Tree[root].size;
    Push_down(root);
    int Mid = Tree[root].l + Tree[root].r >> 1, sum = 0;
    if ( l <= Mid ) sum += Query(lson, l, r);
    if ( Mid < r ) sum += Query(rson, l, r);
    return sum;
}

inline void Update(int root, int l, int r, int val)
{
    if ( l > r ) return ;
    if ( l <= Tree[root].l && Tree[root].r <= r ) 
    {
        Tree[root].size = Tree[root].len * val;
        Tree[root].lazy = val;
        return ;
    }
    Push_down(root);
    int Mid = Tree[root].l + Tree[root].r >> 1;
    if ( l <= Mid ) Update(lson, l, r, val);
    if ( Mid < r ) Update(rson, l, r, val);
    Push_up(root);
}

inline bool check(int Mid)
{
    int s = b[Mid];
    REP(i, 1, n) if ( a[i] >= Mid ) c[i] = 1; else c[i] = 0;
    //REP(i, 1, n) cerr << c[i] << " ";
    Build(1, 1, n);
    //cerr << endl;
    REP(i, 1, m) 
    {
        //cerr << p[i].l << " " << p[i].r << " " << p[i].opt << " ";
        int x = Query(1, p[i].l, p[i].r);
        //cerr << x << endl;
        if ( p[i].opt == 0 ) 
        {
            int L = p[i].r - x;
            Update(1, p[i].l, L, 0);
            Update(1, L + 1, p[i].r, 1);
        }
        else
        {
            int R = p[i].l + x - 1;
            Update(1, p[i].l, R, 1);
            Update(1, R + 1, p[i].r, 0);
        }
        //REP(j, 1, 13) cerr << Tree[j].l << " " << Tree[j].r << " " << Tree[j].size << " " << Tree[j].lazy << endl;
        //cerr << endl;
    }
//    0 0 1 1 1 1 
    s = Query(1, q, q);
//    cerr << s << endl;
    if ( s == 1 ) return true;
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { scanf("%d", &a[i]); b[i] = a[i]; }
    sort(b + 1, b + n + 1);
    REP(i, 1, m) scanf("%d%d%d", &p[i].opt, &p[i].l, &p[i].r);
    scanf("%d", &q);
    int l = 1, r = b[n];
    while ( l <= r ) 
    {
        int Mid = l + r >> 1;
        //cerr << Mid << endl;
        if ( check(Mid) ) { ans = Mid; l = Mid + 1; }
        else r = Mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}
