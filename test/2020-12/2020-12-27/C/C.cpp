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
struct Node { int sum1, sum2, sum, ans, lazy, len; } Tree[maxn << 2];
set<int> Set1, Set2;

inline int calc(int n) { return n * (n + 1) / 2; } 

inline void PushUp(int root)
{
    Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
    Tree[root].ans = Tree[lson].ans + Tree[rson].ans + Tree[lson].sum * Tree[rson].len;
    Tree[root].sum1 = Tree[lson].sum1 + Tree[rson].sum1;
    Tree[root].sum2 = Tree[lson].sum2 + Tree[rson].sum2;
}

inline void PushTag(int root, int val)
{
    Tree[root].sum = val * k * Tree[root].len;
    Tree[root].ans = val * k * calc(Tree[root].len);
    if ( val == 1 ) { Tree[root].sum1 = 0; Tree[root].sum2 = 2 * k * Tree[root].len; } 
    else { Tree[root].sum2 = 0; Tree[root].sum1 = 2 * k * Tree[root].len; } 
    Tree[root].lazy = val;
}

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;     
    PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Modify1(int root, int l, int r, int L, int R, int op)
{
    if ( L > R ) return ; 
    if ( L <= l && r <= R ) { PushTag(root, op); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify1(lson, l, Mid, L, R, op);
    if ( Mid < R ) Modify1(rson, Mid + 1, r, L, R, op);
    PushUp(root);
}

inline int Get(int root, int l, int r, int L, int R, int op)
{
    if ( L > R ) return 0; 
    if ( L <= l && r <= R ) return op == 1 ? Tree[root].sum1 : Tree[root].sum2;
    int Mid = l + r >> 1, ret = 0; PushDown(root);
    if ( L <= Mid ) ret += Get(lson, l, Mid, L, R, op);
    if ( Mid < R ) ret += Get(rson, Mid + 1, r, L, R, op);
    return ret;
}

inline void Modify(int root, int l, int r, int pos, int val)
{
    Tree[root].len = r - l + 1;
    if ( l == r ) 
    { 
        Tree[root].sum += val; Tree[root].ans += val; val = Tree[root].sum; 
        Tree[root].sum1 = Tree[root].sum2 = 0;
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
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &k);
    REP(i, 1, n) { scanf("%lld", &h[i]); a[i] = h[i] - h[i - 1]; }
    int N = n + 1;
    REP(i, 1, n) Modify(1, 1, N, i, a[i]);
    REP(i, 1, n) if ( a[i] > k ) Set1.insert(i); else if ( a[i] < -k ) Set2.insert(i);
    Set1.insert(n + 1); Set2.insert(n + 1);
    while ( m -- ) 
    {
        int op, l, r, c; scanf("%lld%lld%lld", &op, &l, &r);
        if ( op == 1 ) { now = Query2(1, 1, N, 1, l - 1); printf("%lld\n", Query1(1, 1, N, l, r)); }
        else if ( op == 2 ) 
        {
            scanf("%lld", &c); Modify(1, 1, N, l, c); Modify(1, 1, N, r + 1, -c);
            Set1.insert(l); Set1.insert(r + 1); Set2.insert(l); Set2.insert(r + 1);
        }
        else if ( op == 3 ) 
        {
            Set1.insert(r + 1); Set2.insert(l);
            auto it = Set1.lower_bound(l + 1); 
            while ( *it <= r ) 
            {
                auto nxt = it; ++ nxt; 
                int t = 0, i = *it, sum = Query2(1, 1, N, i, i) - k, L = i + 1, R = *nxt - 1, pos = i;
                if ( Query2(1, 1, N, i, i) <= k ) goto Next1 ;
                while ( L <= R ) 
                {
                    int Mid = (L + R) >> 1;
                    if ( Get(1, 1, N, i + 1, Mid, 1) < sum ) { pos = Mid; L = Mid + 1; }
                    else R = Mid - 1;
                }
                t = Get(1, 1, N, i + 1, pos, 1); Modify1(1, 1, N, i + 1, pos, 1);
                Modify(1, 1, N, i, -sum); Modify(1, 1, N, pos + 1, sum - t);
Next1 : ;
                Set1.erase(it); it = nxt; 
            }

            it = -- Set2.upper_bound(r);
            while ( *it > l ) 
            {
                auto pre = it; -- pre;
                int t = 0, i = *it, sum = -k - Query2(1, 1, N, i, i), L = *pre + 1, R = i - 1, pos = i;
                if ( Query2(1, 1, N, i, i) >= -k ) goto Next2 ;
                while ( L <= R ) 
                {
                    int Mid = (L + R) >> 1;
                    if ( Get(1, 1, N, Mid, i - 1, 0) < sum ) { pos = Mid; R = Mid - 1; }
                    else L = Mid + 1;
                }
                t = Get(1, 1, N, pos, i - 1, 0); Modify1(1, 1, N, pos, i - 1, -1);
                Modify(1, 1, N, i, sum); Modify(1, 1, N, pos - 1, t - sum);
Next2 : ;
                Set2.erase(it); it = pre;
            }
        }
    }
    return 0;
}
