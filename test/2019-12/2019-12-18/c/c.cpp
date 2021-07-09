/***************************************************************
	File name: c.cpp
	Author: ljfcnyali
	Create time: 2019年12月18日 星期三 11时29分22秒
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
const int Mod = 998244353;

int n, m, k, q, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], f[maxn][maxn], ans[maxn][maxn];
bool vis[110];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void DFS(int u, int t)
{
    if ( u == t || vis[u] ) return ;
    vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) DFS(To[i], t);
}

inline int Solve(int u, int v)
{
    mem(vis);
    DFS(1, u);
    int ret = 0;
    REP(i, 1, n) if ( !vis[i] ) ret = (ret + power(f[i][v] % Mod, k)) % Mod;
    return ret;
}

signed main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%lld%lld%lld%lld", &n, &m, &k, &q);
    memset(f, 0x3f, sizeof(f));
    REP(i, 1, n) f[i][i] = 0;
    REP(i, 1, m)
    {
        int u, v, w; scanf("%lld%lld%lld", &u, &v, &w);
        add(u, v, w); add(v, u, w);
        f[u][v] = f[v][u] = min(f[u][v], w);
    }
    REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    REP(i, 1, n) REP(j, 1, n) ans[i][j] = Solve(i, j);
    REP(i, 1, q)
    {
        int x, y; scanf("%lld%lld", &x, &y);
        printf("%lld\n", ans[x][y]);
    }
    return 0;
}
