/***************************************************************
	File name: path.cpp
	Author: ljfcnyali
	Create time: 2019年11月09日 星期六 09时30分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 510;

int f[maxn][maxn], n, m, ans, s1, s2, t1, t2, Mid;
int dt[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
bool vis[maxn][maxn];

inline void DFS(int x, int y)
{
    vis[x][y] = true;
    REP(i, 0, 3)
    {
        int u = x + dt[i][0], v = y + dt[i][1];
        if ( vis[u][v] || f[u][v] < Mid || u < 1 || v < 1 || u > n || v > m ) continue ;
        DFS(u, v);
    }
}

inline bool Check()
{
    mem(vis); DFS(s1, s2);
    return vis[t1][t2];
}

int main()
{
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
    scanf("%d%d", &n, &m);
    memset(f, 0x3f, sizeof(f));
    REP(i, 1, n) REP(j, 1, m)
    {
        char c = getchar();
        while ( c != '+' && c != '.' && c != 'V' && c != 'J' ) c = getchar();
        if ( c == '+' ) f[i][j] = 0;
        if ( c == 'V' ) { s1 = i; s2 = j; }
        if ( c == 'J' ) { t1 = i; t2 = j; }
    }
    REP(i, 1, n) REP(j, 2, m) f[i][j] = min(f[i][j], f[i][j - 1] + 1); 
    REP(i, 1, n) for ( int j = m - 1; j >= 1; -- j ) f[i][j] = min(f[i][j], f[i][j + 1] + 1); 
    REP(i, 2, n) REP(j, 1, m) f[i][j] = min(f[i][j], f[i - 1][j] + 1);
    for ( int i = n - 1; i >= 1; -- i ) REP(j, 1, m) f[i][j] = min(f[i][j], f[i + 1][j] + 1);
    int L = 0, R = f[s1][s2], ans;
    while ( L <= R ) 
    {
        Mid = L + R >> 1;
        if ( Check() ) { ans = Mid; L = Mid + 1; }
        else R = Mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}
