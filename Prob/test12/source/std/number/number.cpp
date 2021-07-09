/***************************************************************
	File name: number.cpp
	Author: ljfcnyali
	Create time: 2020年11月18日 星期三 08时51分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, a[maxn], b[maxn], ans;

inline void exgcd(int a, int b, int &x, int &y)
{
    if ( !b ) { x = 1; y = 0; return ; }
    exgcd(b, a % b, x, y); int t = x; x = y; y = t - a / b * y;
}

signed main()
{
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) { int x; scanf("%lld", &x); ++ a[x]; }
    REP(i, 1, n) { int x; scanf("%lld", &x); ++ b[x]; }
    REP(i, 0, n - 1)
    {
        int t = __gcd(i, n);
        if ( m % t != 0 ) continue ;
        int A = i / t, B = n / t, C = m / t, x, y;
        exgcd(A, B, x, y); x *= C; y *= C;
        x = (x % B + B) % B;
        while ( x < n ) { ans += a[i] * b[x]; x += B; }
    }
    printf("%lld\n", ans);
    return 0;
}
