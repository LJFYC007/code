/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年06月03日 星期三 08时11分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, k, Begin[maxn], Next[maxn], To[maxn], e, size[maxn], dis[maxn], anc[maxn][20], ans, fac[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        anc[v][0] = u; dis[v] = dis[u] + 1;
        DFS(v, u);
        size[u] += size[v];
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

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i;
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    dis[1] = 1; DFS(1, 0);     
    REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    REP(i, 1, n) REP(j, i + 1, n)
    {
        int t = LCA(i, j), x, y;        
        if ( t != i && t != j ) 
        {
            x = size[i] - 1; y = size[j] - 1;
        }
        else 
        {
            int u = i, v = j;
            if ( t == i ) swap(u, v);
            x = size[u] - 1; 
            while ( anc[u][0] != v ) u = anc[u][0];
            y = n - size[u] - 1;
        }
        int sum = 0;
        sum += x * y * ((fac[k] / fac[k - 2]) + k);
        sum += k * (x + y);
        ++ sum;
        ans += sum;
        printf("%d %d %d %d %d\n", i, j, x, y, sum);
    }
    printf("%d\n", ans);
    return 0;
}
