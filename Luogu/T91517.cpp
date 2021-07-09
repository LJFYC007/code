/***************************************************************
	File name: T91517.cpp
	Author: ljfcnyali
	Create time: 2019年09月08日 星期日 10时55分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int Mod = 998244353;

int T, n;

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
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld", &n);
        if ( n >= Mod ) { printf("-1\n"); continue ; }
        n %= Mod;
        if ( n % 2 == 0 ) { puts("0"); continue ; }
        printf("%lld\n", power((n + 1) / 2, Mod - 2));
    }
    return 0;
}
