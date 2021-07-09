/***************************************************************
	File name: travel.cpp
	Author: ljfcnyali
	Create time: 2020年09月09日 星期三 21时10分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, q, v[maxn], Begin[maxn], Next[maxn], To[maxn], e, anc[maxn][11], dis[maxn];
bitset<1000> f[maxn][5], Set, S;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v][0] = u; DFS(v, u);
    }
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int i = 4; i >= 0; -- i ) while ( dis[anc[x][i]] >= dis[y] ) x = anc[x][i];
    if ( x == y ) return x;
    for ( int i = 4; i >= 0; -- i ) while ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; }
    return anc[x][0];
}

inline bitset<1000> Solve(int s, int t)
{
    S.reset();
    for ( int i = 4; i >= 0; -- i ) while ( dis[anc[s][i]] >= dis[t] ) 
    {
        S |= f[s][i]; s = anc[s][i];
    }
    return S;
}

int main()
{
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 2, n) { int x; scanf("%d", &x); add(x, i); }
    REP(i, 1, n) { int x; scanf("%d", &x); f[i][0][x - 1] = 1; }
    dis[1] = 1; DFS(1, 0);
    REP(j, 1, 4) REP(i, 1, n)
    {
        f[i][j] = f[i][j - 1];
        int x = anc[i][j - 1]; f[i][j] |= f[x][j - 1];
        x = anc[x][j - 1]; f[i][j] |= f[x][j - 1];
        x = anc[x][j - 1]; f[i][j] |= f[x][j - 1];
        x = anc[x][j - 1]; f[i][j] |= f[x][j - 1];
        x = anc[x][j - 1]; f[i][j] |= f[x][j - 1];
        x = anc[x][j - 1]; f[i][j] |= f[x][j - 1];
        x = anc[x][j - 1]; anc[i][j] = x;
    }
    while ( q -- ) 
    {
        int c, x; scanf("%d", &c);
        REP(i, 1, c) scanf("%d", &v[i]);
        x = v[1]; REP(i, 2, c) x = LCA(x, v[i]);

        int ans = INF;
        REP(i, 1, (1 << c) - 1) 
        {
            Set = f[x][0]; int num = 0;
            REP(j, 1, c) if ( (i >> j - 1) & 1 ) { ++ num; Set |= Solve(v[j], x); }
            ans = min(ans, (int)Set.count() / num);
        }
        printf("%d\n", ans * c);
    }
    return 0;
}
