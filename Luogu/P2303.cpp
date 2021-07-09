/***************************************************************
	File name: P2303.cpp
	Author: ljfcnyali
	Create time: 2019年08月31日 星期六 10时40分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

int n, ans;

inline int Solve(int x)
{
    int sum = x;
    for ( int i = 2; i * i <= x; ++ i )
    {
        if ( x % i == 0 ) sum *= (1 - 1.0 / i);
        while ( x % i == 0 ) x /= i;
    }
    if ( x > 1 ) sum *= (1 - 1.0 / x);
    return sum;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    for ( int i = 1; i * i <= n; ++ i ) 
    {
        if ( n % i != 0 ) continue ;
        ans += (n / i) * Solve(i);
        if ( i * i != n ) ans += i * Solve(n / i);
    }
    printf("%lld\n", ans);
    return 0;
}
