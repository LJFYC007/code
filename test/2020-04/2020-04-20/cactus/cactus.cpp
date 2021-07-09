/***************************************************************
	File name: cactus.cpp
	Author: ljfcnyali
	Create time: 2020年04月21日 星期二 19时57分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e4 + 10;
const int Mod = 1e9 + 7;

int n, m, k, Begin[maxn], Next[maxn], To[maxn], e;
int f[maxn][110][3][2][2][2], g[maxn][110][3][2][2][2];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    f[u][0][0][0][0][0] = 1;
    f[u][1][1][1][0][0] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        REP(size, 0, k) REP(count, 0, 2) REP(sel, 0, 1) REP(up, 0, 1) REP(in, 0, 1) 
        {
            g[u][size][count][sel][up][in] = f[u][size][count][sel][up][in]; 
            f[u][size][count][sel][up][in] = 0;
        }
        REP(size1, 0, k) REP(size2, 1, k) REP(count1, 0, 2) REP(count2, 1, 2) 
        {
            if ( size1 + size2 > k ) continue ;
        }
        REP(size, 0, k) REP(count, 0, 2) REP(sel, 0, 1) REP(up, 0, 1) REP(in, 0, 1) 
            f[u][size][count][sel][up][in] = g[u][size][count][sel][up][in]; 
    }
}

signed main()
{
    freopen("cactus.in", "r", stdin);
    freopen("cactus.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &k);
    REP(i, 1, m) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    DFS(1, 0);
    int ans = (f[1][k][1][1][0][0] + f[1][k][1][0][0][0]) % Mod;
    printf("%lld\n", ans);
    return 0;
}
