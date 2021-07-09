/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年08月13日 星期四 16时46分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;
const int Mod = 998244353;

int n, k, Begin[maxn], Next[maxn], To[maxn], e, f[maxn][21][21], g[maxn][21][21];
vector<int> son[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFSAlice(int u);
inline void DFSBob(int u);

inline void DFSBob(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) DFSAlice(To[i]);
    if ( !son[u].size() ) 
    {
        REP(i, 1, k) REP(j, 1, k) { f[u][i][j] = i * j; g[u][i][j] = 1; }
        return ;
    }
    REP(i, 1, k) REP(j, 1, k) 
    {
        f[u][i][j] = (f[u][i][j] + f[son[u][0]][i][j] * f[son[u][1]][k][j]) % Mod;
        f[u][i][j] = (f[u][i][j] + f[son[u][1]][i][j] * f[son[u][0]][k][j]) % Mod;
        g[u][i][j] = (g[u][i][j] + g[son[u][0]][i][j] * f[son[u][1]][k][j]) % Mod;
        g[u][i][j] = (g[u][i][j] + g[son[u][1]][i][j] * f[son[u][0]][k][j]) % Mod;
    }
}

inline void DFSAlice(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) DFSBob(To[i]);
    if ( !son[u].size() ) 
    {
        REP(i, 1, k) REP(j, 1, k) { f[u][i][j] = i * j; g[u][i][j] = 1; }
        return ;
    }
    REP(i, 1, k) REP(j, 1, k) 
    {
        f[u][i][j] = (f[u][i][j] + f[son[u][0]][i][j] * f[son[u][1]][i][k]) % Mod;
        f[u][i][j] = (f[u][i][j] + f[son[u][1]][i][j] * f[son[u][0]][i][k]) % Mod;
        g[u][i][j] = (g[u][i][j] + g[son[u][0]][i][j] * f[son[u][1]][i][k]) % Mod;
        g[u][i][j] = (g[u][i][j] + g[son[u][1]][i][j] * f[son[u][0]][i][k]) % Mod;
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n - 1) { int x; scanf("%lld", &x); add(x, i); son[x].push_back(i); }
    DFSAlice(0);
    int ans = 0;
    REP(i, 1, k) REP(j, 1, k) ans = (ans + g[0][i][j]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
