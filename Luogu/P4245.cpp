/***************************************************************
	File name: P4245.cpp
	Author: ljfcnyali
	Create time: 2019年12月16日 星期一 15时01分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long 
typedef long long LL;

const int maxn = 8e5 + 10;

int r[maxn];

inline int mul(int a, int b, int Mod) { int r = 0; while ( b ) { if ( b & 1 ) r = (r + a) % Mod; a = (a + a) % Mod; b >>= 1; } return (r + Mod) % Mod; }

inline int power(int a, int b, int Mod) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(int f[], int n, int Mod, int inv)
{
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1), Mod);
        if ( inv == -1 ) tmp = power(tmp, Mod - 2, Mod);
        for ( int i = 0; i < n; i += (Mid << 1) )
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod )
            {
                int x = f[i + j], y = f[i + j + Mid] * sum % Mod;
                f[i + j] = (x + y) % Mod; f[i + j + Mid] = (x - y) % Mod;
            }
        }
    }
    if ( inv == -1 ) { inv = power(n, Mod - 2, Mod); REP(i, 0, n - 1) f[i] = f[i] * inv % Mod; }
}

int n, m, p, f[3][maxn], g[3][maxn], Mod[3];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &p); ++ n; ++ m; 
    REP(i, 0, n - 1) { scanf("%lld", &f[0][i]); f[1][i] = f[2][i] = f[0][i]; }
    REP(i, 0, m - 1) { scanf("%lld", &g[0][i]); g[1][i] = g[2][i] = g[0][i]; }
    Mod[0] = 469762049; Mod[1] = 998244353; Mod[2] = 1004535809;
    n += m; m = 1; while ( m < (n << 1) ) m <<= 1;
    REP(i, 0, m - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? m >> 1 : 0);
    REP(i, 0, 2) 
    { 
        NTT(f[i], m, Mod[i], 1); NTT(g[i], m, Mod[i], 1); 
        REP(j, 0, m - 1) f[i][j] = f[i][j] * g[i][j] % Mod[i];
        NTT(f[i], m, Mod[i], -1);
    }
    int p0 = power(Mod[0], Mod[1] - 2, Mod[1]), p1 = power(Mod[0], Mod[2] - 2, Mod[2]) * power(Mod[1], Mod[2] - 2, Mod[2]) % Mod[2];
    REP(i, 0, n - 2)
    {
        int k0 = (f[1][i] - f[0][i]) * p0 % Mod[1];
        int x = f[0][i] + k0 * Mod[0];
        int k3 = mul((f[2][i] - x), p1, Mod[2]);
        x = (x + (k3 * Mod[0] % p) * Mod[1]) % p;
        printf("%lld ", (x + p) % p);
    }
    puts("");
    return 0;
}
