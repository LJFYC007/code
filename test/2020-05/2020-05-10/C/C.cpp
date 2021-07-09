/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年05月10日 星期日 09时13分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e2 + 10;
const int Mod = 1e9 + 7;

int a, b, c, f[4][maxn][maxn][maxn];
int fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    int N = 100;
    fac[0] = inv[0] = 1; REP(i, 1, N) fac[i] = fac[i - 1] * i % Mod;
    inv[N] = power(fac[N], Mod - 2); for ( int i = N - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    while ( ~scanf("%lld%lld%lld", &a, &b, &c) ) 
    {
        mem(f);          
        f[2][0][0][0] = 1;
        REP(i, 0, a) REP(j, 0, b) REP(k, 0, c) 
        {
            f[1][i + 1][j][k] = (f[1][i + 1][j][k] + f[2][i][j][k] * (a - i)) % Mod;
            f[1][i][j][k + 1] = (f[1][i][j][k + 1] + f[3][i][j][k] * (c - k)) % Mod;

            f[2][i + 1][j][k] = (f[2][i + 1][j][k] + f[1][i][j][k] * (a - i)) % Mod;
            f[2][i][j + 1][k] = (f[2][i][j + 1][k] + f[3][i][j][k] * (b - j)) % Mod;

            f[3][i][j + 1][k] = (f[3][i][j + 1][k] + f[2][i][j][k] * (b - j)) % Mod;
            f[3][i][j][k + 1] = (f[3][i][j][k + 1] + f[1][i][j][k] * (c - k)) % Mod;
        }
        printf("%lld\n", (f[2][a][b][c] + Mod) % Mod);
        // REP(i, 0, a) REP(j, 0, b) REP(k, 0, c) REP(o, 1, 3)
            // printf("%c %lld %lld %lld %lld\n", o == 1 ? 'A' : (o == 2 ? 'B' : 'C'), i, j, k, f[o][i][j][k]);
        // int ans = -1;
        // REP(i, 0, a) REP(j, 0, b) REP(k, 0, c) ans = (ans + f[2][i][j][k]) % Mod;
        // printf("%lld\n", (ans + Mod) % Mod);
    }

    return 0;
}
