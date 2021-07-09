/***************************************************************
	File name: ball.cpp
	Author: ljfcnyali
	Create time: 2020年11月04日 星期三 09时41分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 1e9 + 7;

int n, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], f[maxn], num[maxn];
int h[maxn], fac[maxn], inv[maxn], size[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void DFS(int u)
{
    int son = 0; f[u] = 1; size[u] = a[u]; num[u] = a[u] - 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; DFS(v);
        f[u] = f[u] * f[v] % Mod; num[u] += num[v];
        ++ son; size[u] += size[v];
    }
    f[u] = f[u] * (num[u] + 1) % Mod * power(size[u] - num[u], Mod - 2) % Mod;
    if ( !son ) f[u] = inv[a[u] - 1];
}

signed main()
{
    freopen("ball.in", "r", stdin);
    freopen("ball.out", "w", stdout);
    scanf("%lld", &n);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 2, n) { int x; scanf("%lld", &x); add(x, i); }
    REP(i, 1, n) scanf("%lld", &a[i]);
    DFS(1);
    int ans = f[1] * fac[size[1]] % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
