/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年01月31日 星期日 09时15分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5e6 + 10;

int n, k, Mod, f[maxn], ans, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &k, &Mod); k %= Mod;
	fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	n /= 2; f[0] = 1; int sum = k;
	REP(i, 1, n)
	{
		sum = sum * (k - 1) % Mod;
		f[i] = -sum * fac[2 * i - 2] % Mod;
		f[i] = f[i] * inv[i - 1] % Mod;
		f[i] = f[i] * inv[i] % Mod;
	}
	REP(i, 0, n) ans = (ans + f[i] * power(k, 2 * (n - i))) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
