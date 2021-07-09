#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;
#define int long long

const int Mod = 998244353;

struct node { int f, g, h; } ;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline node Solve(int n, int a, int b, int c)
{
	node ans;
	if ( a == 0 )
	{
		ans.f = (n + 1) * (b / c) % Mod;
		ans.g = (b / c) * ((n * (n + 1) / 2) % Mod) % Mod;
		ans.h = ((n + 1) * (b / c) % Mod) * (b / c) % Mod;
		return ans;
	}
	if ( a >= c || b >= c )
	{
		int x = (n * (n + 1) / 2) % Mod, y = (x * (2 * n + 1) % Mod) * power(3, Mod - 2) % Mod;
		ans.f = (x * (a / c) + (n + 1) * (b / c)) % Mod;
		ans.g = (y * (a / c) + x * (b / c)) % Mod;
		ans.h = ((y * (a / c) % Mod) * (a / c) + ((b / c) * (n + 1) % Mod) * (b / c) + ((a / c) * n % Mod) * ((b / c) * (n + 1) % Mod)) % Mod;
		node p = Solve(n, a % c, b % c, c);
		ans.f = (ans.f + p.f) % Mod;
		ans.g = (ans.g + p.g) % Mod;
		ans.h = (ans.h + p.h + 2 * (b / c) * p.f + 2 * (a / c) * p.g) % Mod;
		return ans;
	}
	int m = (a * n + b) / c;
	int x = (n * m % Mod) * (n + 1) % Mod, y = (n * m % Mod) * (m + 1) % Mod;
	node p = Solve(m - 1, c, c - b - 1, a);
	ans.f = (n * m - p.f) % Mod;
	ans.g = (x - p.h - p.f) * power(2, Mod - 2) % Mod;
	ans.h = (y - 2 * p.g - 2 * p.f - ans.f) % Mod;
	return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int T; scanf("%lld", &T);
	while ( T -- )
	 {
		 int n, a, b, c; scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
		 node ans = Solve(n, a, b, c);
		 printf("%lld %lld %lld\n", (ans.f + Mod) % Mod, (ans.h + Mod) % Mod, (ans.g + Mod) % Mod);
	 }
	return 0;
}
