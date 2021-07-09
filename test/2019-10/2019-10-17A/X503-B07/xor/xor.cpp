/***************************************************************
	File name: xor.cpp
	Author: ljfcnyali
	Create time: 2019年10月17日 星期四 14时38分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

int n;

signed main()
{
    freopen("xor.in", "r", stdin);
    freopen("xor.out", "w", stdout);
    scanf("%lld", &n);
    if ( n % 4 == 0 ) printf("%lld\n", n);
    else if ( n % 4 == 1 ) printf("1\n");
    else if ( n % 4 == 3 ) printf("0\n");
    else printf("%lld\n", n + 1);
    return 0;
    int sum = 0;
    REP(i, 1, n) 
    {
        printf("%lld %lld\n", i, sum ^= i);
    }
    return 0;
}
