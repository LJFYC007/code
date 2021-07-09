/***************************************************************
	File name: catch.cpp
	Author: ljfcnyali
	Create time: 2019年11月12日 星期二 18时38分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

inline int exgcd(int a, int b, int &x, int &y)
{
    if ( !b ) { x = 1; y = 0; return a; }
    int d = exgcd(b, a % b, x, y), t = x; x = y; y = t - (a / b) * y;
    return d;
}

signed main()
{
    freopen("catch.in", "r", stdin);
    freopen("catch.out", "w", stdout);
    int a, b, m, n, L, x, y;
    scanf("%lld%lld%lld%lld%lld", &a, &b, &m, &n, &L);
    if ( m < n ) { swap(a, b); swap(m, n); }
    int A = m - n, B = L, C = ((b - a) % L + L) % L, d = exgcd(A, B, x, y);
    if ( C % d != 0 ) { puts("Impossible"); return 0; }
    x *= C / d; y *= C / d;
    B /= __gcd(A, B);
    printf("%lld\n", (x % B + B) % B);
    // printf("%lld %lld %lld %lld %lld\n", A, B, x, y, C);
    return 0;
}

