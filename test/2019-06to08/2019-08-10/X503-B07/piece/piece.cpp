/***************************************************************
	File name: piece.cpp
	Author: ljfcnyali
	Create time: 2019年08月10日 星期六 08时20分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r
typedef long long LL;

const int maxn = 3000010;

LL a[maxn], n, m, k, p[maxn], h[maxn], cnt, ans, b[maxn], sum[maxn];

struct node
{
    LL l, r, val;
} Tree[maxn];

inline void INIT(int root) { ls(root) = rs(root) = Tree[root].val = 0; }

inline void Insert(LL &root, LL l, LL r, LL val, LL size)
{
    if ( !root ) { root = ++ cnt; INIT(root); }
    // cerr << root << " " << l << " " << r << " " << val << endl;
    Tree[root].val += size;
    if ( l == r ) return ;
    LL Mid = l + r >> 1;
    if ( val <= Mid ) Insert(ls(root), l, Mid, val, size);
    else Insert(rs(root), Mid + 1, r, val, size);
}

inline LL Query(LL root, LL l, LL r, LL val)
{
    if ( !root || !Tree[root].val ) return 0;
    if ( l == r ) return Tree[root].val;
    LL Mid = l + r >> 1;
    if ( val <= Mid ) return Query(ls(root), l, Mid, val);
    else return Query(rs(root), Mid + 1, r, val);
}

inline void read(LL &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
    freopen("piece.in", "r", stdin);
    freopen("piece.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    m = n;
    REP(i, 1, n) read(a[i]);
    sort(a + 1, a + n + 1);
    LL now = 0;
    REP(i, 1, n) { if ( a[i] != a[i - 1] ) ++ now; else ++ sum[now]; b[now] = a[i]; }
    n = now; REP(i, 1, n) a[i] = b[i];
    h[1] = 10; REP(i, 2, 10) h[i] = h[i - 1] * 10; 
    now = 1;
    REP(i, 1, n) 
    {
        ++ sum[i];
        if ( a[i] >= h[now] ) p[now] = i - 1;
        while ( a[i] >= h[now] ) ++ now;
    }
    p[now] = n;
    LL root;
    REP(i, 1, now)
    {
        root = cnt = 0;
        LL L = p[i - 1] + 1, R = p[i];
        h[i] %= k;
        if ( L > R ) continue ; 
        REP(j, 1, n) Insert(root, 0, k - 1, (a[j] * h[i]) % k, sum[j]); 
        REP(j, L, R) 
        {
            if ( (a[j] * (h[i] + 1)) % k == 0 ) 
                ans -= sum[j];
            LL x = a[j] % k;
            if ( x == 0 ) ans += sum[j] * Query(1, 0, k - 1, x);
            else ans += sum[j] * Query(1, 0, k - 1, k - x);
        }
    }   
    printf("%lld\n", m * (m - 1) - ans);
    return 0;
}

