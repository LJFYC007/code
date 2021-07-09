/***************************************************************
	File name: ARC093F.cpp
	Author: ljfcnyali
	Create time: 2020年07月25日 星期六 11时47分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1 << 16;
const int Mod = 1e9 + 7;

int n, m, a[maxn], f[17][maxn], fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline int sgn(int n) { return n & 1 ? -1 : 1; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 1; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) scanf("%lld", &a[i]);
    reverse(a + 1, a + m + 1);
    f[0][0] = 1;
    REP(i, 1, m) REP(j, 0, (1 << n) - 1) 
    {
        f[i][j] = (f[i][j] + f[i - 1][j]) % Mod;
        int sum = 0; 
        REP(k, 1, n) if ( (j >> k - 1) & 1 ) sum += 1 << k - 1;
        REP(k, 1, n)
        {
            if ( (j >> k - 1) & 1 ) continue ;
            int s = j | (1 << k - 1);
            int num = (1 << n) - a[i];
            if ( num >= sum ) f[i][s] = (f[i][s] + (f[i - 1][j] * C(num - sum, (1 << k - 1) - 1) % Mod) * fac[1 << k - 1]) % Mod;
        }
    }
    int ans = 0;
    REP(j, 0, (1 << n) - 1)
    {
        int num = 0, sum = 0; 
        REP(i, 1, n) if ( (j >> i - 1) & 1 ) { ++ sum; num += 1 << i - 1; }
        ans = (ans + sgn(sum) * fac[(1 << n) - 1 - num] * f[m][j]) % Mod;
    }
    ans = ans * (1 << n) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
