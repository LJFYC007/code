#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long

const int maxn = 1010;
const int Mod = 998244353;

int n, k, g[maxn], h[maxn], size[maxn]; vector<int> f[maxn];
int Begin[maxn], Next[maxn], To[maxn], e, fac[maxn], inv[maxn], invs[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; }
inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u, int fa, int x)
{
    size[u] = 1; int son = 0;
    for ( int o = Begin[u]; o; o = Next[o] ) 
    {
        int v = To[o]; if ( v == fa ) continue ; DFS(v, u, x);
        if ( size[v] > size[son] ) son = v; size[u] += size[v];
    }
    f[u].clear(); int sum = 0;
    if ( son ) 
    {
        swap(f[u], f[son]);
        sum = size[son];
    }
    else f[u].resize(1, 1);
    for ( int o = Begin[u]; o; o = Next[o] ) 
    {
        int v = To[o]; if ( v == fa || v == son ) continue ; 
        REP(i, 0, sum) REP(j, 0, size[v]) g[i + j] = (g[i + j] + f[u][i] * f[v][j]) % Mod;
        sum += size[v]; f[u].resize(sum + 1);
        REP(i, 0, sum) f[u][i] = g[i], g[i] = 0;
    } 
    f[u].resize(size[u] + 1);
    REP(i, 1, size[u]) g[i] = (f[u][i - 1] * x + (size[u] - i + 1) * g[i - 1]) % Mod * invs[i] % Mod;
    REP(i, 1, size[u]) { f[u][i] = (f[u][i] + g[i]) % Mod; g[i] = 0; }
}

vector<int> operator *(vector<int> a, vector<int> b)
{
    int n = a.size(), m = b.size();
    vector<int> c(n + m - 1);
    REP(i, 0, n - 1) REP(j, 0, m - 1) c[i + j] = (c[i + j] + a[i] * b[j]) % Mod;
    return c;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n - 1) 
    { 
        int u, v; scanf("%lld%lld", &u, &v); 
        add(u, v); add(v, u); 
    } 
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    invs[0] = 1; REP(i, 1, n) invs[i] = fac[i - 1] * inv[i] % Mod;
    REP(x, 0, n) { DFS(1, 0, x); h[x] = f[1][n]; } 
    int ans = 0;
    REP(i, 0, n)
    {
        vector<int> a(1, 1);
        REP(j, 0, n) if ( j != i ) 
        {
            int x = power(i - j, Mod - 2);
            vector<int> b(2); b[0] = -j * x % Mod; b[1] = x;
            a = a * b;
        }
        REP(j, 1, k) ans = (ans + a[j] * h[i]) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}