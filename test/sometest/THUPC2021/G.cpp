/***************************************************************
	File name: G.cpp
	Author: ljfcnyali
	Create time: 2020年12月12日 星期六 12时53分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int f[13][1 << 12][1 << 12], a[13][13], n, k;
int A[1 << 12][1 << 12], B[1 << 12][1 << 12];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int get1(int x, int z)
{
    int ret = 1;
    REP(j, 1, n) if ( (z >> j - 1) & 1 ) REP(i, 1, n) if ( (x >> i - 1) & 1 ) ret = ret * (1 - a[i][j]) % Mod;
    return ret;
}

inline int get2(int y, int z)
{
    int ret = 1;
    REP(j, 1, n) if ( (z >> j - 1) & 1 )
    {
        int val = 1;
        REP(i, 1, n) if ( (y >> i - 1) & 1 ) val = val * (1 - a[i][j]) % Mod;
        ret = ret * (1 - val) % Mod;
    }
    return ret;
}

inline int calc(int x, int y, int z)
{
    /*
    int ret = 1;
    REP(j, 1, n) if ( (z >> j - 1) & 1 )
    {
        REP(i, 1, n) if ( (x >> i - 1) & 1 ) ret = ret * (1 - a[i][j]) % Mod;
        int val = 1;
        REP(i, 1, n) if ( (y >> i - 1) & 1 ) val = val * (1 - a[i][j]) % Mod;
        ret = ret * (1 - val) % Mod;
    }
    */
    int ret = A[x][z] * B[y][z] % Mod;
    return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n * (n - 1)) { int u, v, p, q; scanf("%lld%lld%lld%lld", &u, &v, &p, &q); a[u][v] = p * power(q, Mod - 2) % Mod; }

    REP(i, 1, (1 << n) - 1) for ( int j = i; j; j = (j - 1) & i )
    {
        int x = i - j, y = j;
        A[x][y] = get1(x, y); B[x][y] = get2(x, y);
    }

    REP(i, 1, (1 << n) - 1) if ( !(i & 1) ) f[1][1][i] = calc(0, 1, i);
    REP(i, 1, k - 1) REP(j, 1, (1 << n) - 1) for ( int k = j; k; k = (k - 1) & j )
    {
        int X = j - k, Y = k, s = (1 << n) - 1 - j;
        if ( !f[i][X][Y] ) continue ;
        for ( int Z = s; Z; Z = (Z - 1) & s )
            f[i + 1][X + Y][Z] = (f[i + 1][X + Y][Z] + calc(X, Y, Z) * f[i][X][Y]) % Mod;
    }
    int ans = 0;
    REP(j, 1, k) REP(i, 0, (1 << n) - 1) ans = (ans + f[j][i][(1 << n) - 1 - i]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
