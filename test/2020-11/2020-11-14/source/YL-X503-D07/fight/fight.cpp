/***************************************************************
	File name: fight.cpp
	Author: ljfcnyali
	Create time: 2020年11月14日 星期六 10时41分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int ans, n, k, f[maxn], g[maxn], fac[maxn], inv[maxn], r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline int sgn(int x) { return x & 1 ? -1 : 1; }

inline vector<int> NTT(vector<int> f, int inv)
{
    int n = f.size();
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
    return f;
}

inline vector<int> operator *(vector<int> a, vector<int> b)
{
    int n = a.size(), m = b.size(), len = 1;
    while ( len < n + m ) len <<= 1; a.resize(len); b.resize(len);
    a = NTT(a, 1); b = NTT(b, 1); REP(i, 0, len - 1) a[i] = a[i] * b[i] % Mod; a = NTT(a, -1);
    a.resize(n + m - 1); return a;
}

signed main()
{
    freopen("fight.in", "r", stdin);
    freopen("fight.out", "w", stdout);
    scanf("%lld%lld", &n, &k); 
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    vector<int> a, b; a.resize(n + 1); b.resize(n + 1);
    REP(i, 0, n) a[i] = power(2, i) * inv[i] % Mod * inv[i - 1] % Mod;
    REP(i, 0, n) b[i] = sgn(i) * inv[i] * fac[n - i - 1] % Mod;
    a = a * b;
    REP(i, 0, n) g[i] = a[i] * fac[i] % Mod * fac[i] % Mod * fac[i] % Mod;
    
    a.clear(); b.clear(); a.resize(n + 1); b.resize(n + 1);
    REP(i, 0, n) a[i] = inv[i] * g[i] % Mod;
    REP(i, 0, n) b[i] = sgn(i) * inv[i] % Mod;
    a = a * b;
    REP(i, 1, n) if ( i <= k + 1 ) ans = (ans + a[i] * inv[n - i]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
