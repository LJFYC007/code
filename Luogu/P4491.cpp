/***************************************************************
	File name: P4491.cpp
	Author: ljfcnyali
	Create time: 2020年05月29日 星期五 14时50分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e7 + 10;
const int Mod = 1004535809;

int r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(int *a, int n, int inv)
{ 
    vector<unsigned long long> f(n);
    copy(a, a + n, f.begin());
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2);
        for ( int i = 0; i < n; i += (Mid << 1) ) 
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod ) 
            {
                int x = f[i + Mid + j] * sum % Mod;
                f[i + Mid + j]= f[i + j] - x + Mod;
                f[i + j] += x;
            }
        }
    }
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2);
        REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
    }
    REP(i, 0, n - 1) a[i] = f[i] % Mod;
}

int n, m, s, lim, f[maxn], g[maxn];
int fac[maxn], inv[maxn];

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline void INIT()
{
    int x = 1;
    REP(i, 0, lim)
    {
        f[i] = C(m, i) * power(m - i, n - s * i) % Mod;
        f[i] = f[i] * fac[n] % Mod;
        f[i] = f[i] * (x * inv[n - s * i] % Mod) % Mod;
        x = x * inv[s] % Mod;
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = 10000000;
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld%lld", &n, &m, &s);
    lim = min(m, n / s); INIT();
    REP(i, 0, lim) 
    {
        f[i] = ((f[i] * fac[i] % Mod) + Mod) % Mod;
        g[lim - i] = ((power(-1, i) * inv[i] % Mod) + Mod) % Mod;
    }
    int len = 1; while ( len <= (lim << 1) ) len <<= 1;
    NTT(f, len, 1); NTT(g, len, 1);
    REP(i, 0, len - 1) f[i] = f[i] * g[i] % Mod;
    NTT(f, len, -1);
    REP(i, 0, lim) f[i] = f[lim + i] * inv[i] % Mod;
    int ret = 0;
    REP(i, 0, lim) { int x; scanf("%lld", &x); ret = (ret + x * f[i]) % Mod; }
    printf("%lld\n", (ret + Mod) % Mod);
    return 0;
}
