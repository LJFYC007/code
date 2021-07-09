#include<bits/stdc++.h>
  
using namespace std;
  
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
  
const int maxn = 4e5 + 10;
const int Mod = 998244353;
  
int n, m, a[maxn], fac[maxn], inv[maxn], r[maxn];
vector<int> f, g;
  
inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
 
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; } 

inline int add(int x, int y) { return x + y >= Mod ? x + y - Mod : x + y; } 
  
inline void NTT(vector<int> &f, int n, int inv)
{
	REP(i, 0, n - 1) f[i] = f[i] < 0 ? f[i] + Mod : f[i];
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
				f[i + j] = add(x, y); f[i + Mid + j] = add(x, Mod - y);
                // f[i + j] = (x + y) % Mod; f[i + Mid + j] = (x - y) % Mod;
            }
        }
    }
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2); 
        REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
    }
}
  
vector<int> operator -(vector<int> a, vector<int> b)
{
    int n = max(a.size(), b.size()); a.resize(n); b.resize(n);
    REP(i, 0, n - 1) a[i] = (a[i] - b[i]) % Mod; return a;
}
 
vector<int> operator *(vector<int> a, vector<int> b)
{
    int n = a.size(), m = b.size(), l = 1;
    while ( l < n + m - 1 ) l <<= 1; a.resize(l); b.resize(l);
    NTT(a, l, 1); NTT(b, l, 1); REP(i, 0, l - 1) a[i] = a[i] * b[i] % Mod; NTT(a, l, -1);
    a.resize(n + m - 1); return a;
}
 
vector<int> down(vector<int> a)
{
    int n = a.size(); REP(i, 0, n - 2) a[i] = (i + 1) * a[i + 1] % Mod;
    a.resize(n - 1); return a;
}
 
vector<int> up(vector<int> a)
{
    int n = a.size(); a.resize(n + 1); 
    for ( int i = n; i >= 1; -- i ) a[i] = a[i - 1] * power(i, Mod - 2) % Mod;
    a[0] = 0; return a;
}
 
vector<int> rev(vector<int> a)
{
    int n = a.size();
    REP(i, 0, n - 1) if ( i < n - i - 1 ) swap(a[i], a[n - i - 1]);
    return a;
}
 
vector<int> Inv(vector<int> a)
{
    int n = a.size();
    vector<int> f; if ( n == 1 ) { f.resize(1); f[0] = power(a[0], Mod - 2); return f; } 
    vector<int> b = a; b.resize((n + 1) / 2); b = Inv(b);
    f = a * b; REP(i, 0, n - 1) f[i] = -f[i]; f[0] += 2; f.resize(n);
    f = f * b; f.resize(n); return f;
}
 
vector<int> ln(vector<int> a)
{
    int n = a.size();
    vector<int> f = down(a) * Inv(a); f.resize(n - 1);
    return up(f);
}
 
vector<int> exp(vector<int> a)
{
    int n = a.size();
    vector<int> f; if ( n == 1 ) { f.resize(1); f[0] = 1; return f; } 
    vector<int> b = a; b.resize((n + 1) / 2); b = exp(b); b.resize(n);
    f = a - ln(b); ++ f[0]; f = f * b; f.resize(n); return f;
}
 
inline vector<int> Solve(int l, int r)
{
    vector<int> f;
    if ( l == r ) { f.resize(2); f[0] = -a[l]; f[1] = 1; return f; } 
    int Mid = l + r >> 1;
    f = Solve(l, Mid) * Solve(Mid + 1, r);
    return f;
}
  
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld", &n, &m); 
    REP(i, 1, n) scanf("%lld", &a[i]);
    f.resize(m + 1); REP(i, 0, m) f[i] = inv[i + 1]; f = ln(f); 
    g = Solve(1, n); g = rev(down(g)) * Inv(rev(g));
    REP(i, 0, m) f[i] = f[i] * g[i] % Mod;
    f = exp(f); REP(i, 1, m) printf("%lld ", (f[i] * fac[i] % Mod + Mod) % Mod); puts("");
    return 0;
}
