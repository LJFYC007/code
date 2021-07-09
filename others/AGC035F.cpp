/***************************************************************
	File name: AGC035F.cpp
	Author: ljfcnyali
	Create time: 2021年02月14日 星期日 15时53分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5e5 + 10;
const int Mod = 998244353;
const int inv2 = (Mod + 1) / 2;

int fac[maxn], inv[maxn], n, m, f[maxn], ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; } 
inline int sgn(int x) { return x & 1 ? -1 : 1; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m); if ( n < m ) swap(n, m);
	fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	REP(i, 0, m) 
	{
		f[i] = C(n, i) * C(m, i) % Mod;
		f[i] = f[i] * fac[i] % Mod;
		f[i] = f[i] * power(m + 1, n - i) % Mod;
		f[i] = f[i] * power(n + 1, m - i) % Mod;
	}
	REP(i, 0, m) ans = (ans + f[i] * sgn(i)) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
