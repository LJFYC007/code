/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年06月02日 星期二 15时16分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 2010;
const int INF = 0x3f3f3f3f;

int n, m, k, f[maxn][maxn], dp[maxn][maxn], g[maxn], ans;
bool vis[maxn][maxn];
queue<pii> Q;

inline bool Check(int x)
{
    for ( int i = 1; i <= k; i += 2 ) 
        if ( ((x >> i - 1) & 1) != ((x >> i) & 1) ) return false; 
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k);
    memset(dp, 0x3f, sizeof(dp)); memset(f, 0x3f, sizeof(f)); memset(g, 0x3f, sizeof(g));     
    REP(i, 1, n) f[i][i] = 0;
    REP(i, 1, m)
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        f[u][v] = f[v][u] = min(f[u][v], w);
    }
    REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    REP(i, 1, n) 
    { 
        int x = 0;
        if ( i <= k ) x = 1 << i - 1;
        dp[i][x] = 0; vis[i][x] = true; 
        Q.push(pii(i, x)); 
    }
    while ( !Q.empty() ) 
    {
        pii x = Q.front(); Q.pop();
        REP(i, 0, (1 << k) - 1)
        {
            if ( (i | x.second) != i ) continue ;
            if ( dp[x.first][x.second] + dp[x.first][i - x.second] < dp[x.first][i] ) 
            {
                dp[x.first][i] = dp[x.first][x.second] + dp[x.first][i - x.second];
                if ( !vis[x.first][i] ) { vis[x.first][i] = true; Q.push(pii(x.first, i)); }
            }
        }
        REP(i, 1, n)
            if ( dp[x.first][x.second] + f[i][x.first] < dp[i][x.second] ) 
            {
                dp[i][x.second] = dp[x.first][x.second] + f[i][x.first];
                if ( !vis[i][x.second] ) { vis[i][x.second] = true; Q.push(pii(i, x.second)); }
            }
        vis[x.x][x.y] = false;
    }
    REP(i, 1, n) REP(j, 0, (1 << k) - 1) g[j] = min(g[j], dp[i][j]);
    REP(i, 0, (1 << k) - 1) 
    {
        if ( !Check(i) ) continue ;
        REP(j, 0, (1 << k) - 1) 
        {
            if ( !Check(j) || (i | j) != i ) continue ;
            g[i] = min(g[i], g[j] + g[i - j]);
        }
    }
    printf("%d\n", g[(1 << k) - 1]);
    return 0;
}
