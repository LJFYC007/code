/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3e5 + 10;
const int Mod = 998244353;

int n, m, k, d, a, b, c, fac[maxn], inv[maxn], ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

inline int calc(int n, int m)
{
	if ( (n + m) % 2 == 1 ) return 0;
	int ret = C(n, (n + m) / 2);
	//ret = (ret - C(n, (n + m) / 2 - 1)) % Mod;
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	n = maxn - 10; fac[0] = inv[0] = 1;
	REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	cin >> d >> n >> m >> k >> a >> b >> c;
	if ( m == 1 && k == 1 ) 
	{
		REP(i, 1, n)
		{
			int len = abs(i - a + 1);
			if ( len % 2 == 1 ) continue ; 
			ans = (ans + calc(d, len)) % Mod;
		}
		printf("%lld\n", (ans + Mod) % Mod);
	}
    return 0;
}
