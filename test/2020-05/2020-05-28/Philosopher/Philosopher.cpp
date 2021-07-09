/***************************************************************
	File name: Philosopher.cpp
	Author: ljfcnyali
	Create time: 2020年05月28日 星期四 16时09分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 1e6 + 10;
const int N = 1e18;

int n, m, a[maxn], Root[maxn], tot, h[maxn];
struct node { __int128 sum; int size, lson, rson; } Tree[maxn << 5];
struct Node
{
    __int128 sum[maxn];

    inline void PushUp(int root) 
    { 
        sum[root] = sum[root << 1] * sum[root << 1 | 1];
        while ( sum[root] > N ) sum[root] /= 1000;
    }

    inline void Modify(int root, int l, int r, int pos, int val)
    {
        if ( l == r ) { sum[root] = val; return ; }
        int Mid = l + r >> 1;
        if ( pos <= Mid ) Modify(root << 1, l, Mid, pos, val);
        else Modify(root << 1 | 1, Mid + 1, r, pos, val);
        PushUp(root);
    }
    
    inline int Query(int root, int l, int r, int L, int R)
    {
        if ( L <= l && r <= R ) return sum[root];
        int Mid = l + r >> 1; __int128 ret = 1;
        if ( L <= Mid ) ret *= Query(root << 1, l, Mid, L, R);
        if ( Mid < R ) ret *= Query(root << 1 | 1, Mid + 1, r, L, R);
        while ( ret > N ) ret /= 1000;
        return ret;
    }
} A;
set<int> Set;

inline int power(__int128 a, int b)
{
    __int128 r = 1;
    while ( b ) 
    {
        if ( b & 1 ) { r *= a; while ( r > N ) r /= 1000; }
        a *= a; b >>= 1; while ( a > N ) a /= 1000;
    }
    return r;
}

inline void PushUp(int root)
{
    Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size;
    Tree[root].sum = 1;
    if ( ls(root) ) Tree[root].sum *= Tree[ls(root)].sum;
    if ( rs(root) ) Tree[root].sum *= Tree[rs(root)].sum;
    while ( Tree[root].sum > N ) Tree[root].sum /= 1000;
}

inline void Modify(int &root, int l, int r, int val)
{
    if ( !root ) root = ++ tot; 
    if ( l == r ) { Tree[root].sum = val; Tree[root].size = 1; return ; }
    int Mid = l + r >> 1;
    if ( val <= Mid ) Modify(ls(root), l, Mid, val);
    else Modify(rs(root), Mid + 1, r, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( !root || R == 0 ) return 1;
    if ( l == r ) return power(l, R - L + 1);
    if ( L == 0 && Tree[root].size <= R ) return Tree[root].sum;
    int sum = Tree[ls(root)].size, Mid = l + r >> 1;; __int128 ret = 1;
    if ( L <= sum ) ret *= Query(ls(root), l, Mid, L, min(R, sum));
    if ( sum < R ) ret *= Query(rs(root), Mid + 1, r, max(0ll, L - sum), R - sum);
    while ( ret > N ) ret /= 1000;
    return ret;
}

inline void Merge(int &p, int &q, int l, int r)
{
    if ( !p || !q ) { p += q; return ; }
    if ( l == r ) 
    { 
        Tree[p].size += Tree[q].size; 
        Tree[p].sum = power(l, Tree[p].size);
        return ;
    }
    int Mid = l + r >> 1;
    Merge(ls(p), ls(q), l, Mid);
    Merge(rs(p), rs(q), Mid + 1, r);
    PushUp(p); 
}

inline void Split(int root, int &a, int &b, int l, int r, int k)
{
    if ( !root ) { a = b = 0; return ; }
    if ( Tree[root].size == k ) { a = root; b = 0; return ; }
    if ( k == 0 ) { a = 0; b = root; return ; }
    if ( l == r ) 
    {
        a = ++ tot; b = ++ tot;
        Tree[a].size = k; Tree[b].size = Tree[root].size - k;
        Tree[a].sum = power(l, Tree[a].size);
        Tree[b].sum = power(l, Tree[b].size);
        return ;
    }
    int Mid = l + r >> 1;
    if ( k <= Tree[ls(root)].size ) 
    { 
        b = root; a = ++ tot; 
        Split(ls(root), ls(a), ls(b), l, Mid, k); 
    }
    else 
    { 
        a = root; b = ++ tot;
        Split(rs(root), rs(a), rs(b), Mid + 1, r, k - Tree[ls(root)].size); 
    }
    PushUp(a); PushUp(b); 
}

inline void HaSplit(int x, int size)
{
    if ( size == 0 || size == Tree[Root[x]].size ) return ;
    int t = x + size; Set.insert(t);
    if ( h[x] == 0 ) size = Tree[Root[x]].size - size;
    Split(Root[x], Root[x], Root[t], 1, n, size);
    h[t] = h[x];
    if ( h[x] == 0 ) swap(Root[x], Root[t]);
    A.Modify(1, 1, n, x, Tree[Root[x]].sum);
    A.Modify(1, 1, n, t, Tree[Root[t]].sum);
}

inline void HaMerge(int l, int r)
{
    auto now = Set.upper_bound(l);
    while ( *now <= r ) 
    {
        Merge(Root[l], Root[*now], 1, n);
        A.Modify(1, 1, n, *now, 1);
        Root[*now] = 0; 
        auto it = now; ++ now; Set.erase(it);
    }
    A.Modify(1, 1, n, l, Tree[Root[l]].sum);
}

inline int Get(int x, int l, int r)
{
    if ( h[x] == 1 ) return Query(Root[x], 1, n, l, r);
    return Query(Root[x], 1, n, Tree[Root[x]].size - r + 1, Tree[Root[x]].size - l + 1);
}

inline void print(__int128 x)
{
    while ( x >= 10 ) x /= 10;
    int t = x;
    printf("%lld\n", t);
}

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
    freopen("Philosopher.in", "r", stdin);
    freopen("Philosopher.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    Set.insert(0); Set.insert(n + 1);
    REP(i, 1, 4 * n) A.sum[i] = 1;
    REP(i, 1, n) 
    {
        read(a[i]);
        Modify(Root[i], 1, n, a[i]);
        h[i] = 1; Set.insert(i);
        A.Modify(1, 1, n, i, a[i]);
    }
    REP(o, 1, m)
    {
        // cerr << o << endl;
        int op, l, r, flag; read(op); read(l); read(r); 
        if ( op == 1 ) 
        {
            read(flag);
            auto pre = -- Set.upper_bound(l);
            HaSplit(*pre, l - *pre); 
            auto suf = -- Set.upper_bound(r);
            HaSplit(*suf, r - *suf + 1);
            HaMerge(l, r); h[l] = flag;
        }
        else
        {
            auto pre = -- Set.upper_bound(l);
            HaSplit(*pre, l - *pre); 
            auto suf = -- Set.upper_bound(r);
            HaSplit(*suf, r - *suf + 1);
            __int128 ret = A.Query(1, 1, n, l, r);
            print(ret);
        }
    }
    return 0;
}
