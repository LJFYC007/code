/***************************************************************
	File name: LibreOJ_6229.cpp
	Author: ljfcnyali
	Create time: 2020年06月14日 星期日 21时26分28秒
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
const int Mod = 1e9 + 7;

int inv8, inv6, miu[maxn], prime[maxn], tot, sum[maxn], n;
map<int, int> Map;
bool vis[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int calc(int n) { return (n * (n + 1) % Mod) * ((2 * n + 1) * inv6 % Mod) % Mod; }

inline int Get(int n) 
{ 
    int x = n * n % Mod;
    int sum1 = ((x * x + 2 * x * n + x) % Mod) * inv8 % Mod;
    int sum2 = calc(n) * (Mod + 1) / 2 % Mod;;
    return (sum1 + sum2) % Mod;
}

inline int Solve(int n)
{
    if ( n <= maxn - 10 ) return sum[n];
    if ( Map.count(n) ) return Map[n];
    int ret = n;
    for ( int i = 2, j = 0; i <= n; i = j + 1 ) 
    {
        j = n / (n / i);
        int sum = Solve(n / i) * (calc(j) - calc(i - 1)) % Mod;
        ret = (ret - sum) % Mod;
    }
    Map[n] = ret; return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    inv8 = power(8, Mod - 2); inv6 = power(6, Mod - 2);
    n = maxn - 10; miu[1] = 1;
    for ( int i = 2; i <= n; ++ i ) 
    {
        if ( !vis[i] ) { prime[++ tot] = i; miu[i] = -1; }
        for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j ) 
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { miu[i * prime[j]] = 0; break ; }
            miu[i * prime[j]] = -miu[i];
        }
    }
    REP(i, 1, n) for ( int j = i; j <= n; j += i ) sum[j] = (sum[j] + miu[i] * i * i) % Mod;
    REP(i, 1, n) sum[i] = (sum[i] + sum[i - 1]) % Mod;
    scanf("%lld", &n);
    int ans = 0;
    for ( int i = 1, j = 0; i <= n; i = j + 1 ) 
    {
        j = n / (n / i);
        int ret = Get(n / i);
        ans = (ans + ret * (Solve(j) - Solve(i - 1))) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
