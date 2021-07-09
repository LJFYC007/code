/***************************************************************
	File name: P4167.cpp
	Author: ljfcnyali
	Create time: 2019年08月13日 星期二 18时57分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const LL Mod = 1e9 + 7;
const int maxn = 1000010;

LL sum[maxn];

inline void Solve(int x)
{
    for ( int i = 2; i * i <= x; ++ i ) 
        while ( x % i == 0 ) { ++ sum[i]; x /= i; }
    if ( x > 1 ) ++ sum[x];
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    LL ans = 1, n; scanf("%lld", &n);
    REP(i, 2, n) Solve(i);
    REP(i, 2, n) ans = (ans * (1 + 2 * sum[i])) % Mod;
    printf("%lld\n", ans);
    return 0;
}
