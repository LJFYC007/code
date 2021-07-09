/***************************************************************
	File name: P5401.cpp
	Author: ljfcnyali
	Create time: 2020年06月10日 星期三 20时35分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(int *f, int n, int inv)
{
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    REP(i, 0, n - 1) if ( r[i] > i ) swap(f[i], f[r[i]]);
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2);
        for ( int i = 0; i < n; i += (Mid << 1) )
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod ) 
            {
                int x = f[i + j], y = sum * f[i + Mid + j] % Mod;
                f[i + j] = (x + y) % Mod; f[i + Mid + j] = (x - y) % Mod;
            }
        }
    }
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2);
        REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
    }
}

inline void Mul(int *f, int *g, int n)
{
    int len = 1; while ( len <= (n << 1) ) len <<= 1;
    fill(f + n, f + len, 0); fill(g + n, g + len, 0);
    NTT(f, len, 1); NTT(g, len, 1);
    REP(i, 0, len - 1) f[i] = f[i] * g[i] % Mod;
    NTT(f, len, -1);
}

int n, m, D, fac[maxn], inv[maxn], f[maxn], g[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10;
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    assert(inv[2] == (Mod + 1) / 2);
    scanf("%lld%lld%lld", &D, &n, &m);
    if ( n - 2 * m < 0 ) { puts("0"); return 0; }
    if ( n - 2 * m >= D ) { printf("%lld\n", power(D, n)); return 0; }
    int N = n - 2 * m;
    REP(i, 0, D) 
    {
        f[i] = inv[i] * (i & 1 ? -1 : 1) * power(D - 2 * i, n) % Mod;
        g[i] = inv[i];
    }
    Mul(f, g, D + 1);
    REP(i, 0, D) f[i] = (f[i] * fac[D] % Mod) * (inv[D - i] * power(inv[2], i) % Mod) % Mod;
    REP(i, 0, D)
    {
        f[i] = f[i] * fac[i] % Mod;
        g[D - i] = (i & 1 ? -1 : 1) * inv[i] % Mod;
    }
    Mul(f, g, D + 1);
    int ans = 0;
    REP(i, 0, N) ans = (ans + f[D + i] * inv[i]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
