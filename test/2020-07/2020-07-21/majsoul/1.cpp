/***************************************************************
	File name: majsoul.cpp
	Author: ljfcnyali
	Create time: 2020年07月21日 星期二 09时08分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define inv(x) power(x, Mod - 2)
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

int n, m, k, f[maxn][5][5][31], g[maxn][5][5][31][2];
int fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline void add(int &x, int y) { x = (x + y) % Mod; }

signed main()
{
    freopen("majsoul.in", "r", stdin);
    freopen("majsoul.out", "w", stdout);
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld%lld", &m, &n, &k);

    f[0][0][0][0] = 1;
    REP(i, 1, m) REP(x, 0, 4) REP(y, 0, 4) REP(j, 0, k)
    {
        add(f[i][y][4][j], f[i - 1][x][y][j]);
        add(f[i][y][1][j + 1], f[i - 1][x][y][j] * 4 % Mod);
        if ( x && y ) 
        {
            int val1 = C(4, x - 1) * inv(C(4, x)) % Mod;
            int val2 = C(4, y - 1) * inv(C(4, y)) % Mod;
            add(f[i][y - 1][3][j + 1], (f[i - 1][x][y][j] * val1 % Mod) * (val2 * 4 % Mod) % Mod);
            add(f[i][y - 1][0][j + 2], (f[i - 1][x][y][j] * val1 % Mod) * val2 % Mod);
        }
        if ( x >= 2 && y >= 2 ) 
        {
            int val1 = C(4, x - 2) * inv(C(4, x)) % Mod;
            int val2 = C(4, y - 2) * inv(C(4, y)) % Mod;
            add(f[i][y - 2][2][j + 2], (f[i - 1][x][y][j] * val1 % Mod) * (val2 * C(4, 2) % Mod) % Mod);
        }
    }

    g[0][0][0][0][0] = 1;
    REP(i, 1, m) REP(x, 0, 4) REP(y, 0, 4) REP(j, 0, k) REP(o, 0, 1)
    {
        add(g[i][y][4][j][o], g[i - 1][x][y][j][o]);
        add(g[i][y][1][j + 1][o], g[i - 1][x][y][j][o] * 4 % Mod);
        if ( x && y ) 
        {
            int val1 = C(4, x - 1) * inv(C(4, x)) % Mod;
            int val2 = C(4, y - 1) * inv(C(4, y)) % Mod;
            add(g[i][y - 1][3][j + 1][o], (g[i - 1][x][y][j][o] * val1 % Mod) * (val2 * 4 % Mod) % Mod);
            add(g[i][y - 1][0][j + 2][o], (g[i - 1][x][y][j][o] * val1 % Mod) * val2 % Mod);
        }
        if ( x >= 2 && y >= 2 ) 
        {
            int val1 = C(4, x - 2) * inv(C(4, x)) % Mod;
            int val2 = C(4, y - 2) * inv(C(4, y)) % Mod;
            add(g[i][y - 2][2][j + 2][o], (g[i - 1][x][y][j][o] * val1 % Mod) * (val2 * C(4, 2) % Mod) % Mod);
        }

        if ( o == 0 ) 
        {
            add(g[i][y][2][j][1], g[i - 1][x][y][j][0] * C(4, 2) % Mod);
            if ( x && y ) 
            {
                int val1 = C(4, x - 1) * inv(C(4, x)) % Mod;
                int val2 = C(4, y - 1) * inv(C(4, y)) % Mod;
                add(g[i][y - 1][1][j + 1][1], (g[i - 1][x][y][j][0] * val1 % Mod) * (val2 * 4 % Mod) % Mod);
            }
            if ( x >= 2 && y >= 2 ) 
            {
                int val1 = C(4, x - 2) * inv(C(4, x)) % Mod;
                int val2 = C(4, y - 2) * inv(C(4, y)) % Mod;
                add(g[i][y - 2][0][j + 2][1], (g[i - 1][x][y][j][0] * val1 % Mod) * (val2 * C(4, 2) % Mod) % Mod);
            }
        }
    }

    int ans = 0;
    REP(x, 0, 4) REP(y, 0, 4) ans = (ans + g[m][x][y][k][1]) % Mod;
    // ans = ans * fac[3 * k + 2] % Mod;
    // ans = ans * fac[4 * n * m - 3 * k - 2] % Mod;
    // REP(i, 1, m) ans = ans * inv[4] % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

