/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年06月06日 星期四 12时01分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Treap[x][num].lson
#define rs(x) Treap[x][num].rson

const int maxn = 1000010;
const int Mod = 1000000;

struct node
{
    int lson, rson, val, sum, size, rank;
} Treap[maxn][2];

int n, cnt[2], root[2], ans, s1, s0;

inline void Zig(int &x, int num)
{
    int y = ls(x);
    ls(x) = rs(y);
    rs(y) = x;
    Treap[y][num].size = Treap[x][num].size;
    Treap[x][num].size = Treap[ls(x)][num].size + Treap[rs(x)][num].size + Treap[x][num].sum;
    x = y;
}

inline void Zag(int &x, int num)
{
    int y = rs(x);
    rs(x) = ls(y);
    ls(y) = x;
    Treap[y][num].size = Treap[x][num].size;
    Treap[x][num].size = Treap[ls(x)][num].size + Treap[rs(x)][num].size + Treap[x][num].sum;
    x = y;
}

inline void Insert(int &x, int val, int num)
{
    if ( !x ) 
    {
        x = ++ cnt[num]; Treap[x][num].val = val;
        ls(x) = rs(x) = 0; Treap[x][num].size = Treap[x][num].sum = 1;
        Treap[x][num].rank = rand();
        return ;
    }
    ++ Treap[x][num].size;
    if ( Treap[x][num].val == val ) ++ Treap[x][num].sum;
    else if ( val < Treap[x][num].val )
    {
        Insert(ls(x), val, num);
        if ( Treap[ls(x)][num].rank < Treap[x][num].rank ) Zig(x, num);
    }
    else 
    {
        Insert(rs(x), val, num);
        if ( Treap[rs(x)][num].rank < Treap[x][num].rank ) Zag(x, num);
    }
}

inline void Delete(int &x, int val, int num)
{
    if ( Treap[x][num].val == val ) 
    {
        if ( Treap[x][num].sum > 1 ) { -- Treap[x][num].sum; -- Treap[x][num].size; }
        else if ( !ls(x) || !rs(x) ) x = ls(x) + rs(x);
        else if ( Treap[ls(x)][num].rank < Treap[rs(x)][num].rank ) { Zig(x, num); Delete(x, val, num); }
        else { Zag(x, num); Delete(x, val, num); }
        return ;
    }
    -- Treap[x][num].size;
    if ( val < Treap[x][num].val ) Delete(ls(x), val, num);
    else Delete(rs(x), val, num);
}

inline int QueryPre(int val, int num)
{
    int x = root[num], ans = -0x3f3f3f3f;
    while ( x ) 
    {
        if ( Treap[x][num].val <= val ) { ans = max(ans, Treap[x][num].val); x = rs(x); }
        else x = ls(x);
    }
    return ans;
}

inline int QueryNxt(int val, int num)
{
    int x = root[num], ans = 0x3f3f3f3f;
    while ( x ) 
    {
        if ( Treap[x][num].val >= val ) { ans = min(ans, Treap[x][num].val); x = ls(x); }
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
    scanf("%d", &n);
    REP(i, 1, n)
    {
        int a, b; scanf("%d%d", &a, &b);
        if ( a == 0 ) 
        {
            if ( s1 == 0 ) { Insert(root[0], b, 0); ++ s0; }
            else 
            {
                int Pre = QueryPre(b, 1), Nxt = QueryNxt(b, 1);
                if ( Pre > b ) Pre = -0x3f3f3f3f;
                if ( Nxt < b ) Nxt = 0x3f3f3f3f;
                if ( (b - Pre) <= (Nxt - b) ) { ans = (ans + b - Pre) % Mod; Delete(root[1], Pre, 1); }
                else { ans = (ans + Nxt - b) % Mod; Delete(root[1], Nxt, 1); }
                -- s1;
            }
        }
        else 
        {
            if ( s0 == 0 ) { Insert(root[1], b, 1); ++ s1; }
            else 
            {
                int Pre = QueryPre(b, 0), Nxt = QueryNxt(b, 0);
                if ( Pre > b ) Pre = -0x3f3f3f3f;
                if ( Nxt < b ) Nxt = 0x3f3f3f3f;
                if ( (b - Pre) <= (Nxt - b) ) { ans = (ans + b - Pre) % Mod; Delete(root[0], Pre, 0); }
                else { ans = (ans + Nxt - b) % Mod; Delete(root[0], Nxt, 0); }
                -- s0;
            }
        }
//        cerr << ans << endl;
    }
    printf("%d\n", ans);
    return 0;
}
