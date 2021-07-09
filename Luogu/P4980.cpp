#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int Mod = 1e9 + 7;

int T, n;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int phi(int x)
{
	int ret = x;
	for ( int i = 2; i * i <= x; ++ i )
	{
		if ( x % i == 0 ) ret = ret / i * (i - 1);
		while ( x % i == 0 ) x /= i;
	}
	if ( x > 1 ) ret = ret / x * (x - 1);
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- )
	{
		scanf("%lld", &n);
		int ans = 0;
		for ( int i = 1; i * i <= n; ++ i )
		{
			if ( n % i != 0 ) continue ;
			int x = i, y = n / i;
			ans = (ans + power(n, x) * phi(y)) % Mod;
			if ( x != y ) ans = (ans + power(n, y) * phi(x)) % Mod;
		}
		ans = ans * power(n, Mod - 2) % Mod;
		printf("%lld\n", ans);
	}
	return 0;
}
