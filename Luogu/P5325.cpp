#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int Mod = 1e9 + 7;

int n, prime[maxn], tot, N, sum1[maxn], sum2[maxn], h1[maxn], h2[maxn];
int p[maxn], id1[maxn], id2[maxn], num;
bool vis[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Solve(int x, int y)
{
	if ( prime[y] >= x ) return 0;
	int t = x * tot + y;
	int pos = x <= N ? id1[x] : id2[n / x];
	int ret = (h2[pos] - h1[pos] - sum2[y] + sum1[y]) % Mod;
	for ( int i = y + 1; i <= tot && prime[i] * prime[i] <= x; ++ i )
	{
		int w = prime[i];
		for ( int e = 1; w <= x; ++ e, w *= prime[i] )
		{
			int f = (w % Mod) * ((w % Mod) - 1) % Mod;
			if ( e != 1 ) ret = (ret + f) % Mod;
			ret = (ret + f * Solve(x / w, i)) % Mod;
		}
	}
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); N = sqrt(n);
	REP(i, 2, N)
	{
		if ( !vis[i] ) prime[++ tot] = i;
		for ( int j = 1; j <= tot && i * prime[j] <= N; ++ j )
		{
			vis[i * prime[j]] = true;
			if ( i % prime[j] == 0 ) break ;
		}
	}
	REP(i, 1, tot) { sum1[i] = (sum1[i - 1] + prime[i]) % Mod; sum2[i] = (sum2[i - 1] + prime[i] * prime[i]) % Mod; }
	for ( int i = 1, j; i <= n; i = j + 1 )
	{
		j = n / (n / i); p[++ num] = n / j;
		int x = p[num] % Mod;
		h1[num] = (x * (x + 1) / 2 - 1) % Mod;
		h2[num] = ((x * (x + 1) % Mod) * ((x * 2 + 1) * power(6, Mod - 2) % Mod) - 1) % Mod;
		if ( n / j <= N ) id1[n / j] = num; else id2[j] = num;
	}
	REP(i, 1, tot) for ( int j = 1; j <= num && prime[i] * prime[i] <= p[j]; ++ j )
	{
		int pos = p[j] / prime[i];
		if ( pos <= N ) pos = id1[pos]; else pos = id2[n / pos];
		h1[j] = (h1[j] - prime[i] * (h1[pos] - sum1[i - 1])) % Mod;
		h2[j] = (h2[j] - (prime[i] * prime[i] % Mod) * (h2[pos] - sum2[i - 1])) % Mod;
	}
	printf("%lld\n", (Solve(n, 0) + 1 + Mod) % Mod);
	return 0;
}
