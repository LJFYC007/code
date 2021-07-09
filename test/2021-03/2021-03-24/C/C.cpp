#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 2e6 + 10;
const int Mod = 998244353;
const int INF = 1e18;

int R, B, fac[maxn], inv[maxn], ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
 	scanf("%lld%lld", &R, &B);
	REP(i, 0, B) REP(j, i, R)
	{
		int val = min(i ? j / i : INF, (B - i) ? (R - j) / (B - i) : INF);
		ans = (ans + val * C(i + j, i) % Mod * C(R + B - i - j, B - i)) % Mod;
	}
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
