/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年10月27日 星期日 19时54分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

int ans = 10000000000000;

signed main()
{
    int n; scanf("%lld", &n);
    for ( int i = 1; i * i <= n; ++ i ) 
        if ( n % i == 0 ) 
            ans = min(ans, i + n / i);
    printf("%lld\n", ans - 2);
    return 0;
}
