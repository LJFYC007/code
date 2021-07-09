/***************************************************************
	File name: P2468.cpp
	Author: ljfcnyali
	Create time: 2019年07月08日 星期一 20时14分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r

const int maxn = 210;
const int maxm = 500010;

int n, m, q, f[maxn][maxn][1010], sum[maxn][maxn][1010];
int X1, X2, Y1, Y2, cnt, Root[maxm], a[maxm], tot;

inline int Check(int x)
{
    int tot = sum[X2][Y2][x] - sum[X1 - 1][Y2][x] - sum[X2][Y1 - 1][x] + sum[X1 - 1][Y1 - 1][x];
    return tot;
}

inline void Solve()
{
    REP(i, 1, n) REP(j, 1, m) { int x; scanf("%d", &x); ++ f[i][j][x]; sum[i][j][x] += x; }
    for ( int o = 1000; o >= 0; -- o )
    {
        REP(i, 1, n) REP(j, 1, m) 
        {
            f[i][j][o] += f[i - 1][j][o] + f[i][j - 1][o] - f[i - 1][j - 1][o];
            sum[i][j][o] += sum[i - 1][j][o] + sum[i][j - 1][o] - sum[i - 1][j - 1][o]; 
        }
        REP(i, 1, n) REP(j, 1, m)
        {
            f[i][j][o] += f[i][j][o + 1];
            sum[i][j][o] += sum[i][j][o + 1];
        }
    }
    while ( q -- ) 
    {
        scanf("%d%d%d%d%d", &X1, &Y1, &X2, &Y2, &cnt);
        int l = 0, r = 1000, ans = -1;
        while ( l <= r ) 
        {
            int Mid = l + r >> 1;
            if ( Check(Mid) >= cnt ) { l = Mid + 1; ans = Mid; }
            else r = Mid - 1;
        }
        if ( ans == -1 ) { printf("Poor QLW\n"); continue ; }
        int x = ans + 1, tot = Check(x);
        ans = f[X2][Y2][x] - f[X1 - 1][Y2][x] - f[X2][Y1 - 1][x] + f[X1 - 1][Y1 - 1][x];
        -- x;
        ans += (cnt - tot - 1) / x + 1;
        printf("%d\n", ans);
    }
}

struct node
{
    int l, r, size, sum;
} Tree[maxm * 20];

inline int Build(int l, int r)
{
    int root = ++ tot;
    ls(root) = rs(root) = Tree[root].sum = Tree[root].size = 0;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    ls(root) = Build(l, Mid); rs(root) = Build(Mid + 1, r);
    return root;
}

inline int Update(int now, int l, int r, int val)
{
    int root = ++ tot; Tree[root] = Tree[now];
    ++ Tree[root].size; Tree[root].sum += val;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    if ( val <= Mid ) ls(root) = Update(ls(root), l, Mid, val);
    else rs(root) = Update(rs(root), Mid + 1, r, val);
    return root;
}

inline int Query(int p, int q, int l, int r, int k)
{
    if ( l == r ) return (k - 1) / l + 1;
    int Mid = l + r >> 1;
    int sum = Tree[rs(p)].sum - Tree[rs(q)].sum;
    if ( sum < k ) return Tree[rs(p)].size - Tree[rs(q)].size + Query(ls(p), ls(q), l, Mid, k - sum);
    else return Query(rs(p), rs(q), Mid + 1, r, k);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &q);
    if ( n != 1 ) { Solve(); return 0; }
    REP(i, 1, m) scanf("%d", &a[i]); 
    Root[0] = Build(1, 1000);
    REP(i, 1, m) Root[i] = Update(Root[i - 1], 1, 1000, a[i]);
    while ( q -- ) 
    {
        scanf("%d%d%d%d%d", &X1, &Y1, &X2, &Y2, &cnt);
        int x = Root[Y1 - 1], y = Root[Y2];
//        printf("%d %d\n", Tree[y].sum, Tree[x].sum);
        if ( Tree[y].sum - Tree[x].sum < cnt ) { printf("Poor QLW\n"); continue ; }
        printf("%d\n", Query(y, x, 1, 1000, cnt));
    }
    return 0;
}
