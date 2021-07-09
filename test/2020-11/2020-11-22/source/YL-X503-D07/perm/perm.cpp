/***************************************************************
	File name: perm.cpp
	Author: ljfcnyali
	Create time: 2020年11月22日 星期日 11时15分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;
const int Mod = 1e9 + 7;

int T, n, a[maxn], b[maxn], fac[maxn], inv[maxn], f[1010][1010][2], g[1010][1010], h[maxn];
int e, Begin[maxn], Next[maxn], To[maxn], cnt, c[maxn];
vector<int> p;
bool vis[maxn];

inline int sgn(int x) { return x & 1 ? -1 : 1; }

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    ++ cnt;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        if ( !vis[v] ) { vis[v] = true; DFS(v); }
    }
}

signed main()
{
    freopen("perm.in", "r", stdin);
    freopen("perm.out", "w", stdout);
    scanf("%lld", &T);

    n = 1000; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    f[1][0][0] = 1;
    REP(i, 2, n) REP(j, 0, i - 1) 
    {
        f[i][j][0] = (f[i - 1][j][0] + f[i - 1][j][1]) % Mod;
        if ( j >= 1 ) 
        {
            f[i][j][0] = (f[i][j][0] + f[i - 1][j - 1][0]) % Mod;
            f[i][j][1] = (f[i - 1][j - 1][0] + f[i - 1][j - 1][1]) % Mod;
        }
    }
    REP(j, 1, n) 
    {
        REP(i, 0, j - 1) g[j][i] = ((f[j][i][0] + f[j][i][1]) * j % Mod) * power(j - i, Mod - 2) % Mod;
        g[j][j] = 2; 
    }

    while ( T -- ) 
    {
        scanf("%lld", &n); 
        REP(i, 1, n) { int x; scanf("%lld", &x); a[x] = i; }
        REP(i, 1, n) { int x; scanf("%lld", &x); b[x] = i; }
        e = 0; mem(Begin); mem(h); mem(vis); p.clear();
        REP(i, 1, n) { add(a[i], b[i]); add(b[i], a[i]); }

        REP(i, 1, n) if ( !vis[i] ) { cnt = 0; vis[i] = true; DFS(i); p.push_back(cnt); }

        h[0] = 1;
        for ( auto it : p ) 
        {
            int m = it; mem(c);
            REP(i, 0, n) REP(j, 0, min(i, m)) c[i] = (c[i] + h[i - j] * g[m][j]) % Mod;
            REP(i, 0, n) h[i] = c[i];
        }

        int ans = 0;
        REP(i, 0, n) ans = (ans + sgn(i) * fac[n - i] * h[i]) % Mod;
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
