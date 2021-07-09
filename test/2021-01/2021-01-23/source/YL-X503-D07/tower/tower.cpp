/***************************************************************
	File name: tower.cpp
	Author: ljfcnyali
	Create time: 2021年01月23日 星期六 16时12分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, d, Begin[maxn], Next[maxn], To[maxn], e, ans, son[maxn], dis[maxn], anc[maxn];
int mem[maxn * 100], *f[maxn], *now = mem, g[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void give(int x) { f[x] = now; now += dis[x] + 1; }

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        DFS1(v, u);
        if ( dis[v] + 1 > dis[u] ) { dis[u] = dis[v] + 1; son[u] = v; } 
    }
}

inline void DFS2(int u, int fa)
{
    REP(i, 0, dis[u]) ++ f[u][i];
    if ( son[u] ) { f[son[u]] = f[u] + 1; DFS2(son[u], u); } 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || v == son[u] ) continue ; 
        give(v); DFS2(v, u); REP(j, 0, dis[v]) f[u][j + 1] += f[v][j];
        REP(j, dis[v] + 2, dis[u]) f[u][j] += f[v][dis[v]];
    }
}

inline void Modify(int u, int now, int val) 
{ 
    REP(i, 0, dis[u]) g[now + i] += val * f[u][i]; 
}

inline int Check(int u, int now, int i)
{
    if ( i < 0 ) return 0;
    cout << u << " " << now << " " << i << " " << f[u][min(dis[u], i)] << " " << g[now + min(dis[u], i)] << endl;
    return g[now + min(dis[u], i)] + f[u][min(dis[u], i)]; 
}

inline int Solve1(int u, int now, int r)
{
    if ( r < 0 || g[now + min(dis[u], r)] + f[u][min(dis[u], r)] < m ) return 0;
    return g[now + min(dis[u], d - r)] + f[u][min(dis[u], d - r)];

    int ret = 0;
    REP(i, 0, min(dis[u], r)) ret += g[now + i] + f[u][i];
    if ( ret < m ) return 0;
    ret = 0;
    REP(i, 0, min(dis[u], d - r)) ret += g[now + i] + f[u][i];
    return ret;
}

inline int Solve2(int u, int now, int r)
{
    if ( r < 0 || g[now + min(dis[u], r) + 1] + f[u][min(dis[u], r)] < m ) return 0;
    return g[now + min(dis[u], d - r - 1) + 1] + f[u][min(dis[u], d - r - 1)];

    if ( r < 0 ) return 0;
    int ret = 0;
    REP(i, 0, min(dis[u], r)) ret += g[now + i + 1] + f[u][i];
    if ( ret < m ) return 0;
    ret = 0;
    REP(i, 0, min(dis[u], d - r - 1)) ret += g[now + i + 1] + f[u][i];
    return ret;
}

inline void DFS3(int u, int fa, int now, int lst)
{
    int x = lst;
    if ( lst == -1 ) { REP(i, 0, d) if ( Check(u, now, i) >= m ) { x = i; break ; } }
    else { REP(i, lst - 1, lst + 1) if ( Check(u, now, i) >= m ) { x = i; break ; } }
    // cout << u << " " << x << " " << Solve1(u, now, x) << endl;
    ans = max(ans, Solve1(u, now, x));
    REP(i, 0, d) ans = max(ans, Solve2(u, now, i));

    Modify(u, now, 1);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || v == son[u] ) continue ; 
        Modify(v, now + 1, -1); DFS3(v, u, now - 1, x); Modify(v, now + 1, 1);
    }
    if ( son[u] ) 
    {
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa || v == son[u] ) continue ;
            REP(j, 0, dis[v]) f[u][j + 1] -= f[v][j];
            REP(j, dis[v] + 2, dis[u]) f[u][j] -= f[v][dis[v]];
        }
        Modify(son[u], now + 1, -1); DFS3(son[u], u, now - 1, x); Modify(son[u], now + 1, 1);
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa || v == son[u] ) continue ;
            REP(j, 0, dis[v]) f[u][j + 1] += f[v][j];
            REP(j, dis[v] + 2, dis[u]) f[u][j] += f[v][dis[v]];
        }
    }
    Modify(u, now, -1);
}

int main()
{
    freopen("tower.in", "r", stdin);
    freopen("tower.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &d);
    REP(i, 2, n) { int x; scanf("%d", &x); add(i, x); add(x, i); anc[i] = x; } 
    DFS1(1, 0); give(1); DFS2(1, 0); DFS3(1, 0, n, -1);
    printf("%d\n", ans);
    return 0;
}
