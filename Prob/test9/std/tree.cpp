/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2020年08月04日 星期二 16时56分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int seed = 233;
const int Mod = 998244353;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, h[maxn][maxn];
int size[maxn], inv[maxn], f[maxn], g[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) 
{ 
    int ret = 1;
    REP(i, n - m + 1, n) ret = ret * i % Mod;
    REP(i, 1, m) ret = ret * inv[i] % Mod;
    return ret;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    map<int, pii> Map; Map.clear(); size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u); size[u] += size[v]; 
        Map[g[v]].first = f[v]; ++ Map[g[v]].second; 
        g[u] = (g[u] + g[v] * seed) % Mod;
    }
    g[u] = g[u] * size[u] % Mod; if ( !g[u] ) g[u] = 1;
    f[u] = m;
    for ( auto i : Map ) 
    {
        int num = i.second.second, ret = 0;
        REP(j, 1, num) ret = (ret + h[num][j] * C(i.second.first, j)) % Mod;
        f[u] = f[u] * ret % Mod;
    }
}

signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) inv[i] = power(i, Mod - 2); 
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, n) h[i][1] = 1;
    REP(i, 2, n) REP(j, 2, i) h[i][j] = (h[i - 1][j - 1] + h[i - 1][j]) % Mod;
    DFS(1, 0);
    printf("%lld\n", (f[1] + Mod) % Mod);
    return 0;
}
