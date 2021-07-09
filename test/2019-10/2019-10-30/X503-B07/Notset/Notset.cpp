/***************************************************************
	File name: Notset.cpp
	Author: ljfcnyali
	Create time: 2019年10月30日 星期三 10时01分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e7 + 10;
const int N = 2e7;
const int Mod = 998244353;

int opt, x[7], y[7], inv[maxn], p[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; b >>= 1; a = a * a % Mod; } return r; }

inline int Solve(int n, int m) { return ((p[n + m] * inv[n] % Mod) * inv[m]) % Mod; }

namespace Subtask1 
{
    inline int main()
    {
        int ans = 0;
        for ( int i = x[3], j = y[4]; x[1] <= i && j <= y[5]; -- i, ++ j ) 
        {
            if ( i == x[3] ) continue ;
            ans = (ans + Solve(i - x[1], j - y[1]) * Solve(x[5] - i, y[5] - j)) % Mod;
        }
        for ( int i = x[4], j = y[3]; y[1] <= j && i <= x[5]; ++ i, -- j )
        {
            if ( i == x[4] ) continue ;
            ans = (ans + Solve(i - x[1], j - y[1]) * Solve(x[5] - i, y[5] - j)) % Mod;
        }
        printf("%lld\n", ans);
        return 0;
    }
}

namespace Subtask2
{
    int f[50] = {1,295201906,160030060,957629942,545208507,213689172,760025067,939830261,506268060,39806322,808258749,440133909,686156489,741797144,390377694,12629586,544711799,104121967,495867250,421290700,117153405,57084755,202713771,675932866,79781699,956276337,652678397,35212756,655645460,468129309,761699708,533047427,287671032,206068022,50865043,144980423,111276893,259415897,444094191,593907889,573994984,892454686,566073550,128761001,888483202,251718753};

    inline int Get(int x)
    {
        int ret = f[(x - 1) / N];
        REP(i, (x - 1) / N * N + 1, x) ret = ret * i % Mod;
        return ret;
    }

    inline int calc(int n, int m) { return ((Get(n + m) * power(Get(n), Mod - 2) % Mod) * power(Get(m), Mod - 2)) % Mod; }

    inline int main()
    {
        int ans = calc(x[3] - x[1], y[3] - y[1]) * calc(x[5] - x[3], y[5] - y[3]) % Mod; 
        ans = (calc(x[5] - x[1], y[5] - y[1]) - ans + Mod) % Mod;
        printf("%lld\n", ans);
        return 0;
    }
}

signed main()
{
    freopen("Notset.in", "r", stdin);
    freopen("Notset.out", "w", stdout);
    scanf("%lld", &opt);
    REP(i, 1, 6) scanf("%lld", &x[i]);    
    REP(i, 1, 6) scanf("%lld", &y[i]);    
    p[0] = inv[0] = 1; REP(i, 1, N) p[i] = p[i - 1] * i % Mod;
    inv[N] = power(p[N], Mod - 2); for ( int i = N - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    if ( opt <= 3 ) return Subtask1 :: main();
    if ( opt == 7 ) return Subtask2 :: main();
    return 0;
}
