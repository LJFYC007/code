/***************************************************************
	File name: elysium.cpp
	Author: ljfcnyali
	Create time: 2020年09月19日 星期六 08时26分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], ans, dis[maxn];
int *f[maxn], F[maxn << 4], *tmp = F, son[maxn], MaxLen[maxn];
vector<pii> c[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; dis[v] = dis[u] + 1; DFS1(v);
        if ( MaxLen[v] > MaxLen[u] ) { MaxLen[u] = MaxLen[v]; son[u] = v; }
    }
    ++ MaxLen[u];
}

inline void DFS2(int u)
{
    if ( son[u] ) { f[son[u]] = f[u] + 1; DFS2(son[u]); }
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == son[u] ) continue ;
        f[v] = tmp; tmp += MaxLen[v];
        DFS2(v);
        REP(j, 0, MaxLen[v] - 1) f[u][j + 1] += f[v][j];
    }
    f[u][0] += a[u];
    for ( auto i : c[u] ) 
    {
        int ret = i.second;
        for ( int j = min(MaxLen[u] - 1, i.first); j >= 0; -- j ) 
        {
            if ( ret < f[u][j] ) { ans -= ret; f[u][j] -= ret; break ; }
            else { ans -= f[u][j]; ret -= f[u][j]; f[u][j] = 0; }
        }
    }
}

signed main()
{
    freopen("elysium.in", "r", stdin);
    freopen("elysium.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 2, n) { int u; scanf("%lld", &u); add(u, i); }
    REP(i, 1, n) { scanf("%lld", &a[i]); ans += a[i]; }
    REP(i, 1, m) { int x, d, v; scanf("%lld%lld%lld", &x, &d, &v); c[x].push_back(pii(d, v)); }
    dis[1] = 1; DFS1(1); f[1] = tmp; tmp += MaxLen[1];
    DFS2(1);
    printf("%lld\n", ans);
    return 0;
}
