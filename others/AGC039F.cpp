/***************************************************************
	File name: AGC039F.cpp
	Author: ljfcnyali
	Create time: 2021年01月26日 星期二 10时00分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 110;

int N, M, K, Mod, f[maxn][maxn][maxn][2], fac[maxn], inv[maxn], g[maxn][maxn][maxn][2];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int sgn(int x) { return x & 1 ? - 1 : 1; } 
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld%lld", &N, &M, &K, &Mod);
    if ( N < M ) swap(N, M); fac[0] = inv[0] = 1; REP(i, 1, N) fac[i] = fac[i - 1] * i % Mod;
    inv[N] = power(fac[N], Mod - 2); for ( int i = N - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(k, 0, K - 1) REP(j, 0, M)
    {
        int x = (power(k + 1, M - j) - power(k, M - j)) * power(K - k, j) % Mod;
        g[k][j][0][0] = 1;
        REP(i, 1, N) g[k][j][i][0] = g[k][j][i - 1][0] * x % Mod;
    }
    REP(k, 0, K - 1) REP(j, 0, N)
    {
        int x = (power(K - k, j) - power(K - k - 1, j)) * power(k + 1, N - j) % Mod;
        g[k][j][0][1] = 1;
        REP(i, 1, M) g[k][j][i][1] = g[k][j][i - 1][1] * x % Mod;
    }

    f[0][0][0][0] = 1;
    REP(k, 0, K - 1) REP(i, 0, N) REP(j, 0, M) 
    {
        REP(x, 0, N - i) f[i + x][j][k][1] = (f[i + x][j][k][1] + f[i][j][k][0] * C(N - i, x) % Mod * g[k][j][x][0]) % Mod;
        REP(y, 0, M - j) f[i][j + y][k + 1][0] = (f[i][j + y][k + 1][0] + f[i][j][k][1] * C(M - j, y) % Mod * g[k][i][y][1]) % Mod;
    }
    printf("%lld\n", (f[N][M][K][0] + Mod) % Mod);
    return 0;
}
