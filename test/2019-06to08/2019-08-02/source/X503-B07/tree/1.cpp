/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2019年08月02日 星期五 08时35分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 10000010;

int n, q;

struct node
{
    int lazy, val;
} Tree[maxn];

inline void paint(int root, int dis, int lazy)
{
    Tree[root].lazy ^= lazy;
    if ( lazy & (1 << dis) ) Tree[root].val ^= 1;
}

inline void Push_down(int root, int dis) 
{
    if ( !Tree[root].lazy ) return ;
    paint(root << 1, dis + 1, Tree[root].lazy);
    paint(root << 1 | 1, dis + 1, Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Update(int root, int l, int r, int L, int R, int dis, int x)
{
    if ( L <= l && r <= R ) 
    { 
        paint(root, dis, 1 << x);
        return ;
    }
    Push_down(root, dis);
    int Mid = l + r >> 1;
    if ( !Tree[root].val )
    {
        if ( L <= Mid ) Update(root << 1, l, Mid, L, R, dis + 1, x);
        if ( Mid < R ) Update(root << 1 | 1, Mid + 1, r, L, R, dis + 1, x);
    }
    else
    {
        if ( L <= Mid ) Update(root << 1 | 1, Mid + 1, r, L + Mid - l + 1, R + Mid - l + 1, dis + 1, x);
        if ( Mid < R ) Update(root << 1, l, Mid, L - Mid + l - 1, R - Mid + l - 1, dis + 1, x);
    }
}

inline int Query(int root, int l, int r, int x, int dis)
{
    if ( l == r ) return l;
    Push_down(root, dis);
    int Mid = l + r >> 1;
    if ( !Tree[root].val )
    {
        if ( x <= Mid ) return Query(root << 1, l, Mid, x, dis + 1);
        return Query(root << 1 | 1, Mid + 1, r, x, dis + 1);
    }
    if ( x <= Mid ) return Query(root << 1 | 1, Mid + 1, r, x + Mid - l + 1, dis + 1);
    return Query(root << 1, l, Mid, x - Mid + l - 1, dis + 1);
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d%d", &n, &q);
    REP(i, 1, q)
    {
        int opt, l, r, x; scanf("%d", &opt);
        if ( opt == 1 ) 
        { 
            scanf("%d%d", &l, &r); 
            REP(j, 0, n - 1)
            {
                int L = max(l, (1 << j)) - (1 << j), R = min(r, (1 << j + 1) - 1) - (1 << j);
                if ( L <= R ) Update(1, 0, (1 << j) - 1, L, R, 0, j);
            }
        }
        else { scanf("%d", &x); printf("%d\n", Query(1, 0, (1 << n) - 1, x - 1, 0) + 1); }
    }
    return 0;
}
