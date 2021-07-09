/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2020年12月02日 星期三 09时34分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define x first
#define y second
typedef long long LL;

const int maxn = 60;
const int INF = 1e18;

int n, k, c[maxn], f[maxn][maxn][maxn][4][2][4][2], t[maxn];
pii limit[maxn];

inline void chkmin(int &x, int y) { x = x < y ? x : y; }

inline int Get(int l, int r)
{
    int x = l ^ r;
    for ( int i = k; i >= 1; -- i ) if ( (x >> i) & 1 ) return i;
    return 1;
}

inline int getpos(int i, int f, int c)
{
    int x = c == 0 ? limit[i].x : limit[i].y;
    return (x >> f) & 1;
}

inline int Solve(int pos, int c1, int c2, int l, int r)
{
    if ( l + 1 == r ) return (l != 0 && r != n + 1 && c1 != c2) * c[pos];
    if ( l == 0 || r == n + 1 ) return 0;
    return (c1 != c2) * c[pos];
    /*
    int x = 0, y = (r - l) & 1, len = r - l - 1, sum = 0;
    sum = min(sum, len - 1 + (l != 0 && x != c1) + (r != n + 1 && y != c2));
    x ^= 1; y ^= 1;
    sum = min(sum, len - 1 + (l != 0 && x != c1) + (r != n + 1 && y != c2));
    return sum * c[pos];
    */
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n) scanf("%lld%lld", &limit[i].x, &limit[i].y); 
    REP(i, 1, k) scanf("%lld", &c[i]);
    REP(i, 0, n + 1)
    {
        limit[i].x = limit[i].x * 2; limit[i].y = limit[i].y * 2 + 1;
        t[i] = Get(limit[i].x, limit[i].y); 
    }
    REP(pos, 0, k) REP(i, 0, n + 1) REP(j, 0, n + 1) REP(x, 0, 3) REP(u, 0, 1) REP(y, 0, 3) REP(v, 0, 1) f[pos][i][j][x][u][y][v] = INF;
    REP(i, 0, n) REP(x, 0, 1) REP(y, 0, 1)
        f[k][i][i + 1][x][getpos(i, k, x)][y][getpos(i + 1, k, y)] = Solve(k, getpos(i, k, x), getpos(i + 1, k, y), i, i + 1);

    for ( int pos = k; pos >= 0; -- pos ) REP(len, 2, n + 2) REP(i, 0, n - len + 2)
    {
        int j = i + len - 1;
        REP(x, 0, 3) REP(u, 0, 1) REP(y, 0, 3) REP(v, 0, 1)
        {
            REP(k, i + 1, j - 1) REP(s, 2, 3) REP(o, 0, 1) 
                chkmin(f[pos][i][j][x][u][y][v], f[pos][i][k][x][u][s][o] + f[pos][k][j][s][o][y][v]);
            // if ( f[pos][i][j][x][u][y][v] != INF )
                // cout << pos << " " << i << " " << j << " " << x << " " << u << " " << y << " " << v << " " << f[pos][i][j][x][u][y][v] << endl;
            if ( pos == 0 || x >= 2 || y >= 2 ) continue ;
            int l = getpos(i, pos - 1, x), r = getpos(j, pos - 1, y);
            // if ( pos == 3 && i == 2 && j == 4 && x == 1 && y == 0 ) 
                // cerr << l << " " << r << " " << Solve(pos - 1, l, r, i, j) << endl;
            chkmin(f[pos - 1][i][j][x][l][y][r], f[pos][i][j][x][u][y][v] + Solve(pos - 1, l, r, i, j));
            if ( pos <= t[j] && r == y ) chkmin(f[pos - 1][i][j][x][l][2 + y][r ^ 1], f[pos][i][j][x][u][y][v] + Solve(pos - 1, l, r ^ 1, i, j));
            if ( pos <= t[i] && l == x ) chkmin(f[pos - 1][i][j][2 + x][l ^ 1][y][r], f[pos][i][j][x][u][y][v] + Solve(pos - 1, l ^ 1, r, i, j));
            if ( pos <= min(t[i], t[j]) && l == x && r == y ) 
                chkmin(f[pos - 1][i][j][2 + x][l ^ 1][2 + y][r ^ 1], f[pos][i][j][x][u][y][v] + Solve(pos - 1, l ^ 1, r ^ 1, i, j));
        }
    }

    int ans = INF;
    REP(x, 0, 1) REP(u, 0, 1) REP(y, 0, 1) REP(v, 0, 1) ans = min(ans, f[0][0][n + 1][x][u][y][v]);
    printf("%lld\n", ans);
    return 0;
}
