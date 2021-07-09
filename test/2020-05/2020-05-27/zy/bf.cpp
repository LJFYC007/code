/***************************************************************
	File name: zy.cpp
	Author: ljfcnyali
	Create time: 2020年05月27日 星期三 20时39分50秒
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
const int Mod = 1004535809;

int n, f[maxn][maxn][maxn], a[maxn], fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
    freopen("zy.in", "r", stdin);
    freopen("zy.out", "w", stdout);
    scanf("%lld", &n);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 1, n) scanf("%lld", &a[i]);
    f[0][0][0] = 1;
    REP(i, 1, n) REP(j, 0, i) REP(k, 0, j) 
    {
        f[i][j][k] = f[i - 1][j][k];
        if ( j && k ) f[i][j][k] = (f[i][j][k] + f[i - 1][j - 1][k - 1]) % Mod;
        REP(o, 1, a[i]) 
            if ( j && k + o - 1 >= 0 ) 
                f[i][j][k] = (f[i][j][k] + f[i - 1][j - 1][k + o - 1] * C(j - 1, o)) % Mod;
    }
    REP(i, 1, n) printf("%lld ", f[n][i][1]); puts("");
    return 0;
}
