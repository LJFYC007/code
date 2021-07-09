/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月25日 星期六 16时45分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

LL n, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	cin >> n;
	for ( LL i = 2; i * i <= n; ++ i )
		if ( n % i == 0 ) { printf("%lld\n", n / i); return 0; }
    return 0;
}
