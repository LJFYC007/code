/***************************************************************
	File name: warface.cpp
	Author: ljfcnyali
	Create time: 2020年10月04日 星期日 10时20分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<LL, LL>
typedef long long LL;

const int maxn = (1 << 15) + 10;
const int N = (1 << 15) - 1;
const int Mod = 1e9 + 7;
const int MOD = 1e9 + 6;
const int inv2 = (Mod + 1) / 2;

LL T, n, m, s, t, p, P, invp, ans, ret;
int f1[maxn], f2[maxn];

inline LL power(LL a, LL b) { LL r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Get(int n) { return (LL)f1[n & N] * f2[n >> 15] % Mod; }

inline LL f(int n)
{
    ret += n; LL x = (invp - Get(n)) * P % Mod;
    return -x * inv2 % Mod;
}

signed main()
{
    freopen("warfare.in", "r", stdin);
    freopen("warfare.out", "w", stdout);
    scanf("%lld%lld%lld%lld", &T, &n, &s, &t); p = s * power(t, Mod - 2) % Mod; 
    invp = power(p, Mod - 2); P = power(1 - invp, Mod - 2);

    f1[0] = 1; REP(i, 1, maxn - 10) f1[i] = (LL)f1[i - 1] * invp % Mod;
    LL x = f1[maxn - 10]; f2[0] = 1; REP(i, 1, maxn - 10) f2[i] = (LL)f2[i - 1] * x % Mod;

    if ( T == 0 ) 
        REP(i, 1, n) { LL x; scanf("%lld", &x); ans = (ans + f(x % (Mod - 1))) % Mod; }
    else 
    {
        LL m, q, lst = 0, l, r; unsigned long long x, y, z, b1, b2, bnow;
        scanf("%lld%llu%llu%llu%llu%llu", &m, &x, &y, &z, &b1, &b2);
        REP(i, 1, n)
        {
            if ( i > lst ) 
            { 
                scanf("%lld%lld%lld", &q, &l, &r); lst = q; 
            }
            if ( i == 1 ) bnow = b1;
            else if ( i == 2 ) bnow = b2;
            else { bnow = x * b2 + y * b1 + z; b1 = b2; b2 = bnow; }

            LL now = bnow % (r - l + 1) + l;
            ans = (ans + f(now % (Mod - 1))) % Mod;
        }
    }

    ret = ret % MOD;
    ans = (ans - f(ret)) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
