/***************************************************************
	File name: b.cpp
	Author: ljfcnyali
	Create time: 2019年08月13日 星期二 14时56分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r
typedef long long LL;

const int maxn = 100010;

int n, k, id[maxn], N, Root[maxn], num = 1000000000, ans, cnt;

struct Node
{
    int l, r, sum;
} Tree[maxn << 10];

struct node
{
    int x, r, q, val;
    bool operator < (const node &a) const { return r > a.r; }
} a[maxn];

inline int cmp(node a, node b) { return a.q < b.q; }

inline int Query(int root, int l, int r, int L, int R)
{
    if ( !root || !Tree[root].sum ) return 0;
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, sum = 0;
    if ( L <= Mid ) sum += Query(ls(root), l, Mid, L, R);
    if ( Mid < R ) sum += Query(rs(root), Mid + 1, r, L, R);
    return sum;
}

inline void Update(int &root, int l, int r, int val)
{
    if ( !root ) root = ++ cnt;
    ++ Tree[root].sum;
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    if ( val <= Mid ) Update(ls(root), l, Mid, val);
    else Update(rs(root), Mid + 1, r, val);
}

int main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%d%d", &n, &k);
    REP(i, 1, n) scanf("%d%d%d", &a[i].x, &a[i].r, &a[i].q);
    sort(a + 1, a + n + 1, cmp); a[0].q = -1;
    REP(i, 1, n)
    {
        if ( a[i].q != a[i - 1].q ) ++ N;
        a[i].val = N; id[N] = a[i].q;
    }
    sort(a + 1, a + n + 1);
    REP(i, 1, n)
    {
        int x = a[i].val;
        while ( id[x] >= a[i].q - k && id[x] <= a[i].q + k ) 
        {
            ans += Query(Root[x], 0, num, a[i].x - a[i].r, a[i].x + a[i].r);
            -- x;
        }
        x = a[i].val + 1;
        while ( id[x] >= a[i].q - k && id[x] <= a[i].q + k ) 
        {
            ans += Query(Root[x], 0, num, a[i].x - a[i].r, a[i].x + a[i].r);
            ++ x;
        }
        Update(Root[a[i].val], 0, num, a[i].x);
    }
    printf("%d\n", ans);
    return 0;
}
