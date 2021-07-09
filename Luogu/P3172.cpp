/***************************************************************
	File name: P3172.cpp
	Author: ljfcnyali
	Create time: 2019年09月26日 星期四 19时54分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int Mod = 1000000007;
const int maxn = 100010;

int ans, n, k, l, r, f[maxn];

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; }
    return r;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld%lld", &n, &k, &l, &r);
    if ( l <= k && k <= r ) ans = 1;
    -- l; l /= k; r /= k;
    for ( int i = r - l; i >= 1; -- i )
    {
        int x = l / i, y = r / i;
        f[i] = (power(y - x, n) - (y - x) + Mod) % Mod;
        for ( int j = i << 1; j <= r - l; j += i ) f[i] = (f[i] - f[j] + Mod) % Mod;
    }
    printf("%lld\n", ans + f[1]);
    return 0;
}
