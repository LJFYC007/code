#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e7 + 10;

int T, p, n = maxn - 10, prime[maxn], tot, phi[maxn];
bool vis[maxn];

inline int power(int a, int b, int p) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % p; a = a * a % p; b >>= 1; } return r; }

inline int Solve(int x)
{
	if ( x == 1 ) return 0;
	int w = Solve(phi[x]) + phi[x];
	return power(2, w, x);
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	phi[1] = 1;
	REP(i, 2, n)
	{
		if ( !vis[i] ) { prime[++ tot] = i; phi[i] = i - 1; }
		for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j )
		{
			vis[i * prime[j]] = true;
			if ( i % prime[j] == 0 ) { phi[i * prime[j]] = phi[i] * prime[j]; break ; }
			phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
	while ( T -- )
	{
		scanf("%lld", &p);
		printf("%lld\n", Solve(p));
	}
	return 0;
}
