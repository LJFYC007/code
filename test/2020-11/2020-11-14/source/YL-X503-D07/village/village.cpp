/***************************************************************
	File name: village.cpp
	Author: ljfcnyali
	Create time: 2020年11月14日 星期六 08时51分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 310;

int n, m, a[maxn][maxn], ans, sum[4][maxn][maxn], dt[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int tax[maxn * maxn * 10], c[maxn][maxn], Minx, Maxx, Miny, Maxy;
struct node 
{ 
    int x1, y1, x2, y2; 
    node ( int a = 0, int b = 0, int c = 0, int d = 0 ) { x1 = a; y1 = b; x2 = c; y2 = d; }
} ;
vector<node> p[maxn];
bool vis[maxn][maxn];

inline void DFS(int u, int v)
{
    if ( vis[u][v] ) return ; vis[u][v] = true;
    Minx = min(Minx, u); Maxx = max(Maxx, u); Miny = min(Miny, v); Maxy = max(Maxy, v);
    REP(i, 0, 3)
    {
        int x = u + dt[i][0], y = v + dt[i][1];
        if ( !a[x][y] && x >= 1 && x <= n && y >= 1 && y <= m ) DFS(x, y);
    }
}

int main()
{
    freopen("village.in", "r", stdin);
    freopen("village.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) REP(j, 1, m) scanf("%1d", &a[i][j]);
    REP(i, 1, n) REP(j, 1, m) 
    {
        if ( a[i][j] && a[i][j + 1] ) -- sum[1][i][j + 1];
        if ( a[i][j] && a[i + 1][j] ) -- sum[2][i + 1][j];
        if ( a[i][j] ) ++ sum[0][i][j];
        if ( a[i][j] && a[i + 1][j] && a[i][j + 1] && a[i + 1][j + 1] ) ++ sum[3][i + 1][j + 1];
    }
    REP(o, 0, 3) REP(i, 1, n) REP(j, 1, m) sum[o][i][j] += sum[o][i - 1][j] + sum[o][i][j - 1] - sum[o][i - 1][j - 1];

    REP(i, 1, n) REP(j, 1, m)
    {
        if ( a[i][j] || vis[i][j] ) continue ;
        Minx = Maxx = i; Miny = Maxy = j;
        DFS(i, j);
        if ( Minx > 1 && Miny > 1 && Maxx < n && Maxy < m ) 
        {
            REP(k, 1, Minx - 1) p[k].push_back(node(Minx - 1, Miny - 1, Maxx + 1, Maxy + 1));
        }
    }

    REP(i, 1, n) 
    {
        REP(j, 0, n) REP(k, 1, m) c[j][k] = m;
        for ( auto it : p[i] ) c[it.x2][it.y1] = min(c[it.x2][it.y1], it.y2 - 1);

        REP(j, i, n)
        {
            REP(x, 1, m) c[j][x] = min(c[j][x], c[j - 1][x]);
            int Min = m;
            for ( int k = m; k >= 1; -- k ) 
            {
                int x = k, val = sum[0][j][x] - sum[0][i - 1][x] + sum[1][j][x] - sum[1][i - 1][x];
                val += sum[2][j][x] - sum[2][i][x] + sum[3][j][x] - sum[3][i][x];
                ++ tax[val];
                while ( Min > c[j][k] ) 
                {
                    x = Min; val = sum[0][j][x] - sum[0][i - 1][x] + sum[1][j][x] - sum[1][i - 1][x];
                    val += sum[2][j][x] - sum[2][i][x] + sum[3][j][x] - sum[3][i][x];
                    -- tax[val]; -- Min;
                }
                x = k; val = sum[0][j][x - 1] - sum[0][i - 1][x - 1] + sum[1][j][x] - sum[1][i - 1][x];
                val += sum[2][j][x - 1] - sum[2][i][x - 1] + sum[3][j][x] - sum[3][i][x];
                ans += tax[val + 1];
            }
            while ( Min > 0 ) 
            {
                int x = Min, val = sum[0][j][x] - sum[0][i - 1][x] + sum[1][j][x] - sum[1][i - 1][x];
                val += sum[2][j][x] - sum[2][i][x] + sum[3][j][x] - sum[3][i][x];
                -- tax[val]; -- Min;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
