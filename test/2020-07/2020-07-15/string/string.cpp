/***************************************************************
	File name: string.cpp
	Author: ljfcnyali
	Create time: 2020年07月15日 星期三 11时35分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Max = 1e6;
const int Mod = 1e9 + 7;
const int inv2 = (Mod + 1) / 2;

int n, m, F[maxn], g[maxn], H[maxn], ans, miu[maxn], prime[maxn], tot;
int f[maxn], Miu[maxn];
bool vis[maxn];
map<int, int> Map, Map1, Map2, Map3;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int calc(int n)
{
    int x = (power(m, n + 1) - m) % Mod;
    return x * power(m - 1, Mod - 2) % Mod;
}

inline int Get(int n)
{
    int k = n; if ( n & 1 ) -- k;

	int ret1 = ((power(m, (k / 2) + 1) * (k - 1) % Mod) - 2 * calc(k / 2) + m) % Mod;
	ret1 = ret1 * power(m - 1, Mod - 2) % Mod;

	int ret2 = (k / 2) * power(m, (k / 2) + 1) % Mod;
	ret2 = (ret2 - calc(k / 2)) % Mod;
    int x = (((k / 2) * power(m, (k / 2) + 1) % Mod) - calc(k / 2)) % Mod;
    ret2 = (ret2 + 2 * x * power(m - 1, Mod - 2)) % Mod;

    ret1 = (ret1 + ret2) % Mod;
	if ( n > k ) ret1 = (ret1 + power(m, (n + 1) / 2) * n) % Mod;
	return ret1;
}

inline int Calc(int n) { return (n * (n + 1) / 2) % Mod; }

inline int Solve(int n)
{
    if ( n <= Max ) return Miu[n];
    if ( Map.count(n) ) return Map[n];
    int ret = 1;
    for ( int i = 2, j; i <= n; i = j + 1 )
    {
        j = n / (n / i);
        ret = (ret - Solve(n / i) * (j - i + 1)) % Mod;
    }
    Map[n] = ret; return ret;
}

inline int Solve1(int n)
{
    if ( n <= Max ) return F[n];
    if ( Map1.count(n) ) return Map1[n];
    int ret = Get(n);
    for ( int i = 2, j; i <= n; i = j + 1 )
    {
        j = n / (n / i);
        int sum = (Calc(j) - Calc(i - 1)) % Mod;
        ret = (ret - sum * Solve1(n / i)) % Mod;
    }
    Map1[n] = ret; return ret;
}

inline int Solve2(int n)
{
    if ( n <= Max ) return H[n];
    if ( Map2.count(n) ) return Map2[n];
    int ret = Solve1(n);
    for ( int i = 2, j; i <= n; i = j + 1 )
    {
        j = n / (n / i);
        int sum = (Solve(j) - Solve(i - 1)) % Mod;
        ret = (ret - sum * Solve2(n / i)) % Mod;
    }
    Map2[n] = ret; return ret;
}

inline int CALC(int n)
{
    int k = n / 2, ret = 0;
    ret = 2 * calc(k) % Mod;
    if ( k * 2 != n ) ret = (ret + power(m, k + 1)) % Mod;
    return ret;
}

inline int Solve3(int n)
{
    if ( n <= Max ) return f[n];
    if ( Map3.count(n) ) return Map3[n];
    int ret = CALC(n);
    for ( int i = 2, j; i <= n; i = j + 1 )
    {
        j = n / (n / i);
        ret = (ret - (j - i + 1) * Solve3(n / i)) % Mod;
    }
    Map3[n] = ret; return ret;
}

signed main()
{
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    scanf("%lld%lld", &n, &m);

    int N = min(n, Max); miu[1] = 1;
    REP(i, 2, N)
    {
        if ( !vis[i] ) { prime[++ tot] = i; miu[i] = -1; }
        for ( int j = 1; j <= tot && i * prime[j] <= N; ++ j )
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { miu[i * prime[j]] = 0; break ; }
            miu[i * prime[j]] = -miu[i];
        }
    }

    REP(i, 1, N)
        if ( i & 1 ) g[i] = power(m, (i + 1) / 2) * i % Mod;
        else g[i] = (power(m, i / 2) + power(m, i / 2 + 1)) * (i * inv2 % Mod) % Mod;
    REP(i, 1, N) for ( int j = i; j <= N; j += i ) F[j] = (F[j] + g[i] * (j / i) * miu[j / i]) % Mod;
    REP(i, 1, N) for ( int j = i; j <= N; j += i ) H[j] = (H[j] + F[i]) % Mod;
    REP(i, 1, N) Miu[i] = (Miu[i - 1] + miu[i]) % Mod;
    REP(i, 1, N) F[i] = (F[i] + F[i - 1]) % Mod;
    REP(i, 1, N) H[i] = (H[i] + H[i - 1]) % Mod;

    REP(i, 1, N) g[i] = power(m, (i + 1) / 2);
    REP(i, 1, N) for ( int j = i; j <= N; j += i ) f[j] = (f[j] + g[i] * miu[j / i]) % Mod;
    REP(i, 1, N) f[i] = (f[i] + f[i - 1]) % Mod;
    // N = maxn - 10;
    // REP(i, 1, N) for ( int j = i; j <= N; j += i ) f[j] = (f[j] + g[i] * miu[j / i]) % Mod;
    // REP(i, 1, N) f[i] = (f[i] + f[i - 1]) % Mod;

    ans = (Solve2(n) - Solve3(n)) % Mod;;

    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
