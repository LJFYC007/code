/***************************************************************
	File name: P3377.cpp
	Author: ljfcnyali
	Create time: 2019年07月03日 星期三 13时51分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 4000010;

struct node
{
    int l, r, val;
} Tree[maxn];

int n, m, f[maxn], dis[maxn];

inline int cha(int x)
{
    return x == f[x] ? x : f[x] = cha(f[x]);
    while ( f[x] ) x = f[x];
    return x;
}

inline int Merge(int x, int y)
{
    if ( !x || ! y ) return x + y;
    if ( Tree[x].val > Tree[y].val || (Tree[x].val == Tree[y].val && x > y) ) swap(x, y);
    Tree[x].r = Merge(Tree[x].r, y);
    f[Tree[x].r] = x;
    if ( dis[Tree[x].l] < dis[Tree[x].r] ) swap(Tree[x].l, Tree[x].r); 
    dis[x] = dis[Tree[x].r] + 1;
    return x;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    dis[0] = -1;
    REP(i, 1, n) { scanf("%d", &Tree[i].val); Tree[i].l = Tree[i].r = 0; f[i] = i; }
    scanf("%d", &m);
    REP(i, 1, m)
    {
        int x, y;
        getchar(); getchar(); char c = getchar();
        scanf("%d", &x);
        if ( c == 'M' ) 
        {
            scanf("%d", &y);
            if ( Tree[x].val == -1 || Tree[y].val == -1 || x == y ) continue ;
            int fx = cha(x), fy = cha(y);
            if ( fx == fy ) continue ;
            Merge(fx, fy);
        }
        else
        {
            if ( Tree[x].val == -1 ) { printf("0\n"); continue ; }
            int fx = cha(x); printf("%d\n", Tree[fx].val);
            Tree[fx].val = -1;
            f[Tree[fx].l] = Tree[fx].l; f[Tree[fx].r] = Tree[fx].r;
            f[fx] = Merge(Tree[fx].l, Tree[fx].r);
        }
    }
    return 0;
}
