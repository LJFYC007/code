/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年03月28日 星期日 19时55分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int T; LL n; cin >> T;
	while ( T -- ) 
	{
		scanf("%lld", &n);
		if ( (n % 2 == 0) && (n / 2) % 2 == 1 ) puts("Same");
		else if ( n & 1 ) puts("Odd");
		else puts("Even");
	}
    return 0;
}
