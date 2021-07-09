/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年06月06日 星期四 14时43分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Treap[x].lson
#define rs(x) Treap[x].rson

const int maxn = 1000010;

struct node
{
    int lson, rson, val, size, sum, rank;
} Treap[maxn];

int sum, n, Min, ans, root, cnt;

inline void Zig(int &x)
{
    int y = ls(x);
    ls(x) = rs(y);
    rs(y) = x;
    Treap[y].size = Treap[x].size;
    Treap[x].size = Treap[ls(x)].size + Treap[rs(x)].size + 1;
    x = y;
}

inline void Zag(int &x)
{
    int y = rs(x);
    rs(x) = ls(y);
    ls(y) = x;
    Treap[y].size = Treap[x].size;
    Treap[x].size = Treap[ls(x)].size + Treap[rs(x)].size + 1;
    x = y;
}

inline void Insert(int &x, int val)
{
    if ( !x ) 
    {
        x = ++ cnt; ls(x) = rs(x) = 0;
        Treap[x].val = val; Treap[x].size = Treap[x].sum = 1;
        Treap[x].rank = rand();
        return ;
    }
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
    Treap[x].size = Treap[ls(x)].size + Treap[rs(x)].size + 1;
}

inline void Delete(int val)
{
    int x = root, last = -1;
    while ( x ) 
    {
        if ( Treap[x].val < val ) 
        {
            ans += Treap[x].sum + Treap[ls(x)].sum;
            if ( last == -1 ) 
            {
                root = rs(x); x = rs(x); continue ;
            }
            ls(last) = rs(x); 
            Treap[last].size = Treap[ls(last)].size + Treap[rs(last)].size + 1; 
            last = x; x = rs(x);
        }
        else if ( Treap[x].val == val ) 
        {
            ans += Treap[ls(x)].size;
            if ( Treap[x].sum > 1 )
            {
                -- Treap[x].sum; Treap[x].size = 1 + Treap[rs(x)].sum;
                ls(x) = 0; return ;
            }
            else 
            {
                if ( last == -1 ) { root = rs(x); return ; }
                ls(last) = rs(x); 
                Treap[last].size = Treap[ls(last)].size + Treap[rs(last)].size + 1; 
                last = x; x = rs(x);
            }
        }
        else { last = x; x = ls(x); }
    }
}

inline int QueryRank(int k)
{
    int x = root;
    if ( Treap[x].size < k ) return -1;
    while ( x ) 
    {
        if ( k <= Treap[rs(x)].size ) x = rs(x);
        else if ( k <= (Treap[rs(x)].size + 1) ) return Treap[x].val + sum;
        else { k -= Treap[rs(x)].size + 1; x = ls(x); }
    }
    return -1;
}

inline void Update(int x)
{
    if ( !x ) return ;
    Treap[x].size = Treap[ls(x)].size + Treap[rs(x)].size + 1;
    Update(ls(x)); Update(rs(x));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &Min);
    REP(i, 1, n)
    {
        //getchar(); 
        getchar(); char c = getchar(); int x; scanf("%d", &x); 
//        cerr << c << endl;
        if ( c == 'I' ) 
        {
            if ( x < Min ) continue ;
            Insert(root, x - sum);
        }
        if ( c == 'A' ) sum += x;
        if ( c == 'S' ) 
        {
            sum -= x; Insert(root, Min - sum);
            Delete(Min - sum);
            Update(root);
        }
        if ( c == 'F' ) printf("%d\n", QueryRank(x));
    }
    printf("%d\n", ans);
    return 0;
}

