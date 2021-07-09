/***************************************************************
	File name: lover.cpp
	Author: ljfcnyali
	Create time: 2020年10月24日 星期六 08时28分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int Mod = 998244353;
const int INF = 1e18;

int ans, n, k, f[18][61][39][27][23], l[5], num[10][5];
int len, h[20], g[61][39][27][23], p[5][70];
struct node 
{ 
    int x, a, b, c, d, op, pre; 
    node ( int g1 = 0, int g2 = 0, int g3 = 0, int g4 = 0, int g5 = 0, int g6 = 0, int g7 = 0 ) 
    {
        x = g1; a = g2; b = g3; c = g4; d = g5; op = g6; pre = g7;
    }
} ;
queue<node> Q;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline bool Check(int a, int b, int c, int d) 
{
    int x = k;
    if ( p[1][a] > x ) return true; x /= p[1][a];
    if ( p[2][b] > x ) return true; x /= p[2][b];
    if ( p[3][c] > x ) return true; x /= p[3][c];
    if ( p[4][d] > x ) return true; x /= p[4][d];
    return false;
}

inline void add(int &x, int y) { x = (x + y) % Mod; }

signed main()
{
    freopen("lover.in", "r", stdin);
    freopen("lover.out", "w", stdout);
    l[1] = 60; l[2] = 38; l[3] = 26; l[4] = 22;
    p[1][0] = 1; REP(i, 1, l[1]) p[1][i] = p[1][i - 1] * 2;
    p[2][0] = 1; REP(i, 1, l[2]) p[2][i] = p[2][i - 1] * 3;
    p[3][0] = 1; REP(i, 1, l[3]) p[3][i] = p[3][i - 1] * 5;
    p[4][0] = 1; REP(i, 1, l[4]) p[4][i] = p[4][i - 1] * 7;

    scanf("%lld%lld", &n, &k); 
    while ( n ) { h[len ++] = n % 10; n /= 10; }
    reverse(h, h + len);
    num[2][1] = 1; num[3][2] = 1; num[4][1] = 2; num[5][3] = 1;
    num[6][1] = num[6][2] = 1; num[7][4] = 1; num[8][1] = 3; num[9][2] = 2;

    Q.push(node(0, 0, 0, 0, 0, 1, 1));
    while ( !Q.empty() ) 
    {
        node u = Q.front(); Q.pop();
        if ( u.x == len ) 
        {
            if ( u.op == 1 ) ++ f[u.x][u.a][u.b][u.c][u.d];
            continue ;
        }
        int ret = u.op ? 1 : f[u.x][u.a][u.b][u.c][u.d];
        int st = u.op ? h[u.x] : 9;
        if ( u.pre == 1 && u.x + 1 < len ) 
        {
            ++ f[u.x + 1][u.a][u.b][u.c][u.d];
            Q.push(node(u.x + 1, u.a, u.b, u.c, u.d, 0, 1));
        }
        REP(i, 1, st)
        {
            if ( u.op && i == st ) 
            {
                Q.push(node(u.x + 1, num[i][1] + u.a, num[i][2] + u.b, num[i][3] + u.c, num[i][4] + u.d, 1));
                continue ;
            }
            if ( !f[u.x + 1][num[i][1] + u.a][num[i][2] + u.b][num[i][3] + u.c][num[i][4] + u.d] )
                Q.push(node(u.x + 1, num[i][1] + u.a, num[i][2] + u.b, num[i][3] + u.c, num[i][4] + u.d, 0));
            add(f[u.x + 1][num[i][1] + u.a][num[i][2] + u.b][num[i][3] + u.c][num[i][4] + u.d], ret);
        }
    }


    REP(a, 0, l[1]) REP(b, 0, l[2]) REP(c, 0, l[3]) REP(d, 0, l[4])
        g[a][b][c][d] = f[len][a][b][c][d];

    /*
    REP(a, 0, l[1]) REP(b, 0, l[2]) REP(c, 0, l[3]) for ( int d = l[4] - 1; d >= 0; -- d )
        add(g[a][b][c][d], g[a][b][c][d + 1]);
    REP(a, 0, l[1]) REP(b, 0, l[2]) for ( int c = l[3] - 1; c >= 0; -- c ) REP(d, 0, l[4])
        add(g[a][b][c][d], g[a][b][c + 1][d]);
    REP(a, 0, l[1]) for ( int b = l[2] - 1; b >= 0; -- b ) REP(c, 0, l[3]) REP(d, 0, l[4])
        add(g[a][b][c][d], g[a][b + 1][c][d]);
    for ( int a = l[1] - 1; a >= 0; -- a ) REP(b, 0, l[2]) REP(c, 0, l[3]) REP(d, 0, l[4])
        add(g[a][b][c][d], g[a + 1][b][c][d]);
    */

    REP(a, 0, l[1]) REP(b, 0, l[2]) REP(c, 0, l[3]) REP(d, 0, l[4])
    {
        if ( !g[a][b][c][d] ) continue ;
        REP(x, 0, l[1]) REP(y, 0, l[2]) REP(z, 0, l[3]) REP(o, 0, l[4])
        {
            if ( !g[x][y][z][o] ) continue ;
            if ( Check(min(a, x), min(b, y), min(c, z), min(d, o)) ) continue ;
            add(ans, g[a][b][c][d] * g[x][y][z][o] % Mod);
        }
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
