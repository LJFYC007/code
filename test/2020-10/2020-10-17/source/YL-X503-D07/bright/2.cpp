/***************************************************************
	File name: bright.cpp
	Author: ljfcnyali
	Create time: 2020年10月17日 星期六 09时17分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxm = 1010;
const int maxn = 510;
const int Mod = 1e9 + 7;

int n, m, x, fac[maxm], inv[maxm];
int f[maxn][maxn][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline int calc(int n) { return n < 0 ? 0 : C(n + n, n) * power(n + 1, Mod - 2) % Mod; }

signed main()
{
    freopen("bright.in", "r", stdin);
    freopen("bright.out", "w", stdout);
    n = maxm - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;  
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld%lld", &n, &m, &x);
    REP(i, 1, n) REP(x, 1, n) REP(pos, 1, n)
    {
        if ( pos > i || i < x ) continue ;
        if ( i == x ) { f[i][x][pos] = calc(pos - 1) * calc(i - pos) % Mod; continue ; }
        // if ( i < x ) { f[i][x][pos] = calc(i); continue ; } 
        REP(j, pos + 1, i)
            if ( x - i + j >= 1 )
                f[i][x][pos] = (f[i][x][pos] + f[j - 1][x - i + j][pos] * calc(i - j)) % Mod;
        // REP(j, 1, pos - 1)
            // f[i][x][pos] = (f[i][x][pos] + calc(j - 1) * f[i - j][x][pos - j]) % Mod;
        /*
        REP(j, 1, i - 1) 
            if ( i - j - 1 <= x - 1 )
                f[i][x] = (f[i][x] + f[j][x - i + j + 1] * calc(i - j - 1)) % Mod;
        */
    }
    REP(i, 5, 10) printf("%lld ", f[i][5][2]); puts("");
    REP(i, 1, m)
    {
        int pos; scanf("%lld", &pos);
        // int ret = calc(pos - 1) * f[n - pos + 1][x] % Mod;
        // if ( n - x >= pos - 1) ret = ret * C(n - x, pos - 1) % Mod;
        printf("%lld ", (f[n][x][pos] + Mod) % Mod);
    }
    puts("");
    return 0;
}
