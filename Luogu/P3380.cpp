/***************************************************************
	File name: P3380.cpp
	Author: ljfcnyali
	Create time: 2019年07月13日 星期六 15时32分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r

const int maxn = 22000010;
const int maxm = 100010;

struct node
{
    int l, r, size;
} Tree[maxn];

struct Node
{
    int opt, l, r, k, pos, id;
} q[maxm];

struct node1
{
    int val, id;
    bool operator < (const node1 &a) const { return val < a.val; }
} a[maxm];

int n, m, Root[maxm], cnt, h[maxm], num, id[maxm];
int tot, p1[maxm], p2[maxm], ans, tot1, tot2;

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

inline int Query1(int l, int r, int val)
{
    int sum = 0;
    if ( l == r ) 
    {
        REP(i, 1, tot1) sum += Tree[p1[i]].size;
        REP(i, 1, tot2) sum -= Tree[p2[i]].size;
        return sum;
    }
    int Mid = l + r >> 1;
    if ( val <= Mid + 1 ) 
    {
        REP(i, 1, tot1) p1[i] = ls(p1[i]);
        REP(i, 1, tot2) p2[i] = ls(p2[i]);
        return Query1(l, Mid, val);
    }
    else 
    {
        REP(i, 1, tot1) sum += Tree[ls(p1[i])].size;
        REP(i, 1, tot2) sum -= Tree[ls(p2[i])].size;
        REP(i, 1, tot1) p1[i] = rs(p1[i]);
        REP(i, 1, tot2) p2[i] = rs(p2[i]);
        return sum + Query1(Mid + 1, r, val);
    }
}

inline int Query2(int l, int r, int k)
{
    if ( l == r ) return l;
    int Mid = l + r >> 1, sum = 0;
    REP(i, 1, tot1) sum += Tree[ls(p1[i])].size;
    REP(i, 1, tot2) sum -= Tree[ls(p2[i])].size;
    if ( k <= sum ) 
    {
        REP(i, 1, tot1) p1[i] = ls(p1[i]);
        REP(i, 1, tot2) p2[i] = ls(p2[i]);
        return Query2(l, Mid, k);
    }
    else
    {
        REP(i, 1, tot1) p1[i] = rs(p1[i]);
        REP(i, 1, tot2) p2[i] = rs(p2[i]);
        return Query2(Mid + 1, r, k - sum);
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
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { scanf("%d", &a[i].val); a[i].id = i; }
    tot = n;
    REP(i, 1, m)
    {
        scanf("%d", &q[i].opt);
        if ( q[i].opt != 3 ) 
        {
            scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].k);
            if ( q[i].opt != 2 ) { a[++ tot].val = q[i].k; a[tot].id = i + n; }
        }
        else 
        {
            scanf("%d%d", &q[i].pos, &q[i].k);
            a[++ tot].val = q[i].k; a[tot].id = i + n;
        }
    }
    sort(a + 1, a + tot + 1);
    a[0].val = -1;
    REP(i, 1, tot)
    {
        if ( a[i].val != a[i - 1].val ) ++ num;
        if ( a[i].id <= n ) h[a[i].id] = num;
        else q[a[i].id - n].k = num;
        id[num] = a[i].val;
    }
//    REP(i, 1, n) cerr << h[i] << " "; cerr << endl;
    ls(0) = rs(0) = Tree[0].size = 0;
    REP(i, 1, n) add(i, h[i], 1);
//    REP(i, 1, cnt) cerr << Root[i] << " "; cerr << endl;
//    REP(i, 1, cnt) cerr << Tree[Root[i]].size << " "; cerr << endl;
    REP(o, 1, m)
    {
        if ( q[o].opt == 1 )
        {
            tot1 = 0;
            for ( int i = q[o].r; i > 0; i -= lowbit(i) ) p1[++ tot1] = Root[i];
            tot2 = 0;
            for ( int i = q[o].l - 1; i > 0; i -= lowbit(i) ) p2[++ tot2] = Root[i];
            ans = Query1(1, num, q[o].k);
            printf("%d\n", ans + 1);
        }
        else if ( q[o].opt == 2 )
        {
            tot1 = 0; 
            for ( int i = q[o].r; i > 0; i -= lowbit(i) ) p1[++ tot1] = Root[i];
            tot2 = 0; 
            for ( int i = q[o].l - 1; i > 0; i -= lowbit(i) ) p2[++ tot2] = Root[i];
            ans = Query2(1, num, q[o].k);
            printf("%d\n", id[ans]);
        }
        else if ( q[o].opt == 3 ) 
        { 
            add(q[o].pos, h[q[o].pos], -1);
            add(q[o].pos, q[o].k, 1);
            h[q[o].pos] = q[o].k;
        }
        else if ( q[o].opt == 4 ) 
        {
            tot1 = 0;
            for ( int i = q[o].r; i > 0; i -= lowbit(i) ) p1[++ tot1] = Root[i];
            tot2 = 0;
            for ( int i = q[o].l - 1; i > 0; i -= lowbit(i) ) p2[++ tot2] = Root[i];
            ans = Query1(1, num, q[o].k);
            if ( ans == 0 ) { printf("-2147483647\n"); continue ; }
            tot1 = 0;
            for ( int i = q[o].r; i > 0; i -= lowbit(i) ) p1[++ tot1] = Root[i];
            tot2 = 0;
            for ( int i = q[o].l - 1; i > 0; i -= lowbit(i) ) p2[++ tot2] = Root[i];
            ans = Query2(1, num, ans);
            printf("%d\n", id[ans]);
        }
        else
        { 
            int sum = 0;
            tot1 = 0;
            for ( int i = q[o].r; i > 0; i -= lowbit(i) ) p1[++ tot1] = Root[i];
            tot2 = 0;
            for ( int i = q[o].l - 1; i > 0; i -= lowbit(i) ) p2[++ tot2] = Root[i];
            REP(i, 1, tot1) sum += Tree[p1[i]].size;
            REP(i, 1, tot2) sum -= Tree[p2[i]].size;
//            printf("%d\n", sum);
            ans = Query1(1, num, q[o].k + 1) + 1;
            if ( ans > sum ) { printf("2147483647\n"); continue ; }
            tot1 = 0;
            for ( int i = q[o].r; i > 0; i -= lowbit(i) ) p1[++ tot1] = Root[i];
            tot2 = 0;
            for ( int i = q[o].l - 1; i > 0; i -= lowbit(i) ) p2[++ tot2] = Root[i];
            ans = Query2(1, num, ans);
            printf("%d\n", id[ans]);
        }
    }
    return 0;
}
