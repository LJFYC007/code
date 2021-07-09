/***************************************************************
	File name: backronym.cpp
	Author: ljfcnyali
	Create time: 2019年10月12日 星期六 09时35分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 20010;
const int seed = 233;
const int INF = 100000000000000;
const int Mod = 998244353;

int p[maxn], n, m, Hash[maxn], inv[maxn];
struct node
{
    int Min, Minn, lazy;
} Tree[maxn << 2];
struct STRING
{
    char s[maxn];
    int val, len, Hash[maxn];
} a[60];
char s[maxn];

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; }
    return r;
}

inline bool Check(int x, int y, int pos)
{
    int l = x, r = x + pos - 1;
    if ( r > m ) return false;
    int sum = Hash[r] - Hash[l - 1];
    if ( m >= r + 1 ) sum = sum * inv[m - r - 1] % Mod;
    else sum = sum * seed % Mod;
    sum = (sum + Mod) % Mod;
    int sum2 = a[y].Hash[pos];
    if ( a[y].len >= pos + 1 ) sum2 = sum2 * inv[a[y].len - pos - 1] % Mod;
    else sum2 = sum2 * seed % Mod;
    sum2 = (sum2 + Mod) % Mod;
    return sum == sum2;
}

inline void PushUp(int root)
{
    if ( Tree[lson].Min < Tree[rson].Min ) 
        Tree[root].Min = Tree[lson].Min, Tree[root].Minn = min(Tree[lson].Minn, Tree[rson].Min);
    else if ( Tree[lson].Min > Tree[rson].Min ) 
        Tree[root].Min = Tree[rson].Min, Tree[root].Minn = min(Tree[rson].Minn, Tree[lson].Min);
    else
        Tree[root].Min = Tree[lson].Min, Tree[root].Minn = min(Tree[lson].Minn, Tree[rson].Minn);
}

inline void PushTag(int root, int val)
{
    if ( !root || Tree[root].Min >= val ) return ;
    Tree[root].Min = Tree[root].lazy = val;
}

inline void PushDown(int root)
{
    if ( Tree[root].lazy == -1 ) return ;
    PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = -1;
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    // cerr << root << " " << l << " " << r << " " << L << " " << R << " " << val << endl;
    if ( Tree[root].Min >= val ) return ;
    if ( L <= l && r <= R && Tree[root].Minn >= val ) { PushTag(root, val); return ; }
    PushDown(root);
    int Mid = l + r >> 1;
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int pos)
{
    if ( l == r ) return Tree[root].Min;
    PushDown(root);
    int Mid = l + r >> 1;
    if ( pos <= Mid ) return Query(lson, l, Mid, pos);
    return Query(rson, Mid + 1, r, pos);
}

signed main()
{
    freopen("backronym.in", "r", stdin);
    freopen("backronym.out", "w", stdout);
    p[0] = inv[0] = 1; REP(i, 1, maxn - 10) p[i] = p[i - 1] * seed % Mod;
    REP(i, 1, maxn - 10) inv[i] = power(p[i], Mod - 2);
    REP(i, 1, (maxn - 1) * 4) Tree[i].Min = -INF, Tree[i].Minn = INF, Tree[i].lazy = -1;
    scanf("%s", s + 1); m = str(s + 1);
    REP(i, 1, m) Hash[i] = (Hash[i - 1] + p[m - i] * (s[i] - 'a')) % Mod;
    scanf("%lld", &n);
    REP(i, 1, n) 
    {
        scanf("%s", a[i].s + 1); scanf("%lld", &a[i].val);
        a[i].len = str(a[i].s + 1); 
        REP(j, 1, a[i].len) a[i].Hash[j] = (a[i].Hash[j - 1] + p[a[i].len - j] * (a[i].s[j] - 'a')) % Mod;
    }
    REP(i, 1, m)
    {
        int val = i == 1 ? 0 : Query(1, 1, m, i - 1);
        REP(j, 1, n)
        {
            int L = 1, R = a[j].len, x = 0;
            while ( L <= R ) 
            {
                int Mid = L + R >> 1;
                if ( Check(i, j, Mid) ) { L = Mid + 1; x = Mid; }
                else R = Mid - 1;
            }
            if ( !x ) continue ;
            Modify(1, 1, m, i, i + x - 1, val + a[j].val);
        }
    }
    int ans = Query(1, 1, m, m);
    printf("%lld\n", ans <= -INF + 10000000000 ? -1 : ans);
    return 0;
}
