/***************************************************************
	File name: P2487.cpp
	Author: ljfcnyali
	Create time: 2019年09月08日 星期日 20时47分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 50010;

struct Node
{
    int Max, cnt;
} Tree[maxn << 2];
struct node
{
    int h, v, id;
    bool operator < (const node &a) const { return id < a.id; }
} a[maxn];
int f[maxn][2], g[maxn][2], n, num, c[maxn], N, ans, last;

inline bool cmp1(node a, node b) { return a.h < b.h; }

inline bool cmp2(node a, node b) { return a.v < b.v; }

inline bool cmp3(node a, node b) { return a.h > b.h; }

inline void PushUp(int root) { Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max); }

inline void Modify(int root, int l, int r, int pos, int val)
{
    if ( l == r ) { Tree[root].Max = val; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].Max;
    int Mid = l + r >> 1, Max = 0;
    if ( L <= Mid ) Max = max(Max, Query(lson, l, Mid, L, R));
    if ( Mid < R ) Max = max(Max, Query(rson, Mid + 1, r, L, R));
    return Max;
}

inline void CDQ(int l, int r)
{
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    sort(a + l, a + r + 1); CDQ(l, Mid);
    sort(a + l, a + Mid + 1, cmp3); sort(a + Mid + 1, a + r + 1, cmp3);
    int i = l, j = Mid + 1;
    while ( j <= r ) 
    {
        while ( a[i].h >= a[j].h && i <= Mid ) 
        {
            Modify(1, 1, N, a[i].v, dp[a[i].id]); ++ i;
        }
        dp[a[j].id] = max(dp[a[j].id], Query(1, 1, N, a[j].v, N) + 1);
        ++ j;
    }
    REP(j, l, Mid) Modify(1, 1, N, a[j].v, 0);
    CDQ(Mid + 1, r);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d%d", &a[i].h, &a[i].v), a[i].id = i;
    sort(a + 1, a + n + 1, cmp1);
    last = -1; REP(i, 1, n) { if ( a[i].h != last ) ++ num; last = a[i].h; a[i].h = num; }
    sort(a + 1, a + n + 1, cmp2); num = 0;
    last = -1; REP(i, 1, n) { if ( a[i].v != last ) ++ num; last = a[i].v; a[i].v = num; }
    N = num; sort(a + 1, a + n + 1); REP(i, 1, n) dp[i] = 1;
    CDQ(1, n);
    REP(i, 1, n) ans = max(ans, dp[i]);
    printf("%d\n", ans);
    REP(i, 1, n) printf("0 "); puts("");
    return 0;
}
