/***************************************************************
	File name: dawn.cpp
	Author: ljfcnyali
	Create time: 2019年11月04日 星期一 15时13分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 200010;
const int Mod = 998244353;

int T, n, m, Begin[maxn], Next[maxn], To[maxn], e;
int f[maxn][110], size[maxn], dis[maxn], anc[maxn][20];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

inline void DFS(int u, int fa)
{
    size[u] = 1; REP(i, 1, 100) f[u][i] = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u;
        DFS(v, u);
        size[u] += size[v];
        REP(j, 1, 100) f[u][j] += power(size[v], j);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int j = 18; j >= 0; -- j ) if ( dis[anc[x][j]] >= dis[y] ) x = anc[x][j];
    if ( x == y ) return x;
    for ( int j = 18; j >= 0; -- j ) if ( anc[x][j] != anc[y][j] ) { x = anc[x][j]; y = anc[y][j]; }
    return anc[x][0];
}

signed main()
{
    freopen("dawn.in", "r", stdin);
    freopen("dawn.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &n, &m);
        mem(Begin); e = 0;
        REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
        dis[1] = 1; DFS(1, 0); REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
        REP(i, 1, m)
        {
            int k, u, v; scanf("%lld%lld%lld", &k, &u, &v);
            if ( dis[u] > dis[v] ) swap(u, v);
            int ans = 0, t = LCA(u, v), sum1; 
            if ( t == u ) 
            {
                int x = v;
                for ( int j = 18; j >= 0; -- j ) if ( dis[anc[x][j]] > dis[t] ) x = anc[x][j];
                sum1 = power(n - size[x], k);
                int sum = (f[u][k] - power(size[x], k) + power(n - size[u], k)) % Mod;
                sum1 = (sum1 - sum + Mod) % Mod;
            }
            else sum1 = (power(size[u], k) - f[u][k] + Mod) % Mod;
            int sum2 = (power(size[v], k) - f[v][k] + Mod) % Mod;
            ans = sum1 * sum2 % Mod;
            printf("%lld\n", (ans + Mod) % Mod);
        }
    }
    return 0;
}
