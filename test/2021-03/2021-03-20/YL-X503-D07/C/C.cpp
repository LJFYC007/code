#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define int long long
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 2e5 + 10;
const int Mod = 998244353;

int n, a[maxn], fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

inline vector<int> Solve(int l, int r)
{
	int Mid = l + r >> 1; vector<int> f = Solve(Mid, r);

}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);
	vector<int> f = Solve(0, n); REP(i, 0, n) printf("%lld ", (f[i] + Mod) % Mod); puts("");
	return 0;
}
