/***************************************************************
	File name: P2839.cpp
	Author: ljfcnyali
	Create time: 2019年08月12日 星期一 19时59分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r
typedef long long LL;

const int maxn = 1280010;

struct node
{
    int l, r, sum, pre, nxt;
} Tree[maxn];

struct node1
{
    int val, pos;
    bool operator < (const node1 &a) const { return val < a.val; }
} a[maxn];

int h[maxn], id[maxn], n, m, num, cnt, p[maxn], Root[maxn], ans, q[5];

inline void Push_up(int root)
{
    Tree[root].sum = Tree[ls(root)].sum + Tree[rs(root)].sum;
    Tree[root].pre = max(Tree[ls(root)].pre, Tree[ls(root)].sum + Tree[rs(root)].pre);
    Tree[root].nxt = max(Tree[rs(root)].nxt, Tree[rs(root)].sum + Tree[ls(root)].nxt);
}

inline void Build(int &root, int l, int r)
{
    root = ++ cnt;
    if ( l == r ) { Tree[root].sum = Tree[root].pre = Tree[root].nxt = 1; return ; }
    int Mid = l + r >> 1;
    Build(ls(root), l, Mid); Build(rs(root), Mid + 1, r);
    Push_up(root);
}

inline int Update(int now, int l, int r, int pos)
{
    int root = ++ cnt; Tree[root] = Tree[now];
    if ( l == r ) { Tree[root].sum = Tree[root].pre = Tree[root].nxt = -1; return root; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) ls(root) = Update(ls(root), l, Mid, pos);
    else rs(root) = Update(rs(root), Mid + 1, r, pos);
    Push_up(root);
    return root;
}

inline int Query_sum(int root, int l, int r, int L, int R)
{
    if ( L > R ) return 0;
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, sum = 0;
    if ( L <= Mid ) sum += Query_sum(ls(root), l, Mid, L, R);
    if ( Mid < R ) sum += Query_sum(rs(root), Mid + 1, r, L, R);
    return sum;
}

inline int Query_pre(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].pre;
    int Mid = l + r >> 1;
    if ( R <= Mid ) return Query_pre(ls(root), l, Mid, L, R);
    else if ( Mid < L ) return Query_pre(rs(root), Mid + 1, r, L, R);
    else
    {
        int sum1 = Query_pre(ls(root), l, Mid, L, Mid);
        int sum2 = Query_pre(rs(root), Mid + 1, r, Mid + 1, R);
        int sum = Query_sum(ls(root), l, Mid, L, Mid);
        return max(sum1, sum + sum2);
    }
}

inline int Query_nxt(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].nxt;
    int Mid = l + r >> 1;
    if ( R <= Mid ) return Query_nxt(ls(root), l, Mid, L, R);
    else if ( Mid < L ) return Query_nxt(rs(root), Mid + 1, r, L, R);
    else
    {
        int sum1 = Query_nxt(ls(root), l, Mid, L, Mid);
        int sum2 = Query_nxt(rs(root), Mid + 1, r, Mid + 1, R);
        int sum = Query_sum(rs(root), Mid + 1, r, Mid + 1, R);
        return max(sum2, sum + sum1);
    }
}

inline bool check(int x)
{
    int sum = Query_sum(Root[x], 1, num, q[2] + 1, q[3] - 1);
    sum += Query_pre(Root[x], 1, num, q[3], q[4]);
    sum += Query_nxt(Root[x], 1, num, q[1], q[2]);
    if ( sum >= 0 ) return true;
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d", &a[i].val); a[i].pos = i; }
    sort(a + 1, a + n + 1);
    a[0].val = -0x3f3f3f3f;
    REP(i, 1, n)
    {
        if ( a[i].val != a[i - 1].val ) ++ num;
        h[a[i].pos] = num; id[num] = a[i].val;
    }
    REP(i, 1, n) a[i].val = h[a[i].pos];
    Build(Root[1], 1, num);
    REP(i, 2, num) 
    {
        int L = 1, R = n, x;
        while ( L <= R ) 
        {
            int Mid = L + R >> 1;
            if ( a[Mid].val < i ) { x = Mid; L = Mid + 1; }
            else R = Mid - 1;
        }
        int root = Root[i - 1];
        while ( a[x].val == i - 1 ) 
        {
            root = Update(root, 1, num, a[x].pos);
            ++ x;
        }
        Root[i] = root;
    }
    scanf("%d", &m);
    REP(o, 1, m)
    {
        REP(i, 1, 4) { scanf("%d", &q[i]); q[i] = (q[i] + ans) % n; }
        sort(q + 1, q + 5);
        REP(i, 1, 4) ++ q[i];
        int L = 1, R = n;
        while ( L <= R ) 
        {
            int Mid = L + R >> 1;
            if ( check(Mid) ) { ans = Mid; L = Mid + 1; }
            else R = Mid - 1;
        }
        ans = id[ans]; printf("%d\n", ans);
    }
    return 0;
}
