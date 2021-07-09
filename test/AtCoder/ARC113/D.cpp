/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2021年02月21日 星期日 21时00分33秒
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

int n, m, k, ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &m, &k);	
	if ( n == 1 || m == 1 ) 
	{
		printf("%lld\n", power(k, n + m - 1));
		return 0; 
	}
	REP(i, 1, k) ans = (ans + (power(i, n) - power(i - 1, n)) * power(k - i + 1, m)) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
