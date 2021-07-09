/***************************************************************
	File name: LibreOJ_6503.cpp
	Author: ljfcnyali
	Create time: 2020年11月24日 星期二 15时50分36秒
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

int n, m, k, a[maxn], fac[maxn], inv[maxn], r[maxn];

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
                int x = f[i + j], y = f[i + Mid + j] * sum % Mod;
                f[i + j] = (x + y) % Mod; f[i + Mid + j] = (x - y) % Mod;
            }
        }
    }
    if ( inv == -1 ) { inv = power(n, Mod - 2); REP(i, 0, n - 1) f[i] = f[i] * inv % Mod; }
    return f;
}

inline vector<int> operator *(vector<int> a, vector<int> b)
{
    int n = a.size(), m = b.size(), len = 1;
    while ( len < n + m ) len <<= 1;
    a.resize(len); b.resize(len); a = NTT(a, 1); b = NTT(b, 1);
    REP(i, 0, len - 1) a[i] = a[i] * b[i] % Mod;
    a = NTT(a, -1); a.resize(n + m - 1); return a;
}

inline vector<int> Solve(vector< vector<int> > a)
{
    if ( a.size() == 1 ) return a.back();
    int Mid = a.size() / 2;
    vector<int> f, g; vector< vector<int> > b;
    while ( a.size() > Mid ) { b.push_back(a.back()); a.pop_back(); }
    f = Solve(a); g = Solve(b); return f * g;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld%lld", &m, &n, &k);
    REP(i, 1, m) scanf("%lld", &a[i]); 

    vector< vector<int> > ttt; 
    REP(i, 1, m)
    {
        vector<int> f; 
        REP(j, 0, a[i] - 1) f.push_back(C(a[i], j) * fac[a[i] - 1] % Mod * inv[a[i] - j - 1] % Mod);
        ttt.push_back(f);
    }
    vector<int> f = Solve(ttt); f.resize(n);

    int ans = 0;
    REP(i, k, n - 1) ans = (ans + sgn(i - k) * f[i] * fac[n - i] % Mod * C(i, k)) % Mod;
    REP(i, 1, m) ans = ans * inv[a[i]] % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
