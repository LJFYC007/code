/***************************************************************
	File name: dtree.cpp
	Author: ljfcnyali
	Create time: 2020年10月08日 星期四 10时42分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 8010;

int n, fac[maxn], inv[maxn], Mod, f[maxn][maxn], ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
    freopen("dtree.in", "r", stdin);
    freopen("dtree.out", "w", stdout);
    scanf("%lld%lld", &n, &Mod);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod; 
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 2, n) REP(j, 0, i - 1)
    {
        int x = j, y = i - 1 - j; 
        int ret = 0;
        REP(a, 1, x) REP(b, 1, y)
        {
            int num = b + x - a + 1;
            num = num * fac[x - 1] % Mod;
            num = num * fac[y - 1] % Mod;
            ret = (ret + num) % Mod;
        }
        REP(a, 1, x) ret = (ret + f[x][a] * fac[y]) % Mod;
        REP(a, 1, y) ret = (ret + f[y][a] * fac[x]) % Mod;
        ret = ret * C(x + y, x) % Mod;
        f[i][j + 1] = ret;
    }
    REP(i, 1, n) ans = (ans + f[n][i]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
