/***************************************************************
	File name: math.cpp
	Author: ljfcnyali
	Create time: 2020年12月01日 星期二 10时00分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e7 + 10;
const int Mod = 998244353;

int n, m, prime[maxn], tot, miu[maxn], phi[maxn], f[maxn], ans, g[maxn], h[maxn];
bool vis[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);
    n = maxn - 10; miu[1] = phi[1] = 1;
    REP(i, 2, n)
    {
        if ( !vis[i] ) { prime[++ tot] = i; miu[i] = -1; phi[i] = i - 1; }
        for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j ) 
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { miu[i * prime[j]] = 0; phi[i * prime[j]] = phi[i] * prime[j]; break ; }
            miu[i * prime[j]] = - miu[i];
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
    scanf("%lld%lld", &n, &m); int N = min(n, m);

    REP(i, 1, N) f[i] = power(i, n + 1) * power(phi[i], Mod - 2) % Mod;
    REP(i, 1, max(n, m)) phi[i] = phi[i] * i % Mod;

    REP(i, 1, max(n, m)) g[i] = h[i] = phi[i]; 
    REP(i, 1, tot)
    {
        int p = prime[i];
        for ( int j = N / p; j >= 1; -- j ) f[j * p] = (f[j * p] - f[j]) % Mod;
        for ( int j = n / p; j >= 1; -- j ) g[j] = (g[j] + g[j * p]) % Mod;
        for ( int j = m / p; j >= 1; -- j ) h[j] = (h[j] + h[j * p]) % Mod;
    }

    REP(i, 1, N) ans = (ans + f[i] % Mod * g[i] % Mod * h[i]) % Mod;
    ans = (ans + f[1]) % Mod;
    ans = ans * (Mod + 1) / 2 % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
