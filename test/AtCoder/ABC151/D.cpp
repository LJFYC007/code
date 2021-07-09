/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2020年01月12日 星期日 20时12分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 30;

int n, m, a[maxn][maxn], dt[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}, ans, p[maxn][maxn];
bool vis[maxn][maxn];
char s[maxn];

inline void DFS(int x, int y)
{
    REP(i, 0, 3)
    {
        int u = dt[i][0] + x;
        int v = dt[i][1] + y;
        if ( a[u][v] && p[u][v] > p[x][y] + 1 && !vis[u][v] )
        {
            p[u][v] = p[x][y] + 1;
            vis[u][v] = true;
            DFS(u, v);
            vis[u][v] = false;
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) 
    {
        scanf("%s", s + 1);
        REP(j, 1, m) if ( s[j] == '.' ) a[i][j] = 1;
    }
    REP(i, 1, n) REP(j, 1, m) if ( a[i][j] ) 
    { 
        mem(vis); memset(p, 0x3f, sizeof(p));
        p[i][j] = 0; vis[i][j] = true;
        DFS(i, j);
        REP(k, 1, n) REP(o, 1, m) if ( p[k][o] != 0x3f3f3f3f ) ans = max(ans, p[k][o]);
    }
    printf("%d\n", ans);
    return 0;
}
