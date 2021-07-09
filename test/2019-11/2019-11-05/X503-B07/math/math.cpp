/***************************************************************
	File name: math.cpp
	Author: ljfcnyali
	Create time: 2019年11月05日 星期二 08时34分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

int a, b, k, n, t1, t2;

inline int Check(int x)
{
    int ret = 0, sum1 = x / a + 1, sum2 = x % a; 
    for ( int i = x; i >= 0; i -= b ) 
    {
        ret += sum1;
        sum1 -= t1; sum2 -= t2;
        if ( sum2 < 0 ) { -- sum1; sum2 += a; }
    }
    return ret;
}

inline int Solve(int L, int R)
{
    int ans = -1;
    while ( L <= R )
    {
        int Mid = L + R >> 1;
        if ( Check(n - Mid) >= k ) { ans = Mid; L = Mid + 1; }
        else R = Mid - 1;
    }
    return ans;
}

signed main()
{
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);
    cin >> a >> b >> k;
    if ( __gcd(a, b) != 1 ) { puts("-1"); return 0; }
    if ( k == 1 ) { printf("%lld\n", a * b - a - b); return 0; }
    n = a * b - a - b;
    n = a * b - a - b;
    if ( a > b ) swap(a, b);
    t1 = b / a; t2 = b % a;
    int x = Check(n - 1), ans; if ( k > x ) { puts("-1"); return 0; }
    if ( k + 500 > x ) ans = Solve(0, 10000);
    else ans = Solve(0, n);
    printf("%lld\n", ans);
    return 0;
}

