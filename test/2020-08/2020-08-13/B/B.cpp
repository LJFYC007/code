/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年08月13日 星期四 08时22分36秒
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

int n, ans, fac[maxn], inv[maxn], r[maxn];
char s[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

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
                int x = f[i + j], y = f[i + Mid + j] * sum % Mod;
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

inline vector<int> operator * (vector<int> f, vector<int> g)
{
    int n = f.size(), m = g.size(), len = 1;
    while ( len < n + m ) len <<= 1; f.resize(len); g.resize(len);
    f = NTT(f, 1); g = NTT(g, 1); REP(i, 0, len - 1) f[i] = f[i] * g[i] % Mod; f = NTT(f, -1);
    f.resize(n + m - 1); return f;
}

vector<int> f, g;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    f.resize(n + 1); g.resize(n + 1);

    REP(i, 1, n) 
    {
        if ( s[i] == '0' ) f[i] = inv[i - 1];
        if ( i < n ) g[i] = power(2, i - 1) * fac[n - i - 1] % Mod;
    }
    f = f * g;
    REP(i, 1, n) if ( s[i] == '0' ) ans = (ans + f[i] * inv[n - i]) % Mod;

    f.clear(); f.resize(n + 1);
    REP(i, 1, n) if ( s[i] == '1' ) f[i] = inv[i - 1];
    f = f * g;
    REP(i, 1, n) if ( s[i] == '1' ) ans = (ans + f[i] * inv[n - i]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
