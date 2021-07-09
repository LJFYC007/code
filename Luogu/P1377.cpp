/***************************************************************
	File name: P1377.cpp
	Author: ljfcnyali
	Create time: 2019年06月18日 星期二 16时29分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Treap[x].lson
#define rs(x) Treap[x].rson

const int maxn = 100010;

struct node
{
    int lson, rson, val, rank;
} Treap[maxn];

int n, root, tot;

inline void Zig(int &x)
{
    int y = ls(x);
    ls(x) = rs(y);
    rs(y) = x;
    x = y;
}

inline void Zag(int &x)
{
    int y = rs(x);
    rs(x) = ls(y);
    ls(y) = x;
    x = y;
}

inline void Insert(int &x, int val)
{
    if ( !x ) 
    {
        x = ++ tot;
        ls(x) = rs(x) = 0; Treap[x].val = val; 
        Treap[x].rank = rand();
        return ;
    }
    if ( val <= Treap[x].val )
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

inline void out(int x)
{
    cerr << Treap[ls(x)].val << " " << Treap[rs(x)].val << endl;
    if ( ls(x) ) out(ls(x));
    printf("%d ", Treap[x].val);
    if ( rs(x) ) out(rs(x));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) { int x; scanf("%d", &x); Insert(root, x); }    
    out(root);
    puts("");
    return 0;
}
