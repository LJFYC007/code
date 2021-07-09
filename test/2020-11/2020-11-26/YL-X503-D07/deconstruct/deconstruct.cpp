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
int fac[maxn], inv[maxn], dis[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
// inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[n - m] % Mod) * inv[m] % Mod; }
// inline int A(int n, int m) { return n < m ? 0 : fac[n] * inv[n - m] % Mod; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) { dis[To[i]] = dis[u] + 1; DFS(To[i]); size[u] += size[To[i]]; }
    if ( u == 1 ) return ;
    ans = (ans + size[u] * power(dis[u] - 1, Mod - 2)) % Mod;
}

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
    freopen("deconstruct.in", "r", stdin);
    freopen("deconstruct.out", "w", stdout);
    scanf("%lld", &n); // fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    // inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 2, n) { int x; read(x); add(x, i); }
    dis[1] = 1; DFS(1); 
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
