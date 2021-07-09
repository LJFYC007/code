#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;
 
const int maxn = 1010;
 
int f[maxn][maxn][3], n, k, Mod, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &k, &Mod);
    if ( k > log2(n) + 1 ) { puts("0"); return 0; }
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    f[0][0][1] = f[0][0][2] = 1;
    REP(i, 1, n) REP(j, 1, min(i, k)) REP(len1, 0, i - 1)
    {
        int len2 = i - 1 - len1, x = 0;
        REP(t1, 0, j - 1) REP(t2, 0, j) if ( max(t1 + 1, t2) == j ) x = (x + f[len1][t1][2] * f[len2][t2][1]) % Mod;
        // REP(t1, 0, j - 1) x = (x + f[len1][t1][2] * f[len2][j][1]) % Mod;
        // REP(t2, 0, j - 1) x = (x + f[len1][j - 1][2] * f[len2][t2][1]) % Mod;
        f[i][j][1] = (f[i][j][1] + x * C(i - 1, len1)) % Mod;

        x = 0;
        REP(t1, 0, j) REP(t2, 0, j) if ( (t1 != t2 && max(t1, t2) == j) || (t1 == t2 && t1 == j - 1) ) 
            x = (x + f[len1][t1][2] * f[len2][t2][2]) % Mod;
        // REP(t1, 0, j - 1) x = (x + f[len1][t1][2] * f[len2][j][2]) % Mod;
        // x = (x + f[len1][j - 1][2] * f[len2][j - 1][2]) % Mod;
        // if ( i == 2 && j == 1 ) cerr << len1 + 1 << " " << x * C(i - 1, len1) << endl;
        f[i][j][2] = (f[i][j][2] + x * C(i - 1, len1)) % Mod;
    }
    // REP(i, 1, n) REP(j, 1, i) printf("%lld %lld %lld\n", i, j, f[i][j][1]);
    // REP(i, 1, n) REP(j, 1, i) printf("%lld %lld %lld\n", i, j, f[i][j][2]);
    int ans = 0;
    REP(len1, 0, n - 1)
    {
        int len2 = n - 1 - len1, ret = 0;
        REP(t1, 0, k) REP(t2, 0, k) if ( max(t1, t2) == k ) ret = (ret + f[len1][t1][1] * f[len2][t2][1]) % Mod;
        // REP(t1, 0, k) ret = (ret + f[len1][t1][1] * f[len2][k][1]) % Mod;
        ans = (ans + ret * C(n - 1, len1)) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}

/*
f[2][1][2]
inf 1 2 inf : 1
inf 2 1 inf : 1

f[3][2][1]
inf 3 2 1 : 1
inf 3 1 2 : 2
inf 2 1 3 : 2
inf 1 2 3 : 2
inf 2 3 1 : 2
inf 1 3 2 : 2
*/
