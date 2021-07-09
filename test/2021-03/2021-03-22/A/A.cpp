#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 3e5 + 10;

int n, Mod, g[maxn], h[maxn], t[maxn], F[maxn];
vector<int> f[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &Mod);
	REP(i, 1, n) { f[i].resize(n / i + 1); f[i][1] = 1; } 
	REP(i, 1, n) for ( int j = i + i; j <= n; j += i ) ++ t[j];
	REP(i, 1, n) t[i] = power(t[i], Mod - 2);

	REP(i, 1, n) for ( int j = i; j <= n; j += i ) for ( int x = j + j; x <= n; x += j ) 
		f[i][x / i] = (f[i][x / i] + f[i][j / i] * t[x]) % Mod;

	for ( int i = n; i >= 1; -- i ) 
	{
		int num = 0; for ( int x = i; x <= n; x += i ) num = (num + f[i][x / i]) % Mod;
		F[i] = num * num % Mod;
		for ( int j = i + i; j <= n; j += i ) F[i] = (F[i] - F[j] * f[i][j / i] % Mod * f[i][j / i]) % Mod;
	}

	REP(i, 1, n) 
	{
		for ( int j = i; j <= n; j += i ) g[i] = (g[i] + f[i][j / i]) % Mod;
		for ( int j = i; j <= n; j += i ) h[i] = (h[i] + f[i][j / i] * F[j]) % Mod;
	}

	int ans = 0;
	REP(i, 1, n) ans = (ans + n * g[i] - h[i]) % Mod;
	ans = ans * 2 % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
