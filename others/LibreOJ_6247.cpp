/***************************************************************
	File name: LibreOJ_6247.cpp
	Author: ljfcnyali
	Create time: 2021年02月16日 星期二 15时57分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, k;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &k);
	int omega = power(3, (Mod - 1) / k);
	int ans = 0, x = 1;
	REP(i, 0, k - 1)
	{
		ans = (ans + power(x + 1, n)) % Mod;
		x = x * omega % Mod;
	}
	ans = ans * power(k, Mod - 2) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
