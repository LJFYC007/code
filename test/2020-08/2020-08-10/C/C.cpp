/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年08月10日 星期一 10时04分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 1e6 + 10;
const int seed = 233;
const int Mod = 998244353;

int n, m, p[maxn], a[maxn], c[maxn], inv[maxn];
struct node { int len, sum, num; } Tree[maxn << 2];
char s[maxn];

inline int power(LL a, int b) { LL r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) c[i] = (c[i] + val) % Mod; }

inline int get(int pos) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret = (ret + c[i]) % Mod; return ret; }

inline int Find(int l, int r)
{
    int ret = (get(r) - get(l - 1)) % Mod;
    ret = (LL)ret * inv[l - 1] % Mod;
    return (ret + Mod) % Mod;
}

inline void PushUp(int root) { Tree[root].sum = Tree[lson].sum + Tree[rson].sum; }

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].sum = s[l] - '0'; return ; }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline void Modify(int root, int l, int r, int pos)
{
    if ( l == r ) { Tree[root].sum = a[pos]; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos);
    else Modify(rson, Mid + 1, r, pos);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 0;
    if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
    return ret;
}

signed main()
{
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    scanf("%d%d", &n, &m);
    p[0] = inv[0] = 1; REP(i, 1, n) p[i] = (LL)p[i - 1] * seed % Mod;
    int x = power(seed, Mod - 2); REP(i, 1, n) inv[i] = (LL)inv[i - 1] * x % Mod;
    scanf("%s", s + 1); Build(1, 1, n);
    REP(i, 1, n) { a[i] = s[i] - '0'; add(i, a[i] * p[i]); }
    while ( m -- ) 
    {
        int op, l, r, x; scanf("%d", &op);
        if ( op == 1 ) 
        { 
            scanf("%d%d%d", &l, &r, &x);
            int pos = 0, lst = 0;
            while ( 1 ) 
            {
                int L = pos + 1, R = x, pos = 0;
                while ( L <= R ) 
                {
                    int Mid = L + R >> 1;
                    if ( Find(l + lst, l + Mid - 1) != Find(r + lst, r + Mid - 1) ) R = Mid - 1;
                    else { L = Mid + 1; pos = Mid; }
                }
                if ( pos == x ) break ; 
                lst = pos; 
                if ( a[l + pos] ) { a[l + pos] = 0; Modify(1, 1, n, l + pos); add(l + pos, -p[l + pos]); }
                else { a[r + pos] = 0; Modify(1, 1, n, r + pos); add(r + pos, -p[r + pos]); }
            }
        }
        if ( op == 2 ) { scanf("%d", &x); a[x] ^= 1; Modify(1, 1, n, x); add(x, a[x] ? p[x] : -p[x]); }
        if ( op == 3 ) 
        {
            scanf("%d%d%d", &l, &r, &x);
            if ( x == 1 ) printf("%d\n", Query(1, 1, n, l, r));
            else printf("%d\n", r - l + 1 - Query(1, 1, n, l, r));
        }
    }
    return 0;
}
