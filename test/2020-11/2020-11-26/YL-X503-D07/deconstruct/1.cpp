/***************************************************************
	File name: deconstruct.cpp
	Author: ljfcnyali
	Create time: 2020年11月26日 星期四 08时40分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 1e9 + 7;

int n, Begin[maxn], Next[maxn], To[maxn], e, ans, sum, size[maxn];
int fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[n - m] % Mod) * inv[m] % Mod; }
inline int A(int n, int m) { return n < m ? 0 : fac[n] * inv[n - m] % Mod; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int dep, int t, int x)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; DFS1(v, dep + 1, t, x);
        if ( x ) sum = (sum + A(n - 2 - dep, x - 1) * x % Mod * size[v]) % Mod;
    }
}

inline void DFS(int u)
{
    size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) { DFS(To[i]); size[u] += size[To[i]]; }
    if ( u == 1 ) return ;
    ans = (ans + fac[n - 1] * size[u]) % Mod;
    REP(i, 0, n - 2)
    {
        sum = 0; DFS1(u, 1, u, i);
        ans = (ans - sum * fac[n - i - 2]) % Mod;
    }
}

signed main()
{
    freopen("deconstruct.in", "r", stdin);
    freopen("deconstruct.out", "w", stdout);
    scanf("%lld", &n); fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 2, n) { int x; scanf("%lld", &x); add(x, i); }
    DFS(1);
    ans = ans * inv[n - 1] % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
