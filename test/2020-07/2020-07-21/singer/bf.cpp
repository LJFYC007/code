/***************************************************************
	File name: singer.cpp
	Author: ljfcnyali
	Create time: 2020年07月21日 星期二 20时53分04秒
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

int n, m, k, fac[maxn], inv[maxn], r[maxn], ans;
vector<int> f, g, h, F;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline int sgn(int x) { return x & 1 ? -1 : 1; }

inline vector<int> NTT(vector<int> f, int inv)
{
    int n = f.size();
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1 ) ? (n >> 1) : 0);
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

vector<int> operator + (vector<int> f, vector<int> g)
{
    int n = f.size(), m = g.size(), len = max(n, m);
    f.resize(len); g.resize(len); 
    REP(i, 0, len - 1) f[i] = (f[i] + g[i]) % Mod;
    return f;
}

vector<int> operator - (vector<int> f, vector<int> g)
{
    int n = f.size(), m = g.size(), len = max(n, m);
    f.resize(len); g.resize(len); 
    REP(i, 0, len - 1) f[i] = (f[i] - g[i]) % Mod;
    return f;
}

vector<int> operator * (vector<int> f, int x)
{
    int n = f.size(); REP(i, 0, n - 1) f[i] = f[i] * x % Mod; return f;
}

vector<int> operator * (vector<int> f, vector<int> g) 
{
    int n = f.size(), m = g.size(), len = 1;
    while ( len < n + m ) len <<= 1;
    f.resize(len); g.resize(len); 
    f = NTT(f, 1); g = NTT(g, 1); REP(i, 0, len - 1) f[i] = f[i] * g[i] % Mod; 
    f = NTT(f, -1); f.resize(n + m - 1); return f;
}

inline vector<int> Inv(vector<int> f)
{
    vector<int> g, h;
    if ( f.size() == 1 ) 
    {
        g.resize(1); g[0] = power(f[0], Mod - 2);
        return g;
    }
    int n = f.size(); g = f; g.resize((n + 1) / 2); g = Inv(g);
    h = f * g; h.resize(n); REP(i, 0, n - 1) h[i] = -h[i]; h[0] += 2;
    h = h * g; h.resize(n); return h;
}

inline vector<int> power(vector<int> f, int n, int len)
{
    if ( !n ) { vector<int> g; g.resize(len); g[0] = 1; return g; }
    vector<int> g = f; -- n;
    while ( n ) 
    { 
        if ( n & 1 ) { g = g * f; g.resize(len); }
        f = f * f; f.resize(len); n >>= 1;
    }
    return g;
}

signed main()
{
    freopen("singer.in", "r", stdin);
    freopen("singer.out", "w", stdout);
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld%lld", &n, &m, &k);
    F.resize(m + 1); REP(i, 1, m) F[i] = C(m, i);
    f.resize(n + 2); REP(i, 0, m - 1) f[i] = C(m, i + 1);
    h = f; -- h[0]; h = Inv(h);

    REP(i, 0, n + 1)
        g = g + (power(F, n - i + 1, n + 2) * sgn(i - k) * C(i, k));
    REP(i, 0, n + 1) printf("%lld ", (g[i] + Mod) % Mod); puts("");
    g = g * h;
    ans = (g[n + 1] + Mod) % Mod;

    g.clear(); g.resize(n + 2); REP(i, 0, n + 1) g[n - i + 1] = sgn(i - k) * C(i, k);
    g = g * f * h;
    ans = (ans - g[n + 1]) % Mod;

    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
