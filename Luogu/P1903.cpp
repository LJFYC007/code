/***************************************************************
	File name: P1903.cpp
	Author: ljfcnyali
	Create time: 2019年07月02日 星期二 14时29分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 5000010;

struct node
{
    int l, r, pre, id, p;
} q[maxn];

struct Node
{
    int pos, val;
} t[maxn];

int n, m, a[maxn], ans[maxn], sum, size[maxn], block, tot, cnt;

inline int cmp(node a, node b) 
{
    if ( a.id != b.id ) return a.id < b.id;
    if ( a.r != b.r ) return a.r < b.r;
    return a.pre < b.pre;
}

inline void del(int x) { -- size[a[x]]; if ( !size[a[x]] ) -- sum; }

inline void add(int x) { ++ size[a[x]]; if ( size[a[x]] == 1 ) ++ sum; }

inline void work(int x, int i)
{
    if ( q[i].l <= t[x].pos && t[x].pos <= q[i].r )
    {
        if ( -- size[a[t[x].pos]] == 0 ) -- sum;
        if ( ++ size[t[x].val] == 1 ) ++ sum;
    }
    swap(t[x].val, a[t[x].pos]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    block = sqrt(n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, m) 
    {
        getchar(); char c = getchar();
        if ( c == 'Q' ) 
        {
            ++ tot;
            scanf("%d%d", &q[tot].l, &q[tot].r);
            q[tot].pre = cnt; q[tot].id = (q[tot].l - 1) / block + 1;
            q[tot].p = tot;
        }
        else
        {
            ++ cnt;
            scanf("%d%d", &t[cnt].pos, &t[cnt].val);
        }
    }
    sort(q + 1, q + tot + 1, cmp);
    int l = q[1].l, r = q[1].l - 1, num = 0;
    REP(i, 1, tot)
    {
        while ( l < q[i].l ) del(l ++);
        while ( l > q[i].l ) add(-- l);
        while ( r < q[i].r ) add(++ r);
        while ( r > q[i].r ) del(r --);
        while ( num < q[i].pre ) work(++ num, i);
        while ( num > q[i].pre ) work(num --, i);
        ans[q[i].p] = sum;
    }
    REP(i, 1, tot) printf("%d\n", ans[i]);
    return 0;
}
