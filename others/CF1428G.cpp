/***************************************************************
	File name: CF1428G.cpp
	Author: ljfcnyali
	Create time: 2020年10月21日 星期三 10时17分48秒
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
const int INF = 1e18;

int n, k, F[6], f[maxn], m;

inline int calc(int x)
{
    int now = 0, cur = 0;
    while ( x ) 
    {
        if ( x % 10 == 3 ) cur += F[now];
        if ( x % 10 == 6 ) cur += 2 * F[now];
        if ( x % 10 == 9 ) cur += 3 * F[now];
        x /= 10; ++ now;
    }
    return cur;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = 1000000; scanf("%lld", &k); k = 3 * k - 3;
    REP(i, 1, n) f[i] = -INF;
    REP(i, 0, 5) scanf("%lld", &F[i]);
    for ( int i = 1; i <= k; i *= 2 ) 
    {
        int val = 3 * i; k -= i;
        REP(j, 0, 5)
        {
            for ( int o = n; o >= val; -- o ) f[o] = max(f[o], f[o - val] + F[j] * i);
            val *= 10;
        }
    }
    int val = 3 * k;
    REP(j, 0, 5)
    {
        for ( int o = n; o >= val; -- o ) f[o] = max(f[o], f[o - val] + F[j] * k);
        val *= 10;
    }
    val = 1;
    REP(i, 0, 5)
    {
        for ( int j = n; j >= 0; -- j )
            REP(k, 1, 9)
                f[j + k * val] = max(f[j + k * val], f[j] + (k % 3 == 0 ? k / 3 * F[i]: 0));
        val *= 10;
    }
    scanf("%lld", &m);
    while ( m -- ) 
    {
        int x; scanf("%lld", &x);
        printf("%lld\n", f[x]);
    }
    return 0;
}
