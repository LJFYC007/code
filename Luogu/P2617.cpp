/***************************************************************
    File name: P2617.cpp
    Author: ljfcnyali
    Create time: 2019年07月14日 星期日 20时31分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r

const int maxn = 70000010;
const int maxm = 200010;

struct node
{
    int l, r, size;
} Tree[maxn];

struct node1
{
    int val, id;
    bool operator < (const node1 &a) const { return val < a.val; }
} a[maxm];

struct Node
{
    int opt, l, r, val, pos;
} q[maxm];

int n, m, Root[maxm], cnt, h[maxm], id[maxm];
int p1[maxm], p2[maxm], ans, tot1, tot2, tot, num;

inline int Update(int now, int l, int r, int val, int pos)
{
    int root = ++ cnt; Tree[root] = Tree[now];
    Tree[root].size += pos;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    if ( val <= Mid ) ls(root) = Update(ls(root), l, Mid, val, pos);
    else rs(root) = Update(rs(root), Mid + 1, r, val, pos);
    return root;
}

inline int Query(int l, int r, int k)
{
    if ( l == r ) return id[l];
    int Mid = l + r >> 1, sum = 0;
    REP(i, 1, tot1) sum += Tree[ls(p1[i])].size;
    REP(i, 1, tot2) sum -= Tree[ls(p2[i])].size;
//    cerr << l << " " << r << " " << k << " " << sum << endl;
    if ( k <= sum ) 
    {
        REP(i, 1, tot1) p1[i] = ls(p1[i]);
        REP(i, 1, tot2) p2[i] = ls(p2[i]);
        return Query(l, Mid, k);
    }
    else
    {
        REP(i, 1, tot1) p1[i] = rs(p1[i]);
        REP(i, 1, tot2) p2[i] = rs(p2[i]);
        return Query(Mid + 1, r, k - sum);
    }
}

inline int lowbit(int x) { return x & -x; }

inline void add(int x, int val, int pos)
{
    for ( int i = x; i <= n; i += lowbit(i) )
        Root[i] = Update(Root[i], 1, num, val, pos);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { scanf("%d", &a[i].val); a[i].id = i; }
    tot = n;
    REP(i, 1, m)
    {
        char c[1]; scanf("%s", c);
//        cerr << c[0] << endl;
        q[i].opt = c[0] == 'Q' ? 1 : 2;
        if ( c[0] == 'Q' ) scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].val);
        else 
        {
            scanf("%d%d", &q[i].pos, &q[i].val);
            a[++ tot].val = q[i].val; a[tot].id = i + n;
        }
    }
    sort(a + 1, a + tot + 1);
    a[0].val = -2147483647;
    REP(i, 1, tot)
    {
        if ( a[i].val != a[i - 1].val ) ++ num;
        if ( a[i].id <= n ) h[a[i].id] = num; 
        else q[a[i].id - n].val = num;
        id[num] = a[i].val;
    }
    ls(0) = rs(0) = Tree[0].size = 0;
    REP(i, 1, n) add(i, h[i], 1);
    REP(o, 1, m)
    {
        if ( q[o].opt == 1 )
        {
            tot1 = 0; 
            for ( int i = q[o].r; i > 0; i -= lowbit(i) ) p1[++ tot1] = Root[i];
            tot2 = 0; 
            for ( int i = q[o].l - 1; i > 0; i -= lowbit(i) ) p2[++ tot2] = Root[i];
            ans = Query(1, num, q[o].val);
            printf("%d\n", ans);
        }
        else 
        { 
            add(q[o].pos, h[q[o].pos], -1);
            add(q[o].pos, q[o].val, 1);
            h[q[o].pos] = q[o].val;
        }  
    }
    return 0;
}
