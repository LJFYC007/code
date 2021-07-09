/***************************************************************
	File name: P4091.cpp
	Author: ljfcnyali
	Create time: 2020年06月04日 星期四 14时15分38秒
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

int n, m, a[maxn], b[maxn], fac[maxn], inv[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    m = 1; while ( m <= (n << 1) ) m <<= 1;
    fac[0] = inv[0] = 1; REP(i, 1, m) fac[i] = fac[i - 1] * i % Mod;
    inv[m] = power(fac[m], Mod - 2); for ( int i = m - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 0, n) 
    {
        a[i] = inv[i] * power(-1, i);
        int sum = (power(i, n + 1) - 1) * power(i - 1, Mod - 2) % Mod;
        if ( i == 1 ) sum = n + 1;
        b[i] = inv[i] * sum % Mod;
    }
    NTT(a, m, 1); NTT(b, m, 1);
    REP(i, 0, m - 1) a[i] = a[i] * b[i] % Mod;
    NTT(a, m, -1);
    int ans = 0;
    REP(i, 0, n) ans = (ans + (power(2, i) * fac[i] % Mod) * a[i]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
