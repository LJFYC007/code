/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月25日 星期六 11时11分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const LL Mod = 100003;

inline LL js(LL a, LL b)
{
	LL r = 1;
	while ( b ) 
	{
		if ( b & 1 ) r = (r * a) % Mod;
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
	LL m, n; cin >> m >> n;
	LL ans = js(m, n) - (m * js(m - 1, n - 1)); ans %= Mod;
	ans = ans < 0 ? ans + Mod : ans;
	printf("%lld\n", ans);
    return 0;
}
