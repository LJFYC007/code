/***************************************************************
	File name: destiny.cpp
	Author: ljfcnyali
	Create time: 2020年08月31日 星期一 20时52分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4010;
const int Mod = 998244353;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], f[maxn][maxn], dis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; DFS(v, u);
    }
}

inline void Solve(int u, int fa)
{
    REP(i, dis[u] - a[u] + 1, dis[u]) f[u][i] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        Solve(v, u);
        REP(j, dis[u] - a[u] + 1, dis[u]) f[u][j] = f[u][j] * (f[v][dis[v]] + f[v][j]) % Mod;
    }
    printf("%lld\n", u);
    REP(i, 1, n) printf("%lld ", f[u][i]); puts("");
}

signed main()
{
    freopen("destiny.in", "r", stdin);
    freopen("destiny1.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS(1, 0);
    scanf("%lld", &m);
    REP(i, 1, n) a[i] = dis[i];
    REP(i, 1, m) { int u, v; scanf("%lld%lld", &u, &v); a[v] = min(a[v], dis[v] - dis[u]); }
    Solve(1, 0);
    printf("%lld\n", (f[1][1] + Mod) % Mod);
    return 0;
}
