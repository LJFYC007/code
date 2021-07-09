/***************************************************************
	File name: world.cpp
	Author: ljfcnyali
	Create time: 2020年10月29日 星期四 19时30分56秒
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
const int inv2 = (Mod + 1) / 2;
const int N = 1e5;

int n, K, fac[maxn], inv[maxn], ss[26][26], F[2][26], G[2][26], t[maxn];
int a[maxn], prime[maxn], tot, phi[maxn], ans, f[26], g[26], p[26], h[26];
bool vis[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
    freopen("world.in", "r", stdin);
    freopen("world.out", "w", stdout);
    n = 25;
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    ss[0][0] = 1;
    REP(i, 1, n) REP(j, 1, i) ss[i][j] = (ss[i - 1][j - 1] + ss[i - 1][j] * j) % Mod;

    phi[1] = 1;
    REP(i, 2, N)
    {
        if ( !vis[i] ) { prime[++ tot] = i; phi[i] = i - 1; }
        for ( int j = 1; j <= tot && i * prime[j] <= N; ++ j ) 
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { phi[i * prime[j]] = phi[i] * prime[j]; break ; }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }

    scanf("%lld%lld", &n, &K);
    REP(i, 1, n) { int x, y; scanf("%lld%lld", &x, &y); a[x] = y; t[x] = power(2, y); }

    REP(d, 1, N)
    {
        F[0][0] = 1; G[0][0] = -1; REP(i, 1, K) F[0][i] = G[0][i] = 0;
        int op = 0;
        REP(i, 1, N / d)
        {
            const int b = i * d, c = a[i * d];
            if ( !c ) continue ;
            op ^= 1; p[0] = 1; h[0] = t[b];
            REP(j, 1, K + 1) { p[j] = p[j - 1] * b % Mod; h[j] = h[j - 1] * inv2 % Mod; }
            REP(j, 0, K) 
            {
                int sum = 1, ret = power(2, c); f[j] = g[j] = 0;
                REP(s, 0, min(c, j + 1))
                {
                    int val = h[s] * sum % Mod;
                    f[j] += val * ss[j][s]; g[j] += val * ss[j + 1][s];
                    sum = sum * (c - s) % Mod;
                }
                f[j] %= Mod; g[j] %= Mod;
            }
            REP(j, 0, K)
            {
                F[op][j] = G[op][j] = 0;
                REP(k, 0, j)
                {
                    int ret = C(j, k) * p[j - k] % Mod;
                    F[op][j] += (f[j - k] * ret % Mod) * F[op ^ 1][k] % Mod;
                    G[op][j] += (f[j - k] * ret % Mod) * G[op ^ 1][k] % Mod;
                    G[op][j] += (g[j - k] * ret % Mod) * F[op ^ 1][k] % Mod;
                }
                F[op][j] %= Mod; G[op][j] %= Mod;
            }
        }
        ans = (ans + phi[d] * G[op][K]) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
