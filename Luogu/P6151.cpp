/***************************************************************
	File name: always.cpp
	Author: ljfcnyali
	Create time: 2020年07月17日 星期五 21时12分44秒
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

int n, m, c[maxn], fac[maxn], inv[maxn], r[maxn];
bool flag = true;

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
    if ( inv == -1 ) { inv = power(n, Mod - 2); REP(i, 0, n - 1) f[i] = f[i] * inv % Mod; }
    return f;
}

vector<int> operator + (vector<int> f, vector<int> g)
{
    int n = f.size(), m = g.size();
    f.resize(max(n, m)); g.resize(max(n, m));
    REP(i, 0, max(n, m) - 1) f[i] = (f[i] + g[i]) % Mod;
    return f;
}
vector<int> operator - (vector<int> f, vector<int> g)
{
    int n = f.size(), m = g.size();
    f.resize(max(n, m)); g.resize(max(n, m));
    REP(i, 0, max(n, m) - 1) f[i] = (f[i] - g[i]) % Mod;
    return f;
}
vector<int> operator * (vector<int> f, vector<int> g) 
{
    int n = f.size(), m = g.size(), len = 1;
    while ( len <= n + m ) len <<= 1;
    f.resize(len); g.resize(len); f = NTT(f, 1); g = NTT(g, 1);
    REP(i, 0, len - 1) f[i] = f[i] * g[i] % Mod;
    f = NTT(f, -1); f.resize(n + m - 1); return f;
}

inline int sgn(int x) { return x & 1 ? -1 : 1; }

inline vector<int> Solve1(int n)
{
    vector<int> f, g; f.resize(n + 1); g.resize(n + 1);
    REP(i, 0, n) { f[i] = power(i, n) * inv[i] % Mod; g[i] = sgn(i) * inv[i]; }
    f = f * g;
    REP(i, 0, n) f[i] = (f[i] * fac[i] % Mod) * inv[n] % Mod;
    return f;
}

inline vector<int> Solve2(int n)
{
    vector<int> f, g; f.resize(n + 1); g.resize(n + 1);
    REP(i, 1, n) 
    {
        int x = C(n + i - 1, i + i - 1);
        f[n - i] = fac[i - 1] * x % Mod;
        if ( flag ) f[n - i] = f[n - i] * power(i, Mod - 2) % Mod;
        g[i] = sgn(i) * inv[i];
    }
    g[0] = 1; f = f * g; f.resize(n + 1);
    REP(i, 0, n) if ( i < n - i ) swap(f[i], f[n - i]);
    REP(i, 1, n) f[i] = f[i] * inv[i - 1] % Mod;
    if ( !flag ) REP(i, 1, n) f[i] = f[i] * inv[i] % Mod;
    f[0] = 0; return f;
}

vector<int> f[maxn], F[maxn], g, t, h;

inline vector<int> Solve(int l, int r)
{
    if ( l == r ) return F[l];
    int Mid = l + r >> 1; 
    vector<int> a = Solve(l, Mid), b = Solve(Mid + 1, r);
    return a * b;
}

signed main()
{
    n = maxn - 10;
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld", &c[i]); m += c[i]; }
    
    REP(i, 1, n)
    {
       //f[i] = Solve1(c[i]);
        F[i] = Solve2(c[i]);
        flag = false;
    }

    t = Solve(2, n);
    int ans = 0;
    REP(i, 1, c[1]) F[1][i - 1] = F[1][i]; F[1].resize(c[1]);
    h = F[1]; REP(i, 0, c[1] - 1) h[i] = h[i] * inv[i] % Mod;
    g = h * t; 
    REP(i, 1, c[1] - 1) F[1][i - 1] = F[1][i]; F[1].resize(c[1] - 1);
    h = F[1]; REP(i, 0, c[1] - 2) h[i] = h[i] * inv[i] % Mod;
    g = g - h * t;
    REP(i, 1, m - 1) ans = (ans + fac[i] * g[i]) % Mod;
    ans = (ans + Mod) % Mod;

    printf("%lld\n", ans * m % Mod);
    return 0;
}

