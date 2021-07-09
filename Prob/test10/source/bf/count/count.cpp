/***************************************************************
	File name: 1.cpp
	Author: ljfcnyali
	Create time: 2020年09月22日 星期二 20时28分53秒
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
const int Mod = 998244353;

int f[maxn][maxn][maxn], fac[maxn], inv[maxn], n, k, g[maxn], h[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    n = 100;
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;

    h[1] = 1; REP(i, 1, n) g[i] = power(2, C(i, 2)) * inv[i] % Mod;
    REP(i, 2, n - 1)
    {
        int ret = g[i] * i % Mod;
        REP(j, 1, i - 1) ret = (ret - (g[j] * h[i - j] % Mod) * (i - j)) % Mod;
        h[i] = ret * power(i, Mod - 2) % Mod;
    }
    REP(i, 1, n) h[i] = h[i] * fac[i] % Mod;

    scanf("%lld%lld", &n, &k);
    f[1][0][0] = 1;  
    REP(i, 2, n) REP(j, 1, k) REP(o, 1, k) REP(a, 1, i) REP(b, 1, min(a, j))
    {
        int ret = h[a] * inv[b] % Mod;
        ret = ret * inv[a - b] % Mod;
        ret = ret * f[i - a][j - b][o - 1] % Mod;
        f[i][j][o] = (f[i][j][o] + ret) % Mod;
    }
    int ans = 0;
    REP(j, 1, k) REP(i, 1, k) ans = (ans + (f[n][j][i] * inv[i] % Mod) * fac[n - 1]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
