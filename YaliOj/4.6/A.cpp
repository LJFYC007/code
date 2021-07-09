/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年06月06日 星期四 10时25分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Treap[x].lson
#define rs(x) Treap[x].rson

const int maxn = 2000010;

int n, ans, root, cnt, a[maxn];

struct node
{
    int lson, rson, val, size, sum, rank;
} Treap[maxn];

inline void Zig(int &x)
{
    int y = ls(x);
    ls(x) = rs(y);
    rs(y) = x;
    Treap[y].size = Treap[x].size;
    Treap[x].size = Treap[ls(x)].size + Treap[rs(x)].size + Treap[x].sum;
    x = y;
}

inline void Zag(int &x)
{
    int y = rs(x);
    rs(x) = ls(y);
    ls(y) = x;
    Treap[y].size = Treap[x].size;
    Treap[x].size = Treap[ls(x)].size + Treap[rs(x)].size + Treap[x].sum;
    x = y;
}

inline void Insert(int &x, int val)
{
    if ( !x ) 
    {
        x = ++ cnt;
        Treap[x].val = val; Treap[x].lson = Treap[x].rson = 0;
        Treap[x].size = Treap[x].sum = 1;
        Treap[x].rank = rand();
        return ;
    }
    else ++ Treap[x].size;
    if ( val == Treap[x].val ) ++ Treap[x].sum;
    else if ( val < Treap[x].val ) 
    {
        Insert(ls(x), val);
        if ( Treap[ls(x)].rank < Treap[x].rank ) Zig(x);
    }
    else
    {
        Insert(rs(x), val);
        if ( Treap[rs(x)].rank < Treap[x].rank ) Zag(x);
    }
}

inline int QueryPre(int val)
{
    int x = root, ans = -0x3f3f3f3f;
    while ( x ) 
    {
        if ( Treap[x].val <= val ) { ans = max(ans, Treap[x].val); x = rs(x); }
        else x = ls(x);
    }
    return ans;
}

inline int QueryNxt(int val)
{
    int x = root, ans = 0x3f3f3f3f;
    while ( x ) 
    {
        if ( Treap[x].val >= val ) { ans = min(ans, Treap[x].val); x = ls(x); }
        else x = rs(x);
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &a[1]); ans = a[1]; Insert(root, a[1]);
    REP(i, 2, n)
    {
/*        if ( i == 8 )
        {
            cout << root << endl;
            REP(j, 1, cnt) printf("%d %d %d\n", Treap[j].val, ls(j), rs(j));
        }*/
        scanf("%d", &a[i]);
        int pre = QueryPre(a[i]), nxt = QueryNxt(a[i]);
        if ( pre > a[i] ) pre = -0x3f3f3f3f; 
        if ( nxt < a[i] ) nxt = 0x3f3f3f3f;
//        printf("%d %d %d\n", pre, nxt, min(a[i] - pre, nxt - a[i]));
        ans += min(a[i] - pre, nxt - a[i]);
        Insert(root, a[i]);
    }
    printf("%d\n", ans);
    return 0;
}
