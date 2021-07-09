/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月25日 星期六 10时28分42秒
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
		if ( b & 1 ) r *= a; 
		a = a * a % Mod; r %= Mod; b >>= 1;
	}
	return r;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	LL a, b, Mod;
	cin >> a >> b >> Mod;
	cout << js(a, b, Mod) << endl;
    return 0;
}
