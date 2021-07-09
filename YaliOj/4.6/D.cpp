/***************************************************************
    File name: D.cpp
    Author: ljfcnyali
    Create time: 2019年06月05日 星期三 09时27分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls Treap[root].lson
#define rs Treap[root].rson
#define lss Treap[x].lson
#define rss Treap[x].rson

const int maxn = 2000010;

struct node
{
    int lson, rson, val, size, sum, rank;
} Treap[maxn];

int n, cnt, root = 0;

inline void Zig(int &root)
{
    int lson = ls; 
    Treap[root].lson = Treap[lson].rson;
    Treap[lson].rson = root;
    Treap[lson].size = Treap[root].size;
    Treap[root].size = Treap[ls].size + Treap[rs].size + Treap[root].sum;
    root = lson;
}

inline void Zag(int &root)
{
    int rson = rs;
    Treap[root].rson = Treap[rson].lson;
    Treap[rson].lson = root;
    Treap[rson].size = Treap[root].size;
    Treap[root].size = Treap[ls].size + Treap[rs].size + Treap[root].sum;
    root = rson;
}

inline void Insert(int &root, int val)
{
    if ( !root ) 
    {
        root = ++ cnt;
        Treap[root].lson = Treap[root].rson = 0;
        Treap[root].rank = rand();
        Treap[root].val = val; 
        Treap[root].size = Treap[root].sum = 1;
        return ;
    }
    else ++ Treap[root].size;
    if ( val == Treap[root].val ) ++ Treap[root].sum;
    else if ( val < Treap[root].val ) 
    {
        Insert(ls, val);
        if ( Treap[ls].rank < Treap[root].rank ) Zig(root);
    }
    else 
    { 
        Insert(rs, val);
        if ( Treap[rs].rank < Treap[root].rank ) Zag(root);
    }
}

inline void Delete(int &root, int val)
{
    if ( Treap[root].val == val ) 
    {
        if ( Treap[root].sum > 1 ) { -- Treap[root].sum; -- Treap[root].size; }
        else if ( !ls || !rs ) { root = ls + rs; }
        else if ( Treap[ls].rank < Treap[rs].rank ) { Zig(root); Delete(root, val); }
        else { Zag(root); Delete(root, val); }
        return ;
    }
    -- Treap[root].size;
    if ( val < Treap[root].val ) Delete(ls, val);
    else Delete(rs, val);
}

inline int GetRank(int rank)
{
    int x = root;
    while ( x ) 
    {
        if ( Treap[lss].size < rank && (Treap[lss].size + Treap[x].sum) >= rank ) return Treap[x].val;
        if ( Treap[lss].size >= rank ) x = lss;
        else { rank -= Treap[lss].size + Treap[x].sum; x = rss; }
    }
    return 0;
}

inline int QueryRank(int val)
{
    int x = root, ans = 0;
    while ( x ) 
    {
        if ( val == Treap[x].val ) return ans + Treap[lss].size + 1;
        if ( val < Treap[x].val ) x = lss;
        else { ans += Treap[lss].size + Treap[x].sum; x = rss; }
    }
    return ans;
}

inline int QueryPre(int val)
{
    int x = root, ans = -0x3f3f3f3f;
    while ( x ) 
    {
        if ( Treap[x].val < val ) { ans = max(ans, Treap[x].val); x = Treap[x].rson; }
        else x = Treap[x].lson;
    }
    return ans;
}

inline int QueryNxt(int val)
{
    int x = root, ans = 0x3f3f3f3f;
    while ( x ) 
    {
        if ( Treap[x].val > val ) { ans = min(ans, Treap[x].val); x = Treap[x].lson; }
        else x = Treap[x].rson;
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
//    srand(time(0));
    scanf("%d", &n);
    REP(i, 1, n * 10) Treap[i].size = 0;
    REP(i, 1, n)
    {
        int opt, x; scanf("%d%d", &opt, &x);
        if ( opt == 1 ) Insert(root, x);
        if ( opt == 2 ) Delete(root, x);
        if ( opt == 4 ) printf("%d\n", GetRank(x));
        if ( opt == 3 ) printf("%d\n", QueryRank(x));
        if ( opt == 5 ) printf("%d\n", QueryPre(x));
        if ( opt == 6 ) printf("%d\n", QueryNxt(x));
    }
 //   printf("%d\n", root);
 //   REP(root, 1, 10) printf("%d %d %d\n", Treap[root].val, ls, rs);
    return 0;
}
