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
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 10000010;

int n, q, m;

struct node
{
    int lson, rson, val, lazy;
} Tree[maxn];

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].val = l - m; return ; }
    Tree[root].lson = root << 1;
    Tree[root].rson = root << 1 | 1;
    int Mid = l + r >> 1;
    Build(ls(root), l, Mid); Build(rs(root), Mid + 1, r);
}

inline void Update(int root, int l, int r, int L, int R)
{
    if ( root > R ) return ;
    if ( L <= root && root <= R ) Tree[root].lazy ^= 1;
    Push_down(root);
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d%d", &n, &q);
    m = 1 << (n - 1);
    Build(1, 1, 1 << n);
    REP(i, 1, n)
    {
        int opt, l, r, x; scanf("%d", &opt);
        if ( opt == 1 )
        {
            scanf("%d%d", &l, &r);
            Update(1, 1, m, l, r);
        }
    }
    return 0;
}
