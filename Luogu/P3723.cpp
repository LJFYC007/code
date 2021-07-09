/***************************************************************
	File name: P3723.cpp
	Author: ljfcnyali
	Create time: 2019年12月19日 星期四 08时56分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 998244353;
const int INF = 1e18;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(int f[], int n, int inv)
{
    static int r[maxn];
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2);
        for ( int i = 0; i < n; i += (Mid << 1) )
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod )
            {
                int x = f[i + j], y = sum * f[i + j + Mid] % Mod;
                f[i + j] = (x + y) % Mod; f[i + j + Mid] = (x - y) % Mod;
            }
        }
    }
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2);
        REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
    }
}

int n, m, a[maxn], b[maxn], ret, ans = INF, sum1, sum2; 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 0, n - 1) { scanf("%lld", &a[i]); a[i + n] = a[i]; sum1 += a[i] * a[i]; sum2 += a[i]; }
    REP(i, 0, n - 1) { scanf("%lld", &b[n - i - 1]); sum1 += b[n - i - 1] * b[n - i - 1]; sum2 -= b[n - i - 1]; }
    int len = 1, x = n * 3;
    while ( len <= x ) len <<= 1;
    NTT(a, len, 1); NTT(b, len, 1);
    REP(i, 0, len - 1) a[i] = a[i] * b[i] % Mod;
    NTT(a, len, -1);
    REP(i, n, n * 2 - 1) ret = max(ret, (a[i] + Mod) % Mod);
    // printf("%lld %lld %lld\n", sum1, sum2, ret);
    REP(i, -m, m)
    {
        int sum = n * i * i + sum1 + 2 * i * sum2 - 2 * ret;
        if ( sum < 0 ) sum = n * i * i + sum1 - 2 * i * sum2 - 2 * ret;
        // if ( i == 1 ) printf("%lld\n", sum);
        ans = min(ans, sum);
    }
    printf("%lld\n", ans);
    return 0;
}
