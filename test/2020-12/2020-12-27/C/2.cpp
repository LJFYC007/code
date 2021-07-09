/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年12月27日 星期日 10时32分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, k, h[maxn], a[maxn], now;
struct node { int sum1, sum2, sum, ans, lazy, vis, len; } Tree[maxn << 2];

inline void PushUp(int root)
{
    Tree[root].vis = Tree[lson].vis | Tree[rson].vis;
    Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
    Tree[root].ans = Tree[lson].ans + Tree[rson].ans + Tree[lson].sum * Tree[rson].len;
    Tree[root].sum1 = Tree[lson].sum1 + Tree[rson].sum1;
    Tree[root].sum2 = Tree[lson].sum2 + Tree[rson].sum2;
}

inline void PushDown(int root)
{
}

inline void Modify(int root, int l, int r, int pos, int val)
{
    Tree[root].len = r - l + 1;
    if ( l == r ) 
    { 
        Tree[root].sum += val; Tree[root].ans += val; 
        val = Tree[root].sum;
        Tree[root].vis = abs(val) > k;
        if ( val < k ) Tree[root].sum1 = k - val;
        if ( val > -k ) Tree[root].sum2 = val + k;
        return ; 
    }
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);
    PushUp(root);
}

inline int Query1(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) { now += Tree[root].sum; return (now - Tree[root].sum) * Tree[root].len + Tree[root].ans; }
    int Mid = l + r >> 1, ret = 0; PushDown(root);
    if ( L <= Mid ) ret += Query1(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query1(rson, Mid + 1, r, L, R);
    return ret;
}

inline int Query2(int root, int l, int r, int L, int R)
{
    if ( L > R ) return 0; 
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 0; PushDown(root);
    if ( L <= Mid ) ret += Query2(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query2(rson, Mid + 1, r, L, R);
    return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &k);
    REP(i, 1, n) { scanf("%lld", &h[i]); a[i] = h[i] - h[i - 1]; }
    int N = n + 1;
    REP(i, 1, n) Modify(1, 1, N, i, a[i]);
    while ( m -- ) 
    {
        int op, l, r, c; scanf("%lld%lld%lld", &op, &l, &r);
        if ( op == 1 ) { now = Query2(1, 1, N, 1, l - 1); printf("%lld\n", Query1(1, 1, N, l, r)); }
        else if ( op == 2 ) 
        {
            scanf("%lld", &c); a[l] += c; a[r + 1] -= c;
            Modify(1, 1, N, l, c); Modify(1, 1, N, r + 1, -c);
        }
        else if ( op == 3 ) 
        {
            REP(i, l + 1, r)
            {
                if ( abs(a[i]) <= k ) continue ;
                if ( a[i] > k ) 
                {
                    REP(j, i + 1, r) if ( a[j] < k ) 
                    {
                        int t = min(a[i] - k, k - a[j]);
                        Modify(1, 1, N, i, -t); Modify(1, 1, N, j, t);
                        a[i] -= t; a[j] += t; 
                        if ( a[i] == k ) break ; 
                    }
                    
                    Modify(1, 1, N, r + 1, a[i] - k);
                    Modify(1, 1, N, i, k - a[i]);
                    a[r + 1] += a[i] - k; a[i] = k;
                }
                else 
                {
                    continue ; 
                    for ( int j = i - 1; j > l; -- j ) if ( a[j] > -k ) 
                    {
                        int t = min(-k - a[i], a[j] + k);
                        Modify(1, 1, N, i, t); Modify(1, 1, N, j, -t);
                        a[i] += t; a[j] -= t;
                        if ( a[i] == -k ) break ; 
                    }
                    Modify(1, 1, N, l, a[i] + k);
                    Modify(1, 1, N, i, -k - a[i]);
                    a[l] -= -k - a[i]; a[i] = -k;
                }
            }
        }
    }
    return 0;
}
