/***************************************************************
	File name: CF1436F.cpp
	Author: ljfcnyali
	Create time: 2020年10月29日 星期四 16时34分46秒
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

int n, m, prime[maxn], tot, miu[maxn], a[maxn], b[maxn];
int fac[maxn], inv[maxn], A[maxn], ans;
bool vis[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10; 
    miu[1] = fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod; 
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 2, n)
    {
        if ( !vis[i] ) { miu[i] = -1; prime[++ tot] = i; }
        for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j ) 
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) break ;
            miu[i * prime[j]] = -miu[i];
        }
    }
    scanf("%lld", &m);
    REP(i, 1, m) scanf("%lld%lld", &a[i], &b[i]);
    REP(d, 1, 100000)
    {
        n = 0;
        REP(i, 1, m) if ( a[i] % d == 0 ) REP(j, 1, b[i]) A[++ n] = a[i];
        int sum = 0; REP(i, 1, n) sum = (sum + A[i]) % Mod;
        int val = 0; REP(i, 1, n) val = (val + A[i] * A[i]) % Mod;
        REP(i, 2, n)
        {
            int ret = ((i - 1) * sum * sum + (n - i) * val) % Mod;
            ret = ret * C(n - 2, i - 2) % Mod;
            ans = (ans + miu[d] * ret) % Mod;
        }
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
