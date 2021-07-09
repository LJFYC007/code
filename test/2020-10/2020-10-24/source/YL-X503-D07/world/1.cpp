/***************************************************************
	File name: world.cpp
	Author: ljfcnyali
	Create time: 2020年10月24日 星期六 10时31分02秒
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

int A, ans;

inline int power(int a, int b, int p) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % p; a = a * a % p; b >>= 1; } return r; }

inline bool Check(int n)
{
    ++ n; int N = 0, p = n;
    REP(i, 1, n) if ( __gcd(i, n) == 1 ) ++ N;
    if ( N != n - 1 ) return false;
    n = N;

    for ( int i = 2; i * i <= n; ++ i ) 
    {
        if ( n % i != 0 ) continue ;
        while ( n % i == 0 ) n /= i;
        if ( power(2, N / i, p) == 1 ) return false;
    }
    if ( n > 1 && power(2, N / n, p) == 1 ) return false;

    return true;
}

signed main()
{
    freopen("world.in", "r", stdin);
    freopen("world.out", "w", stdout);
    scanf("%lld", &A);
    for ( int i = 2; i <= A; i += 2 ) 
        if ( Check(i) ) ans += i;
    printf("%.5lf\n", ans * 1.0 / (A / 2));
    return 0;
}
