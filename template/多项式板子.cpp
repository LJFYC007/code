/***************************************************************
	File name: 多项式板子.cpp
	Author: ljfcnyali
	Create time: 2020年06月17日 星期三 08时14分22秒
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
const int inv2 = (Mod + 1) / 2;

int r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

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

inline vector<int> Mul(vector<int> f, vector<int> g)
{
    int n = f.size(), m = g.size(), len = 1;
    while ( len <= (n + m) ) len <<= 1;
    f.resize(len); g.resize(len);
    f = NTT(f, 1); g = NTT(g, 1);
    REP(i, 0, len - 1) f[i] = f[i] * g[i] % Mod;
    f = NTT(f, -1); return f;
}

inline vector<int> Dx(vector<int> f)
{
    int n = f.size();
    REP(i, 0, n - 2) f[i] = f[i + 1] * (i + 1) % Mod;
    f.resize(n - 1); return f;
}

inline vector<int> Int(vector<int> f)
{
    int n = f.size(); f.resize(n + 1); 
    for ( int i = n; i >= 1; -- i ) f[i] = f[i - 1] * power(i, Mod - 2) % Mod;
    f[0] = 0; return f;
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
    h = Mul(f, g); h.resize(n);
    REP(i, 0, n - 1) h[i] = -h[i]; h[0] += 2;
    h = Mul(h, g); h.resize(n);
    return h;
}

inline vector<int> Sqrt(vector<int> f)
{
    vector<int> g, h;
    if ( f.size() == 1 ) { g.resize(1); g[0] = 1; return g; }
    int n = f.size(); g = f; g.resize((n + 1) / 2);
    g = Sqrt(g); g.resize(n); h = Inv(g); g = Mul(g, g); g.resize(n);
    REP(i, 0, n - 1) { f[i] = (g[i] + f[i]) % Mod; h[i] = h[i] * inv2 % Mod; }
    f = Mul(f, h); f.resize(n); return f;
}

inline vector<int> ln(vector<int> f)
{
    int n = f.size();
    vector<int> g = Dx(f), h = Inv(f);
    f = Mul(g, h); f.resize(n - 1); f = Int(f);
    return f;
}

inline vector<int> exp(vector<int> f)
{
    vector<int> g, h;
    if ( f.size() == 1 ) { g.resize(1); g[0] = 1; return g; }
    int n = f.size(); g = f; g.resize((n + 1) / 2); g = exp(g); g.resize(n); h = ln(g);
    REP(i, 0, n - 1) f[i] = (f[i] - h[i]) % Mod; ++ f[0];
    f = Mul(f, g); f.resize(n); return f;
}

int n; vector<int> f;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n); f.resize(n);
    REP(i, 0, n - 1) scanf("%lld", &f[i]);
    f = exp(f);
    REP(i, 0, n - 1) printf("%lld ", (f[i] + Mod) % Mod); puts("");
    return 0;
}
