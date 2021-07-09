/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年11月13日 星期五 10时00分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int n, a[maxn], b[maxn], f[maxn], g, ans[maxn], r[maxn], c[maxn];
vector<int> A, B;
bool vis[maxn];

inline LL power(LL a, LL b) { LL r = 1; while ( b ) { if ( b & 1 ) r = r * a % n; a = a * a % n; b >>= 1; } return r; }

inline bool check()
{
    int x = n - 1;
    for ( int i = 2; i * i <= x; ++ i ) 
    {
        if ( x % i != 0 ) continue ;
        while ( x % i == 0 ) x /= i;
        if ( power(g, (n - 1) / i) == 1 ) return false;
    }
    if ( x && power(g, (n - 1) / x) == 1 ) return false;
    return true;
}

inline LL power(LL a, int b, int Mod)
{
    LL r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; }
    return r;
}

inline vector<int> NTT(vector<int> f, int inv)
{
    int n = f.size();
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
    for ( int Mid = 1; Mid < n; Mid <<= 1 )
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1), Mod);
        if ( inv == -1 ) tmp = power(tmp, Mod - 2, Mod);
        for ( int i = 0; i < n; i += (Mid << 1) )
        {
            LL sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = (sum * tmp) % Mod )
            {
                int x = f[i + j], y = (sum * f[i + j + Mid]) % Mod;
                f[i + j] = (x + y) % Mod; f[i + j + Mid] = (x - y + Mod) % Mod;
            }
        }
    }
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2, Mod);
        REP(i, 0, n - 1) f[i] = 1ll * f[i] * inv % Mod;
    }
    return f;
}

inline vector<int> operator *(vector<int> a, vector<int> b)
{
    int n = a.size(), m = b.size(), len = 1;
    while ( len <= n + m ) len <<= 1; a.resize(len); b.resize(len);
    a = NTT(a, 1); b = NTT(b, 1); REP(i, 0, len - 1) a[i] = 1ll * a[i] * b[i] % Mod; a = NTT(a, -1);
    a.resize(n + m - 1); 
    for ( auto &it : a ) it = (it + Mod) % Mod;
    return a;
}

signed main()
{
    freopen("mode.in", "r", stdin);
    freopen("mode.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n - 1) { int x; scanf("%d", &x); ++ a[x]; }
    REP(i, 1, n - 1) { int x; scanf("%d", &x); ++ b[x]; }
    REP(i, 1, n - 1) vis[a[i]] = vis[b[i]] = true;

    g = 2;
    while ( !check() ) ++ g;
    LL now = 1;
    REP(i, 1, n - 1) { now = now * g % n; f[now] = i; }

    REP(j, 1, n - 1) 
    {
        if ( a[j] >= 6 ) A.push_back(j);
        if ( b[j] >= 6 ) B.push_back(j);
    }
    for ( auto x : A ) for ( auto y : B ) 
    {
        ans[(f[x] + f[y]) % (n - 1)] += min(a[x], b[y]);
        ++ c[(f[x] + f[y]) % (n - 1)];
    }

    for ( int i = 5; i >= 1; -- i )
    {
        if ( !vis[i] ) continue ;
        A.clear(); B.clear(); A.resize(n); B.resize(n);
        REP(j, 1, n - 1) { A[f[j]] = (a[j] >= i); B[f[j]] = (b[j] >= i); }
        A = A * B;
        for ( int j = 0; j < A.size(); ++ j ) ans[j % (n - 1)] += (A[j] - c[j]) * i;
        for ( int j = 0; j < A.size(); ++ j ) c[j] = A[j];
    }
    int ret = 0; REP(i, 0, n - 2) ret = max(ret, ans[i]);
    printf("%d\n", ret);
    return 0;
}
