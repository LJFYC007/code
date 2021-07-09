/***************************************************************
	File name: HDU6064.cpp
	Author: ljfcnyali
	Create time: 2020年05月29日 星期五 20时52分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 510;
const int maxm = 1e6 + 10;
const int Mod = 998244353;

int n, a[maxn][maxn], d1[maxn], d2[maxn], fac[maxm], inv[maxm];
// d1 : in ; d2 : out

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Get()
{
    int ans = 1;
    // REP(i, 1, n) { REP(j, 1, n) printf("%lld ", a[i][j]); puts(""); }
    REP(i, 1, n - 1)
    {
        int pos = -1;
        REP(j, i, n - 1) if ( a[j][i] ) { pos = j; break ; }
        if ( pos == -1 ) return 0;
        if ( pos != i ) 
        {
            ans *= -1;
            REP(j, i, n - 1) swap(a[i][j], a[pos][j]);
        }
        REP(j, i + 1, n - 1)
        {
            int x = a[j][i] * power(a[i][i], Mod - 2) % Mod;
            REP(k, i + 1, n - 1) a[j][k] = (a[j][k] - a[i][k] * x) % Mod;
        }
    }
    REP(i, 1, n - 1) ans = ans * a[i][i] % Mod;
    return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T = 0;
    fac[0] = inv[0] = 1; REP(i, 1, maxm - 10) fac[i] = fac[i - 1] * i % Mod;
    REP(i, 1, maxm - 10) inv[i] = power(fac[i], Mod - 2);
    while ( ~scanf("%lld", &n) )
    {
        ++ T;
        REP(i, 1, n) d1[i] = d2[i] = 0;
        int ans = 1;
        REP(i, 1, n) REP(j, 1, n) 
        { 
            scanf("%lld", &a[i][j]); 
            ans = ans * inv[a[i][j]] % Mod;
            d2[i] += a[i][j]; d1[j] += a[i][j]; 
        }
        REP(i, 1, n) if ( d1[i] != d2[i] ) { printf("Case #%lld: %d\n", T, 0); goto Next; }
        REP(i, 1, n) REP(j, 1, n) a[i][j] = -a[i][j];
        REP(i, 1, n) a[i][i] += d1[i];

        swap(d1[1], d1[n]);
        REP(i, 1, n) swap(a[1][i], a[n][i]);
        REP(i, 1, n) swap(a[i][1], a[i][n]);

        ans = (ans * Get() % Mod) * d1[n] % Mod;
        REP(i, 1, n) ans = ans * fac[d1[i] - 1] % Mod;
        printf("Case #%lld: %lld\n", T, (ans + Mod) % Mod);
Next : ;
    }
    return 0;
}
