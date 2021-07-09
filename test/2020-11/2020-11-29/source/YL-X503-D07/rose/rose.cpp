/***************************************************************
	File name: rose.cpp
	Author: ljfcnyali-akioi
	Create time: 2020年11月29日 星期日 08时37分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e5 + 10;
const int seed = 233;
const int Mod = 998244353;

int n, m, fa[maxn], son[maxn][2], dis[maxn], p[maxn], inv[maxn], val;
int ans[maxn], Stack[maxn], tot, anc[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void DFS(int u, int x)
{
    if ( dis[u] >= m ) 
    {
        if ( dis[u] > m ) x = (x - p[m] * Stack[tot - m]) % Mod;
        x = (x + Mod) % Mod;
        if ( x == val ) ans[anc[tot - m + 1]] = u;
    }
    REP(i, 0, 1)
    {
        if ( !son[u][i] ) continue ;
        dis[son[u][i]] = dis[u] + 1; ++ tot;
        Stack[tot] = i; anc[tot] = u;
        DFS(son[u][i], (x * seed + i) % Mod); -- tot;
    }
}

signed main()
{
    freopen("rose.in", "r", stdin);
    freopen("rose.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); fa[v] = u; son[u][w] = v; }
    p[0] = inv[0] = 1; REP(i, 1, n) p[i] = p[i - 1] * seed % Mod;
    inv[1] = power(seed, Mod - 2); REP(i, 2, n) inv[i] = inv[i - 1] * inv[1] % Mod;
    scanf("%lld", &m);
    REP(i, 1, m) { int x; scanf("%lld", &x); val = (val * seed + x) % Mod; }

    dis[1] = 0; DFS(1, 0);
    REP(i, 1, n) printf("%lld ", ans[i]); puts("");
    return 0;
}
