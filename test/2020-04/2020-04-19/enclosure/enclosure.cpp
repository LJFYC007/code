/***************************************************************
	File name: enclosure.cpp
	Author: ljfcnyali
	Create time: 2020年04月19日 星期日 15时38分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 60;
const int maxm = 2010;

int n, m, f[maxn][maxn][maxm], g[maxn][maxn], p[maxn][maxn], N, ans[maxn];
int dt[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool vis[maxn][maxn][maxm];
char s[maxn][maxn];
struct node 
{ 
    int x, y, sta; 
    node(int A = 0, int B = 0, int C = 0) { x = A; y = B; sta = C; } 
} p1, p2;
queue<node> Q;

int main()
{
    freopen("enclosure.in", "r", stdin);
    freopen("enclosure.out", "w", stdout);
    scanf("%s", s[1] + 1); m = str(s[1] + 1); n = 1;
    while ( ~scanf("%s", s[n + 1] + 1) ) ++ n;
    REP(i, 1, n) REP(j, 1, m) if ( s[i][j] == 'I' ) p[i][j] = ++ N;
    int num = N;
    REP(i, 1, n) REP(j, 1, m) if ( s[i][j] == 'X' ) p[i][j] = ++ N;
    REP(i, 0, n - 1) REP(j, 0, m - 1) REP(k, i + 1, n) if ( p[k][j + 1] ) g[i][j] |= 1 << p[k][j + 1] - 1;
    memset(f, 0x3f, sizeof(f));
    memset(ans, 0x3f, sizeof(ans));
    vis[0][0][0] = true; Q.push(node(0, 0, 0)); f[0][0][0] = 0;
    while ( !Q.empty() ) 
    {
        p1 = Q.front(); Q.pop();
        REP(i, 0, 3)
        {
            p2 = node(p1.x + dt[i][0], p1.y + dt[i][1], p1.sta);
            if ( p2.x < 0 || p2.y < 0 || p2.x > n || p2.y > m ) continue ;
            if ( i == 0 ) p2.sta ^= g[p2.x][p2.y - 1];
            if ( i == 2 ) p2.sta ^= g[p2.x][p2.y];
            if ( f[p2.x][p2.y][p2.sta] > f[p1.x][p1.y][p1.sta] + 1 ) 
            {
                f[p2.x][p2.y][p2.sta] = f[p1.x][p1.y][p1.sta] + 1;
                if ( !vis[p2.x][p2.y][p2.sta] ) 
                {
                    vis[p2.x][p2.y][p2.sta] = true;
                    Q.push(p2);
                }
            }
        }
        vis[p1.x][p1.y][p1.sta] = false;
    }
    REP(i, 1, (1 << num) - 1)
    {
        int ret = 0;
        REP(j, 0, num - 1) if ( (i >> j) & 1 ) ++ ret;
        ans[ret] = min(ans[ret], f[0][0][i]);
    }
    REP(i, 1, num) printf("%d\n", ans[i]);
    return 0;
}
