/***************************************************************
	File name: reverse.cpp
	Author: ljfcnyali
	Create time: 2020年01月14日 星期二 11时05分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3e5 + 10;
const int Mod = 998244353;

int n, m, T, a[maxn], b[maxn], ret, Suf1[maxn], Pre1[maxn], Suf2[maxn], Pre2[maxn], tot1, tot2;
int p1[maxn], p2[maxn], inv1[maxn], inv2[maxn], suf[maxn], pre[maxn], len;
bool vis[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void SWAP(int r, int op)
{
    if ( op == 1 ) REP(i, 1, r / 2) swap(a[i], a[r - i + 1]);
    else REP(i, 1, r / 2) swap(b[i], b[r - i + 1]);
}

inline bool Check(int last)
{
    REP(i, 1, last)
    {
        if ( a[i] < b[i] ) return false;
        if ( a[i] > b[i] ) return true;
    }
    return true;
}

inline int Query()
{
    int x = 1; ret = 0;
    REP(i, 1, n)
    {
        ret = (ret + x * a[i]) % Mod;
        x = x * 37 % Mod;
    }
    return ret;
}

inline int Get1(int L, int R)
{
    int x = Suf1[R] - Suf1[L - 1];
    return x * p1[R - 1] % Mod;
}

inline int Get2(int L, int R)
{
    int x = Suf2[R] - Suf2[L - 1];
    return x * p2[R - 1] % Mod;
}

inline bool CHECK(int R)
{
    int x, y;
    if ( R <= tot2 ) x = Get1(tot2 - R + 1, tot2);
    else x = (Get1(1, tot2) + Pre1[R - tot2] * p1[tot2]) % Mod;
    if ( R <= tot2 + len ) y = Get1(tot2 + len - R + 1, tot2 + len);
    else y = (Get1(1, tot2 + len) + Pre1[R - tot2 - len] * p1[tot2 + len]) % Mod;
    x = (x + Mod) % Mod; y = (y + Mod) % Mod;
	if ( x != y ) return false;
    if ( R <= tot2 ) x = Get2(tot2 - R + 1, tot2);
    else x = (Get2(1, tot2) + Pre2[R - tot2] * p2[tot2]) % Mod;
    if ( R <= tot2 + len ) y = Get2(tot2 + len - R + 1, tot2 + len);
    else y = (Get2(1, tot2 + len) + Pre2[R - tot2 - len] * p2[tot2 + len]) % Mod;
    x = (x + Mod) % Mod; y = (y + Mod) % Mod;
    return x == y;
}

inline bool Solve(int R)
{
    int L = 1, pos = 0;
    while ( L <= R )
    {
        int Mid = L + R >> 1;
        if ( CHECK(Mid) ) { pos = Mid; L = Mid + 1; }
        else R = Mid - 1;
    }
    ++ pos; int x, y;
    if ( pos <= tot2 ) x = suf[tot2 - pos + 1];
    else x = pre[pos - tot2];
    if ( pos <= tot2 + len ) y = suf[tot2 + len - pos + 1];
    else y = pre[pos - tot2 - len];
    return x <= y;
}

signed main()
{
    freopen("reverse.in", "r", stdin);
    freopen("reverse.out", "w", stdout);
    scanf("%lld", &T);
    p1[0] = inv1[0] = 1;
    REP(i, 1, maxn - 10) { p1[i] = p1[i - 1] * 37 % Mod; inv1[i] = inv1[i - 1] * power(37, Mod - 2) % Mod; }
    p2[0] = inv2[0] = 1;
    REP(i, 1, maxn - 10) { p2[i] = p2[i - 1] * 233 % Mod; inv2[i] = inv2[i - 1] * power(233, Mod - 2) % Mod; }
    while ( T -- )
    {
        mem(vis); tot1 = tot2 = 0;
        scanf("%lld%lld", &n, &m);
        REP(i, 1, n) scanf("%lld", &a[i]);
        REP(i, 1, m) { int x; scanf("%lld", &x); vis[x] = true; }
        int last = 1;
        while ( last <= n && vis[last] ) ++ last;
        if ( last > n ) { printf("%lld\n", Query()); continue ; }
        REP(i, 1, last) b[i] = a[i]; SWAP(last, 2);
        if ( Check(last) ) REP(i, 1, last) a[i] = b[i];
        REP(i, 1, last)
        {
            Pre1[i] = (Pre1[i - 1] + p1[i - 1] * a[i]) % Mod;
            Pre2[i] = (Pre2[i - 1] + p2[i - 1] * a[i]) % Mod;
            pre[i] = a[i];
        }
        tot1 = last;
        REP(i, last + 1, n)
        {
            if ( vis[i] ) continue ;
            len = i - last;
            REP(j, 1, len)
            {
                Pre1[tot1 + j] = (Pre1[tot1 + j - 1] + p1[tot1 + j - 1] * a[last + j]) % Mod;
                Pre2[tot1 + j] = (Pre2[tot1 + j - 1] + p2[tot1 + j - 1] * a[last + j]) % Mod;
                pre[tot1 + j] = a[last + j];
                Suf1[tot2 + j] = (Suf1[tot2 + j - 1] + inv1[tot2 + j - 1] * a[last + j]) % Mod;
                Suf2[tot2 + j] = (Suf2[tot2 + j - 1] + inv2[tot2 + j - 1] * a[last + j]) % Mod;
                suf[tot2 + j] = a[last + j];
            }
            if ( Solve(i) ) tot1 += len;
            else tot2 += len;
            last = i;
        }
        REP(i, last + 1, n)
        {
            ++ tot1;
            Pre1[tot1] = (Pre1[tot1 - 1] + p1[tot1 - 1] * a[i]) % Mod;
        }
        printf("%lld\n", (Get1(1, tot2) + Pre1[tot1] * p1[tot2]) % Mod);
    }
    return 0;
}
