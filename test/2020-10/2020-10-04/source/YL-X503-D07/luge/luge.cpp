/***************************************************************
	File name: luge.cpp
	Author: ljfcnyali
	Create time: 2020年10月04日 星期日 08时33分59秒
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
const int inv2 = (Mod + 1) / 2;

int n, k, a[maxn], f[maxn][maxn], Begin[maxn << 1], Next[maxn << 1], To[maxn << 1], e;
int size[maxn], dfn[maxn], tot, id[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u, int fa)
{
    size[u] = 1; dfn[u] = ++ tot; id[tot] = u; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS1(v, u); size[u] += size[v];
    }
}

signed main()
{
    freopen("luge.in", "r", stdin);
    freopen("luge.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    DFS1(1, 0); 
    f[1][min(a[1], k + 1)] = 1;
    REP(i, 1, n - 1) REP(j, 0, k + 1)
    {
        f[i + 1][min(k + 1, j + a[id[i + 1]])] = (f[i + 1][min(k + 1, j + a[id[i + 1]])] + f[i][j] * inv2) % Mod;
        f[i + size[id[i + 1]]][j] = (f[i + size[id[i + 1]]][j] + f[i][j] * inv2) % Mod;
    }
    printf("%lld\n", (f[n][k] + Mod) % Mod);
    return 0;
}
