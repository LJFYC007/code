#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, m, a[maxn], b[maxn], fac[maxn], inv[maxn], ans;
bool vis[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline void DFS(int x, int num)
{
	if ( x == m + 1 ) 
	{
		if ( num > m / 2 ) ++ ans;
		return ; 
	}
	REP(i, 1, m) if ( !vis[i] ) { vis[i] = true; DFS(x + 1, num + (b[x] < a[i])); vis[i] = false; } 
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
#endif
	n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld%lld", &n, &m);
	REP(i, 1, m) scanf("%lld", &a[i]);
	sort(a + 1, a + m + 1);
	while ( n -- ) 
	{
		int op; scanf("%lld", &op);
		REP(i, 1, m) scanf("%lld", &b[i]);
		sort(b + 1, b + m + 1);

		ans = 0; DFS(1, 0);
		printf("%lld\n", (ans + Mod) * inv[m] % Mod); 
	}
	return 0;
}
