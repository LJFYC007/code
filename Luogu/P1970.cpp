/***************************************************************
	File name: P1970.cpp
	Author: ljfcnyali
	Create time: 2019年08月15日 星期四 20时33分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x][opt].l
#define rs(x) Tree[x][opt].r
typedef long long LL;

const int maxn = 100010;

int n, h[maxn], f[maxn][2], num = 1000000, cnt[2];

struct node
{
    int l, r, Max;
} Tree[maxn << 2][2];

inline int Query(int root, int l, int r, int L, int R, int opt)
{
    if ( !root ) return 0; 
    if ( L <= l && r <= R ) return Tree[root][opt].Max;
    int Mid = l + r >> 1, sum = 0;
    if ( L <= Mid ) sum = max(sum, Query(ls(root), l, Mid, L, R, opt));
    if ( Mid < R ) sum = max(sum, Query(rs(root), Mid + 1, r, L, R, opt));
    return sum;
}

inline void Modify(int &root, int l, int r, int pos, int val, int opt)
{
    if ( !root ) root = ++ cnt[opt];
    if ( l == r ) { Tree[root][opt].Max = max(Tree[root][opt].Max, val); return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, val, opt);
    else Modify(rs(root), Mid + 1, r, pos, val, opt);
    Tree[root][opt].Max = max(Tree[ls(root)][opt].Max, Tree[rs(root)][opt].Max);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    int root1 = 0, root2 = 0;
    REP(i, 1, n) 
    {
        scanf("%d", &h[i]);
        f[i][0] = max(Query(root1, 0, num, 0, h[i] - 1, 1) + 1, f[i - 1][0]);
        f[i][1] = max(Query(root2, 0, num, h[i] + 1, num, 0) + 1, f[i - 1][1]);
        // cerr << f[i][0] << " " << f[i][1] << endl;
        Modify(root1, 0, num, h[i], f[i][0], 0);
        Modify(root2, 0, num, h[i], f[i][1], 1);
    }
    printf("%d\n", max(f[n][0], f[n][1]));
    return 0;
}
