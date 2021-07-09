/***************************************************************
	File name: 3.cpp
	Author: ljfcnyali
	Create time: 2019年08月07日 星期三 09时44分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 50010;
const LL Mod = 1e9 + 7;

inline LL power(LL a, LL b)
{
    LL r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; }
    return r;
}

inline LL C(LL n, LL m)
{
    LL sum = 1, sum1 = 1;
    REP(i, m + 1, n) sum = (sum * i) % Mod;
    REP(i, 2, (n - m)) sum1 = (sum1 * i) % Mod;
    sum = (sum * power(sum1, Mod - 2)) % Mod;
    return sum;
}

LL f[maxn], p[maxn];

int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    LL n, m;
    scanf("%lld%lld", &m, &n);
    f[0] = 1; f[1] = n + 1;
    REP(i, 1, (n + 2) / 2) p[i] = C(n + 2 - i, i);
    REP(k, 2, m)
        REP(i, 1, (n + 2) / 2) 
            f[k] = ((f[k] + p[i] * (k - i < 0 ? 0 : f[k - i]) * (i % 2 == 1 ? 1 : -1)) % Mod + Mod) % Mod;
    printf("%lld\n", f[m]);
    return 0;
}
