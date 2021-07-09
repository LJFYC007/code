/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2021年06月28日 星期一 10时23分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int Mod = 998244353;
const int maxn = 1e6 + 10;

int T, A, x, y, z, n, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	while ( T -- ) 
	{
		scanf("%lld%lld", &n, &A);
		int ans = 0;
		if ( n - A <= 2 ) 
		{
			REP(z, 1, n - A)
			{
				x = A; y = n - x - z; 
				int ret = C(x - 1 + y - 1, x - 1) * C(z - 1 + y - 1, z - 1) % Mod;
				ans = (ans + ret * fac[x - 1] % Mod * fac[y] % Mod * fac[z - 1]) % Mod;
			}
		}
		else 
		{
			int ret = (n - 2) * ((1 - A + n * A - A * A) % Mod) % Mod * fac[n - 3] % Mod;
			ret = ret * power(A * (1 + A) % Mod, Mod - 2) % Mod;
			ans = (ans + ret) % Mod;
		}
		if ( A - 2 <= 2 ) 
		{
			REP(x, 1, A - 1)
			{
				z = n - A + 1; y = n - x - z; 
				int ret = C(x - 1 + y - 1, x - 1) * C(z - 1 + y - 1, z - 1) % Mod;
				ans = (ans + ret * fac[x - 1] % Mod * fac[y] % Mod * fac[z - 1]) % Mod;
			}
		}
		else
		{
			int z = n - A + 1;
			int ret = (n - 2) * ((1 - z + n * z - z * z) % Mod) % Mod * fac[n - 3] % Mod;
			ret = ret * power(z * (1 + z) % Mod, Mod - 2) % Mod;
			ans = (ans + ret) % Mod;
		}
		ans = (fac[n - 1] - ans) % Mod;
		printf("%lld\n", (ans + Mod) % Mod);
	}
    return 0;
}
