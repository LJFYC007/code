/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年06月03日 星期三 15时01分29秒
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

inline void NTT(vector<int> &f, int inv)
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
}

int n, m, Begin[maxn], Next[maxn], To[maxn], e, size[maxn], f[maxn];
int fac[maxn], inv[maxn], ans, num[maxn];
vector<int> a[maxn], p, b, c;

inline int A(int n, int m) { return n < m ? 0 : fac[n] * inv[n - m] % Mod; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline vector<int> Mul(vector<int> f, vector<int> g)
{
    int n = f.size() + g.size() - 1;
    int len = 1; while ( len <= (n << 1) ) len <<= 1;
    f.resize(len); g.resize(len); 
    // for ( auto i : f ) printf("%lld ", i); puts("");
    // for ( auto i : g ) printf("%lld ", i); puts("");
    NTT(f, 1); NTT(g, 1); REP(i, 0, len - 1) f[i] = f[i] * g[i] % Mod; NTT(f, -1);
    // for ( auto i : f ) printf("%lld ", i); puts("");
    f.resize(n); return f;
}

inline vector<int> Inv(vector<int> a, int x)
{
    vector<int> b; b.resize(a.size() - 1);
    b[0] = a[0];
    for ( int i = 1; i < b.size(); ++ i ) b[i] = (a[i] - x * b[i - 1]) % Mod;
    return b;
}

inline vector<int> Solve(int l, int r)
{
    if ( l == r ) 
    {
        vector<int> f; f.resize(2);
        f[0] = 1; f[1] = p[l];
        return f;
    }
    int Mid = l + r >> 1;
    vector<int> f = Solve(l, Mid), g = Solve(Mid + 1, r);
    return Mul(f, g);
}

inline void DFS1(int u, int fa)
{
    size[u] = 1; vector<int> g; g.clear();
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS1(v, u); size[u] += size[v];
        g.push_back(size[v]); 
    }
    p = g; p.push_back(0);
    a[u] = Solve(0, p.size() - 1);
    for ( int i = 0; i < a[u].size(); ++ i ) f[u] = (f[u] + a[u][i] * A(m, i)) % Mod;
    int sum = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        ans = (ans + sum * f[v]) % Mod;
        f[u] = (f[u] + f[v]) % Mod; sum = (sum + f[v]) % Mod;
    }
}

inline void DFS2(int u, int fa)
{
    p.clear();
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( !num[size[v]] ) p.push_back(size[v]);
        num[size[v]] += f[v];
    }

    b.resize(2); b[0] = 1; b[1] = n - size[u];
    a[u] = Mul(a[u], b);
    for ( auto o : p ) 
    {
        b = Inv(a[u], o);
        int sum = 0;
        for ( int i = 0; i < b.size(); ++ i ) sum = (sum + b[i] * A(m, i)) % Mod;
        ans = (ans + sum * num[o]) % Mod;
    }

    for ( int i = Begin[u]; i; i = Next[i] ) 
    { 
        int v = To[i]; if ( v == fa ) continue ; 
        num[size[v]] = 0; 
    }

    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS2(v, u);
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    n = maxn - 10;
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld", &n, &m);
    if ( m == 1 ) { printf("%lld\n", (n * (n - 1) / 2) % Mod); return 0; }
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    DFS1(1, 0); DFS2(1, 0);
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
