/***************************************************************
	File name: rubik.cpp
	Author: ljfcnyali
	Create time: 2021年01月11日 星期一 16时05分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 6e6 + 10;
const int Mod = 1e9 + 7;

int N, n, P, a[6][3], ans[maxn << 1], fac[maxn << 1], inv[maxn << 1], F[maxn], c[1000], b[maxn << 1], d[maxn << 1];
int Inv[maxn << 1];

inline vector<int> operator *(vector<int> a, vector<int> b)
{
    int n = a.size(), m = b.size(); vector<int> c; c.resize(n + m - 1);
    REP(i, 0, n - 1) REP(j, 0, m - 1) c[i + j] = (c[i + j] + a[i] * b[j]) % Mod;
    return c;
}
inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int x) { int val = fac[6 * x]; REP(i, 1, 6) val = val * inv[x] % Mod; return val; }
inline vector<int> Get(int i, int j)
{
    vector<int> p; p.resize(j * 2 + 1);
    p[0] = a[i][0]; p[j] = a[i][1]; p[j * 2] = a[i][2];
    return p;
}
inline void Modify(int pos, int val) { pos = (pos % P + P) % P; val = (val % Mod + Mod) % Mod; F[pos] ^= val; }
inline void calc(vector<int> a, int w, int k) 
{ 
    for ( int i = 0; i < a.size(); ++ i ) 
        ans[i * k] = (ans[i * k] + a[i] * w) % Mod; 
}
inline void Solve(vector<int> &a, int k, int N)
{
    int num = 0; while ( !a.empty() && !a.front() ) { a.erase(a.begin()); ++ num; }
    int n = a.size(); if ( !n ) return ; b[0] = power(a.front(), k);
    REP(i, 0, n - 2) c[i] = a[i + 1] * (i + 1) % Mod;
    int x = power(a[0], Mod - 2);
    REP(o, 1, N - k * num)
    {
        int ret1 = 0, ret2 = 0;
        REP(i, 0, n - 2) if ( o - i - 1 >= 0 ) ret1 += c[i] * b[o - i - 1];
        REP(i, 1, n - 1) if ( o - i >= 0 ) ret2 += a[i] * d[o - i];
        ret1 %= Mod; 
        b[o] = (ret1 * k - ret2) % Mod * Inv[o] % Mod * x % Mod;
        d[o] = b[o] * o % Mod;
    }
    a.clear(); REP(o, 0, N - k * num) a.emplace_back(b[o]);
    reverse(a.begin(), a.end());
    REP(i, 1, num * k) a.push_back(0);
    reverse(a.begin(), a.end());
}

signed main()
{
    freopen("rubik.in", "r", stdin);
    freopen("rubik.out", "w", stdout);
    scanf("%lld%lld", &n, &P); 
    N = n * n * 12; fac[0] = inv[0] = 1; REP(i, 1, N) fac[i] = fac[i - 1] * i % Mod;
    inv[N] = power(fac[N], Mod - 2); for ( int i = N - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 1, N) Inv[i] = inv[i] * fac[i - 1] % Mod;
    REP(i, 0, 5) REP(j, 0, 2) scanf("%lld", &a[i][j]);
    
    vector<int> a; a.push_back(1);
    REP(i, 0, 5) a = a * Get(i, 1);
    Solve(a, n * n, n * n * 12); calc(a, C(n * n), 1);

    if ( n % 3 == 0 ) 
    {
        a.clear(); a.push_back(1);
        REP(i, 0, 5) a = a * Get(i, 1);
        Solve(a, n * n / 3, n * n * 4);
        calc(a, C(n * n / 3) * 8 % Mod, 3);
    }

    if ( n % 2 == 0 )
    {
        a.clear(); a.push_back(1);
        REP(i, 0, 5) a = a * Get(i, 1);
        Solve(a, n * n / 2, n * n * 6);
        calc(a, C(n * n / 2) * 9 % Mod, 2);

        a.clear(); a.push_back(1);
        REP(i, 0, 5) a = a * Get(i, 1);
        Solve(a, n * n / 4, n * n * 3);
        calc(a, C(n * n / 4) * 6 % Mod, 4);
    }

    int x = power(24, Mod - 2);
    REP(i, 0, n * n * 12) Modify(i - 6 * n * n, ans[i] * x % Mod);
    int now = (1 - (P + 1) / 2 + P) % P;
    REP(i, 1, P) { printf("%lld ", F[now % P]); ++ now; } puts("");
    return 0;
}
