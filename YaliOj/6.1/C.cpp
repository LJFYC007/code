/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月25日 星期六 10时30分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

inline LL js(LL a, LL b, LL Mod)
{
	LL r = 1;
	while ( b ) 
	{
		if ( b & 1 ) { r *= a; r %= Mod; }
		a = (a * a) % Mod; b >>= 1;
	}
	return r;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int n, m, k, x; scanf("%d%d%d%d", &n, &m, &k, &x);
	LL ans = js(10, k, n);
	ans = (x + (ans * m) % n) % n;
	printf("%lld\n", ans);
    return 0;
}
