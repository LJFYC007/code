/***************************************************************
	File name: CF452F.cpp
	Author: ljfcnyali
	Create time: 2019年09月08日 星期日 15时14分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
#define int long long
typedef long long LL;

const int maxn = 300010;
const int Mod = 103;

int n, a[maxn], p[maxn];
struct node
{
    int val;
} Tree[maxn << 2][2];

inline int Query(int root, int l, int r, int L, int R, int k)
{
    if ( L <= l && r <= R ) return Tree[root][k].val;
    int Mid = l + r >> 1, sum = 0;
    if ( L <= Mid ) sum += Query(lson, l, Mid, L, R, k);
    if ( Mid < R ) sum += Query(rson, Mid + 1, r, L, R, k);
    return sum;
}

inline void PushUp(int root, int k)
{
    Tree[root][k].val = Tree[lson][k].val + Tree[rson][k].val;
}

inline void Modify(int root, int l, int r, int pos, int val, int k)
{
    if ( l == r ) { Tree[root][k].val = val; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val, k);
    else Modify(rson, Mid + 1, r, pos, val, k);
    PushUp(root, k);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    p[0] = 1; REP(i, 1, n) p[i] = p[i - 1] * Mod;
    REP(i, 1, n)
    {
        int len = min(a[i] - 1, n - a[i]);
        int s1 = a[i] - len, s2 = n - a[i] - len + 1;
        int x = Query(1, 1, n, s1, a[i], 0);
        int y = Query(1, 1, n, s2, n - a[i] + 1, 1);
        if ( s1 > s2 ) y = y * p[s1 - s2];
        else x = x * p[s2 - s1];
        // printf("%lld %lld\n", x, y);
        if ( x != y ) { puts("YES"); return 0; }
        Modify(1, 1, n, a[i], p[a[i]], 0);
        // printf("%lld %lld %lld %lld\n", a[i], p[a[i]], n - a[i] + 2, p[n - a[i] + 1]);
        Modify(1, 1, n, n - a[i] + 1, p[n - a[i] + 1], 1);
    }
    puts("NO");
    return 0;
}
