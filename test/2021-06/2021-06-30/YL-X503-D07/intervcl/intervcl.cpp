/***************************************************************
	File name: intervcl.cpp
	Author: ljfcnyali
	Create time: 2021年06月30日 星期三 16时28分04秒
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
const int B = sqrt(maxn);
const int maxm = B + 10;
const int Mod = 998244353;

int n, q, a[maxn], b[maxn], f[maxm][maxn], fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b>>= 1; } return r; }
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("intervcl.in", "r", stdin);
    freopen("intervcl.out", "w", stdout);
#endif
	scanf("%lld%lld", &n, &q); fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	REP(i, 1, n) scanf("%lld", &a[i]);
	sort(a + 1, a + n + 1); REP(i, 1, n) b[i] = a[n - i + 1];
	REP(k, 1, B) REP(j, 1, n) 
	{
		f[k][j] = (f[k - 1][j - 1] + f[k][j - 1]) % Mod;
		if ( k == 1 ) f[k][j] = (f[k][j] + b[j]) % Mod;
	}

	while ( q -- ) 
	{
		int l, r, k; scanf("%lld%lld%lld", &l, &r, &k);
		l = lower_bound(a + 1, a + n + 1, l) - a;
		r = upper_bound(a + 1, a + n + 1, r) - a - 1;
		swap(l, r); l = n - l + 1; r = n - r + 1;
		int ans = 0, num = r - l + 1; 
		if ( k <= B ) 
		{
			ans = f[k][r];
			REP(i, 1, k) ans = (ans - C(r - l + 1, k - i) * f[i][l - 1]) % Mod;
		}
		else REP(i, l, r) ans = (ans + C(r - i, k - 1) * b[i]) % Mod;
		if ( num < k ) printf("%lld %lld\n", num, -1ll);
		else printf("%lld %lld\n", num, (ans * power(C(num, k), Mod - 2) % Mod + Mod) % Mod);
	}
    return 0;
}
